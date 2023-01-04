from typing import TypeAlias

import pulsectl

import constants as cont

Pulse: TypeAlias = pulsectl.Pulse
SinkInInfo: TypeAlias = pulsectl.PulseSinkInputInfo


def init():
    pulse = pulsectl.Pulse("mediaboard")
    return pulse


def get_sinks(pulse: Pulse, channel, single=False):
    sinks = []
    for in_sink in pulse.sink_input_list():
        if in_sink.proplist.get("application.name") in cont.CHANNELS[channel]:
            sinks.append(in_sink)
            if single:
                break

    if len(sinks) == 0:
        return None

    return sinks


def change_volume(pulse: pulsectl.Pulse, channel, volume: int):
    sinks = get_sinks(pulse, channel, True)

    if sinks is None:
        return None

    for sink in sinks:
        pulse.volume_set_all_chans(sink, volume / 1024)


def get_volume(pulse: pulsectl.Pulse, channel: int):
    sinks = get_sinks(pulse, channel, True)

    if sinks is None:
        return None

    volume = pulse.volume_get_all_chans(sinks[0])

    return int(volume * 1024)
