import asyncio
import signal
from contextlib import suppress

import pulsectl
import pulsectl_asyncio

# import pulsectl
# print('Event types:', pulsectl.PulseEventTypeEnum)
# print('Event facilities:', pulsectl.PulseEventFacilityEnum)
# print('Event masks:', pulsectl.PulseEventMaskEnum)


async def listen():
    sinks = []

    async with pulsectl_asyncio.PulseAsync("volume-increaser") as pulse:
        for sink in await pulse.sink_input_list():
            sinks.append(sink)

    async with pulsectl_asyncio.PulseAsync("event-printer") as pulse:
        async for event in pulse.subscribe_events("sink_input", "client"):
            print("Pulse event:", event)
            # sink = await pulse.sink_input_info(event.index)
            # print(
            #     f"{sink.name}, {sink.volume.value_flat} {sink.proplist.get('application.name')}"
            # )


# Pulse event: facility=<EnumValue event-facility=client>, index=309, t=<EnumValue event-type=remove>
# Pulse event: facility=<EnumValue event-facility=client>, index=312, t=<EnumValue event-type=new>


async def main():
    # Run listen() coroutine in task to allow cancelling it
    listen_task = asyncio.create_task(listen())

    # register signal handlers to cancel listener when program is asked to terminate
    for sig in (signal.SIGTERM, signal.SIGHUP, signal.SIGINT):
        loop.add_signal_handler(sig, listen_task.cancel)
    # Alternatively, the PulseAudio event subscription can be ended by breaking/returning from the `async for` loop

    with suppress(asyncio.CancelledError):
        await listen_task


# Run event loop until main_task finishes
loop = asyncio.get_event_loop()
loop.run_until_complete(main())
