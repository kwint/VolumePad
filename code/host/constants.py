from enum import Enum


class Order(Enum):
    HELLO = 0
    ERROR = 1
    ALREADY_CONNECTED = 2
    RECEIVED = 3
    STOP = 4
    FADER0 = 5
    FADER1 = 6
    BUTTON_PRESSED = 7


CHANNELS = {
    0: ["csgo_linux64", "Deep Rock Galactic", "VLC media player (LibVLC 3.0.16)"],
    1: ["Firefox"],
}
