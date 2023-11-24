

#include <Arduino.h>
#include "Adafruit_Keypad.h"
#include "order.h"
#include "slave.h"
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
} FADER;

FADER faders[2] = {{0, 0, 0, false, fader0Up, fader0Down, fader0Read, fader0Cap}, {1, 0, 0, false, fader1Up, fader1Down, fader1Read, fader1Cap}};
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
}

void loop()
{
  //Handle USB communication
	USBMIDI.poll();

	while (USBMIDI.available()) {
		// We must read entire available data, so in case we receive incoming
		// MIDI data, the host wouldn't get stuck.
		u8 b = USBMIDI.read();
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
