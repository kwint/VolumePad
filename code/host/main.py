import asyncio
import time

import aioserial
import pulsectl
import serial.tools.list_ports

import audio_control
from aserial import write_i16, write_order
from constants import CHANNELS, Command, Protocol


def connect_board(ser) -> aioserial.AioSerial:
    print(f"Board found at {ser.device}")
    return aioserial.AioSerial(ser.device, baudrate=115200)


def find_and_connect_board() -> aioserial.AioSerial:
    for ser in serial.tools.list_ports.comports():
        if ser.description == "SparkFun Pro Micro":
            return connect_board(ser)

    raise ValueError("No board found!")


async def board_reader(
    board: aioserial.AioSerial, pulse: pulsectl.Pulse, channel_volumes
):

    print("Reading board")
    while True:
        cmd = await board.read_until_async(size=4)
        print("got something")
        if len(cmd) != 4:
            print(f"Unexpected thingy! {cmd}")
            continue

        instr = Protocol(cmd)

        await audio_control.change_volume(pulse, instr.channel_num(), instr.value)
        channel_volumes[instr.channel_num()] = instr.value
        print(f"Got: {instr.channel_num()} | {instr.value}")


async def pulse_reader(
    pulse: pulsectl.Pulse, board: aioserial.AioSerial, channel_volumes
):
    while True:

        for channel in CHANNELS.keys():

            volume = await audio_control.get_volume(pulse, channel)
            if volume is None or volume == channel_volumes.get(channel):
                continue
            fader = Command.FADER0 if channel == 0 else Command.FADER1


            await write_order(board, fader)
            await write_i16(board, volume)
            print(f"Sent: {channel} | {volume}")

            channel_volumes[channel] = volume

        await asyncio.sleep(0.1)


async def main():
    board = find_and_connect_board()

    is_connected = False
    # Initialize communication with Arduino
    while not is_connected:
        print("Waiting for arduino...")
        await  write_order(board, Command.HELLO)
        bytes_array = bytearray(board.read(1))
        if not bytes_array:
            time.sleep(2)
            continue
        byte = bytes_array[0]
        if byte in [Command.HELLO.value, Command.ALREADY_CONNECTED.value]:
            is_connected = True

    print("Connected to Arduino")
    time.sleep(1)
    board.read_all()

    pulse = await audio_control.init()

    channel_volumes: dict[int, int] = {}
    print(1)

    async with asyncio.TaskGroup() as tg:
        board_reader_task = tg.create_task(board_reader(board, pulse, channel_volumes))
        pulse_reader_task = tg.create_task(pulse_reader(pulse, board, channel_volumes))

    print(2)


if __name__ == "__main__":
    asyncio.run(main())
