from typing import TypeAlias

import pulsectl
import pulsectl_asyncio

import constants as cont

Pulse: TypeAlias = pulsectl_asyncio.PulseAsync
PulseEvent: TypeAlias = pulsectl.PulseEventInfo
SinkInInfo: TypeAlias = pulsectl.PulseSinkInputInfo


async def init():
    pulse = pulsectl_asyncio.PulseAsync("volumepad")
    await pulse.connect()

    return pulse
    

async def get_sinks(pulse: Pulse, channel, single=False):
    sinks = []
    in_sinks = await pulse.sink_input_list()
    for in_sink in in_sinks:
        if in_sink.proplist.get("application.name") in cont.CHANNELS[channel]:
            sinks.append(in_sink)
            if single:
                break

    if len(sinks) == 0:
        return None

    return sinks


async def change_volume(pulse: pulsectl_asyncio.PulseAsync, channel, volume: int):
    sinks = await get_sinks(pulse, channel, False)

    if sinks is None:
        return None

    for sink in sinks:
        await pulse.volume_set_all_chans(sink, volume / 1024)


async def get_volume(pulse: pulsectl_asyncio.PulseAsync, channel: int):
    sinks = await get_sinks(pulse, channel, True)

    if sinks is None:
        return None

    volume = await pulse.volume_get_all_chans(sinks[0])

    return int(volume * 1024)
