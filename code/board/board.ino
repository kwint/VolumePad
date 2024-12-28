#include <Arduino.h>
#include "Adafruit_Keypad.h"
#include "parameters.h"
#include "usbmidi.h"

bool isConnected = false; ///< True if the connection with the master is available
const int channel = 1;

int RXLED = 17; // The RX LED has a defined Arduino pin
// Note: The TX LED was not so lucky, we'll need to use pre-defined
// macros (TXLED1, TXLED0) to control that.
// (We could use the same macros for the RX LED too -- RXLED1,
//  and RXLED0.)

unsigned long lastDebug;

#define MIDI_NOTE_OFF   0b10000000
#define MIDI_NOTE_ON    0b10010000
#define MIDI_CONTROL    0b10110000
#define MIDI_PITCH_BEND 0b11100000

typedef struct
{
  int index;
  int16_t pos;
  int16_t prevPos;
  bool updating;
  int upPin;
  int downPin;
  int readPin;
  int capPin;
  int16_t capBaseLine;

} FADER;

FADER faders[2] = {{0, 0, 0, false, fader0Up, fader0Down, fader0Read, fader0Cap, 0}, {1, 0, 0, false, fader1Up, fader1Down, fader1Read, fader1Cap, 0}};
const int faderCount = 2;
Adafruit_Keypad numpad = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{

  for (int i = 0; i < faderCount; i++)
  {
    pinMode(faders[i].upPin, OUTPUT);
    digitalWrite(faders[i].upPin, LOW);
    pinMode(faders[i].downPin, OUTPUT);
    digitalWrite(faders[i].downPin, LOW);

    pinMode(faders[i].readPin, INPUT);

  }
  numpad.begin();
  Serial.begin(9600);


}

void loop()
{
  USBMIDI.poll();

  while (USBMIDI.available()) {
      //Parse MIDI
      u8 command=0, channel=0, key=0, control=0, value=0, velocity=0;

      //Skip to beginning of next message (silently dropping stray data bytes)
      while(!(USBMIDI.peek() & 0b10000000)) USBMIDI.read();

      command = USBMIDI.read();
      channel = (command & 0b00001111)+1;
      command = command & 0b11110000;

      switch(command) {
        case MIDI_NOTE_ON:
        case MIDI_NOTE_OFF:
          if(USBMIDI.peek() & 0b10000000) continue; key      = USBMIDI.read();
          if(USBMIDI.peek() & 0b10000000) continue; velocity = USBMIDI.read();
          break;
        case MIDI_CONTROL:
          if(USBMIDI.peek() & 0b10000000) continue; control = USBMIDI.read();
          if(USBMIDI.peek() & 0b10000000) continue; value = USBMIDI.read();

          if (!capTouched(faders[control-20].capPin, 4250)){
            faders[control - 20].pos = map(value, 0, 127, 0, 1023);
            faders[control - 20].updating = true;
          }
          break;

      }

  }
  setFaders();

  sendFaders();
  sendButtons();
  
	USBMIDI.flush();
}

void sendButtons()
{
  numpad.tick();
  while (numpad.available())
  {
    keypadEvent e = numpad.read();
    if (e.bit.EVENT == KEY_JUST_PRESSED)
    {
      sendNote(channel, e.bit.KEY, 127);
    }
    else if (e.bit.EVENT == KEY_JUST_RELEASED)
    {
      sendNote(channel, e.bit.KEY, 0);
    }
  }
}

void sendFaders()
{
  int16_t faderCurrentPos;

  for (int i = 0; i < faderCount; i++)
  {
    faderCurrentPos = analogRead(faders[i].readPin);
    if (!faders[i].updating && (faderCurrentPos < (faders[i].prevPos - faderHysteresis) || faderCurrentPos > (faders[i].prevPos + faderHysteresis)))
    {
      sendCC(channel, i + 40, map(faderCurrentPos, 0, 1023, 0, 127));
      faders[i].prevPos = faderCurrentPos;
    }
  }
}

void sendCC(uint8_t channel, uint8_t control, uint8_t value)
{
  USBMIDI.write(0xB0 | (channel & 0xf));
  USBMIDI.write(control & 0x7f);
  USBMIDI.write(value & 0x7f);
}

void sendNote(uint8_t channel, uint8_t note, uint8_t velocity)
{
  USBMIDI.write((velocity != 0 ? 0x90 : 0x80) | (channel & 0xf));
  USBMIDI.write(note & 0x7f);
  USBMIDI.write(velocity & 0x7f);
}

void setFaders()
{
  int16_t faderCurrentPos;

  for (int i = 0; i < faderCount; i++)
  {
    if (faders[i].updating)
    {
      faderCurrentPos = analogRead(faders[i].readPin);
      faders[i].prevPos = faderCurrentPos;
      if (faderCurrentPos > (faders[i].pos - faderHysteresis) && faderCurrentPos < (faders[i].pos + faderHysteresis))
      {
        faders[i].updating = false;
        digitalWrite(faders[i].upPin, LOW);
        digitalWrite(faders[i].downPin, LOW);
      }
      else if (faders[i].pos < faderCurrentPos)
      {
        digitalWrite(faders[i].upPin, LOW);
        analogWrite(faders[i].downPin, motorSpeed);
      }
      else if (faders[i].pos > faderCurrentPos)
      {
        digitalWrite(faders[i].downPin, LOW);
        analogWrite(faders[i].upPin, motorSpeed);
      }
    }
  }
}

bool capTouched(int pin, int baseline){
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    pinMode(pin,INPUT);
    int count = 0;
    unsigned long start_time = millis();
    while (millis() - start_time < 25) { // Check for 50 ms
        if (digitalRead(pin)) {
            count++;
        }
    }
    Serial.println(count);
    return count < baseline;
}
