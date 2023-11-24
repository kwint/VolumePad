from enum import Enum

# "csgo_linux64",
# "Deep Rock Galactic",
# "VLC media player (LibVLC 3.0.16)",
# "Project Playtime",

CHANNELS = {
    0: ["Firefox", "WEBRTC VoiceEngine"],
    1: "ALL",
}


class Command(Enum):
    HELLO = 0
    ERROR = 1
    ALREADY_CONNECTED = 2
    RECEIVED = 3
    STOP = 4
    FADER0 = 5
    FADER1 = 6
    BUTTON_PRESSED = 7


class Protocol:
    cmd: Command
    value: int

    def __init__(self, in_bytes):
        self.cmd = Command(int(in_bytes[0]))
        self.value = self.get_value(in_bytes[1:-1])

    def get_value(self, in_bytes):
        if self.cmd in [Command.FADER0, Command.FADER1]:
            assert len(in_bytes) == 2
            return int.from_bytes(in_bytes, byteorder="little", signed=True)

    def channel_num(self):
        return int(self.cmd.name[-1])