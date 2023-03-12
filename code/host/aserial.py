import struct
from enum import Enum

import aioserial


class Order(Enum):
    HELLO = 0
    SERVO = 1
    MOTOR = 2
    ALREADY_CONNECTED = 3
    ERROR = 4
    RECEIVED = 5
    STOP = 6


async def read_order(f):
    """
    :param f: file handler or serial file
    :return: (Order Enum Object)
    """
    return Order(read_i8(f))


async def read_i8(f):
    """
    :param f: file handler or serial file
    :return: (int8_t)
    """
    return struct.unpack("<b", bytearray(f.read(1)))[0]


async def read_i16(f):
    """
    :param f: file handler or serial file
    :return: (int16_t)
    """
    return struct.unpack("<h", bytearray(f.read(2)))[0]


async def read_i32(f):
    """
    :param f: file handler or serial file
    :return: (int32_t)
    """
    return struct.unpack("<l", bytearray(f.read(4)))[0]


async def write_i8(f: aioserial.AioSerial, value):
    """
    :param f: file handler or serial file
    :param value: (int8_t)
    """
    if -128 <= value <= 127:
        await f.write_async(struct.pack("<b", value))
    else:
        print("Value error:{}".format(value))


async def write_order(f: aioserial.AioSerial, order):
    """
    :param f: file handler or serial file
    :param order: (Order Enum Object)
    """
    await write_i8(f, order.value)


async def write_i16(f: aioserial.AioSerial, value):
    """
    :param f: file handler or serial file
    :param value: (int16_t)
    """
    await f.write_async(struct.pack("<h", value))


async def write_i32(f: aioserial.AioSerial, value):
    """
    :param f: file handler or serial file
    :param value: (int32_t)
    """
    await f.write_async(struct.pack("<l", value))


async def decode_order(f: aioserial.AioSerial, byte, debug=False):
    """
    :param f: file handler or serial file
    :param byte: (int8_t)
    :param debug: (bool) whether to print or not received messages
    """
    try:
        order = Order(byte)
        if order == Order.HELLO:
            msg = "HELLO"
        elif order == Order.SERVO:
            angle = await read_i16(f)
            # Bit representation
            # print('{0:016b}'.format(angle))
            msg = "SERVO {}".format(angle)
        elif order == Order.MOTOR:
            speed = await read_i8(f)
            msg = "motor {}".format(speed)
        elif order == Order.ALREADY_CONNECTED:
            msg = "ALREADY_CONNECTED"
        elif order == Order.ERROR:
            error_code = await read_i16(f)
            msg = "Error {}".format(error_code)
        elif order == Order.RECEIVED:
            msg = "RECEIVED"
        elif order == Order.STOP:
            msg = "STOP"
        else:
            msg = ""
            print("Unknown Order", byte)

        if debug:
            print(msg)
    except Exception as e:
        print("Error decoding order {}: {}".format(byte, e))
        print("byte={0:08b}".format(byte))
        print("byte={0:08b}".format(byte))
