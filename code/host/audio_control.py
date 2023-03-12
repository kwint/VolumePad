from typing import TypeAlias

import pulsectl
import pulsectl_asyncio

import constants as cont

Pulse: TypeAlias = pulsectl_asyncio.PulseAsync
PulseEvent: TypeAlias = pulsectl.PulseEventInfo
SinkInInfo: TypeAlias = pulsectl_asyncio.PulseSinkInputInfo


async def init():
    pulse = pulsectl_asyncio.PulseAsync("volumepad")
    await pulse.connect()

    channels = await get_channels(pulse)
    return pulse


async def get_channels(pulse: Pulse) -> dict[str, int]:
    channels: dict[int, list[int]] = {channel: [] for channel in cont.CHANNELS}

    sink: pulsectl.PulseSinkInputInfo
    for sink in await pulse.sink_input_list():
        app_sink = sink.proplist.get("application.name")
        for channel, apps in cont.CHANNELS.items():
            if isinstance(apps, list) and app_sink in apps:
                channels[channel].append(sink)
                break

            if apps == "ALL":
                channels[channel].append(sink)


async def pulse_listener(pulse: Pulse, channels: dict[str, int]):
    async with pulsectl_asyncio.PulseAsync("event-printer") as pulse:
        async for event in pulse.subscribe_events("sink_input", "client"):
            print("Pulse event:", event)

            if event.t._value == "change":
                print("Change")
            elif event.t._value == "new":
                await add_pulse_app(event, channels, pulse)
            elif event.t._value == "remove":
                remove_pulse_app(event, channels)


async def add_pulse_app(event: PulseEvent, channels: dict[str, int], pulse: Pulse):
    sink = await pulse.sink_input_info(event.index)
    channels[sink.proplist.get("application.name")] = event.index


def remove_pulse_app(event: PulseEvent, channels: dict[str, int]):
    for application, index in channels.items():
        if index == event.index:
            channels.pop(application, None)


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


def change_volume(pulse: pulsectl_asyncio.PulseAsync, channel, volume: int):
    sinks = get_sinks(pulse, channel, False)

    if sinks is None:
        return None

    for sink in sinks:
        pulse.volume_set_all_chans(sink, volume / 1024)


def get_volume(pulse: pulsectl_asyncio.PulseAsync, channel: int):
    sinks = get_sinks(pulse, channel, True)

    if sinks is None:
        return None

    volume = pulse.volume_get_all_chans(sinks[0])

    return int(volume * 1024)
