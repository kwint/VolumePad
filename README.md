# VolumePad

Proof of concept of a numpad / macropad with motorized faders to control volume. Fader position is also updated if you change the volume on the pc.

The main problem it tries to solve is noisy friends in discord while you are trying to clutch a csgo match

Current state of the project; PCB needs a lot of work, the original motor driver uses to much power and the fingerprint of the faders is wrong. The microcontoller code fully works, it uses MIDI for communication with the host. On windows you can use [MIDI Mixer](https://www.midi-mixer.com/). Haven't found a similar solution yet on linux, but shouldn't be hard to make. (The code in `code/host` is from before I moved the project over to MIDI).


https://user-images.githubusercontent.com/7907280/210675597-fe70f985-09b6-4afa-9840-3089a5ae9c90.mp4


## TODO:
### Code:
 - Create code for host machine
 - The capacitive button check needs work, might be electrical related
 - Clean up

### Electrical
 - Use newer motor driver
 - Fix footprint of faders
 - I think something is wrong with the capacitive button wiring
