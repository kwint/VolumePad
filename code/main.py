import struct
import time

import audio_control
from constants import CHANNELS, Order
from robust_serial import read_i8, read_i16, write_i16, write_order
from robust_serial.utils import open_serial_port


def read_order(f):
    """
    :param f: file handler or serial file
    :return: (Order Enum Object)
    """
    return Order(read_i8(f))


if __name__ == "__main__":
    try:
        board = open_serial_port("/dev/ttyACM0", baudrate=115200, timeout=0)
    except Exception as e:
        raise e

    is_connected = False
    # Initialize communication with Arduino
    while not is_connected:
        print("Waiting for arduino...")
        write_order(board, Order.HELLO)
        bytes_array = bytearray(board.read(1))
        if not bytes_array:
            time.sleep(2)
            continue
        byte = bytes_array[0]
        if byte in [Order.HELLO.value, Order.ALREADY_CONNECTED.value]:
            is_connected = True

    print("Connected to Arduino")
    time.sleep(1)
    board.read_all()

    pulse = audio_control.init()

    channel_volumes: dict[int, int] = {}

    while True:
        # val = input("fader numer, value [0, 1024]:")
        # if val == "d":
        #     print_debug(board)
        #     continue

        for channel in CHANNELS.keys():

            volume = audio_control.get_volume(pulse, channel)
            if volume is None or volume == channel_volumes.get(channel):
                continue
            fader = Order.FADER0 if channel == 0 else Order.FADER1

            write_order(board, fader)
            write_i16(board, volume)
            print(f"Sent: {channel} | {volume}")

            channel_volumes[channel] = volume

        try:
            order = read_order(board)
            if order not in [Order.FADER0, Order.FADER1]:
                continue

            new_volume = read_i16(board)
            print(f"End i16 {read_i16(board)}")
            channel = 0 if order == Order.FADER0 else 1
            audio_control.change_volume(pulse, channel, new_volume)
            channel_volumes[channel] = new_volume
            print(f"Got: {channel} | {new_volume}")
            # time.sleep(0.1)
        except struct.error:
            pass
