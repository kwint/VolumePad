

#include <Arduino.h>
#include "Adafruit_Keypad.h"
#include "order.h"
#include "slave.h"
#include "parameters.h"

bool isConnected = false; ///< True if the connection with the master is available

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
  // Init Serial
  Serial.begin(SERIAL_BAUD);

  for (int i = 0; i < faderCount; i++)
  {
    pinMode(faders[i].upPin, OUTPUT);
    digitalWrite(faders[i].upPin, LOW);
    pinMode(faders[i].downPin, OUTPUT);
    digitalWrite(faders[i].downPin, LOW);
  }

  // Wait until the arduino is isConnected to master
  while (!isConnected)
  {
    writeOrder(HELLO);
    waitForBytes(1, 1000);
    getMessageFromSerial();
  }
}

void loop()
{
  getMessageFromSerial();
  setFaders();

  sendFaders();
}

void sendFaders()
{
  int16_t faderCurrentPos;

  for (int i = 0; i < faderCount; i++)
  {
    faderCurrentPos = analogRead(faders[i].readPin);
    if (!faders[i].updating && (faderCurrentPos < (faders[i].prevPos - faderHysteresis) || faderCurrentPos > (faders[i].prevPos + faderHysteresis)))
    {
      writeOrder(i + 5);
      writeI16(faderCurrentPos);
      Serial.write('\n');
      faders[i].prevPos = faderCurrentPos;
    }
  }
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

void getMessageFromSerial()
{
  if (Serial.available() > 0)
  {
    // The first byte received is the instruction
    Order orderReceived = readOrder();

    if (orderReceived == HELLO)
    {
      // If the cards haven't say hello, check the connection
      if (!isConnected)
      {
        isConnected = true;
        writeOrder(HELLO);
      }
      else
      {
        // If we are already isConnected do not send "hello" to avoid infinite loop
        writeOrder(ALREADY_CONNECTED);
      }
    }
    else if (orderReceived == ALREADY_CONNECTED)
    {
      isConnected = true;
    }
    else
    {
      switch (orderReceived)
      {
      case FADER0:
      {
        faders[0].pos = readI16();
        faders[0].updating = true;
        break;
      }
      case FADER1:
      {
        faders[1].pos = readI16();
        faders[1].updating = true;
        break;
      }
      // Unknown order
      default:
        writeOrder(ERROR);
        writeI16(404);
        return;
      }
    }
  }
}

Order readOrder()
{
  return (Order)Serial.read();
}

void waitForBytes(int num_bytes, unsigned long timeout)
{
  unsigned long startTime = millis();
  // Wait for incoming bytes or exit if timeout
  while ((Serial.available() < num_bytes) && (millis() - startTime < timeout))
  {
  }
}

// NOTE : Serial.readBytes is SLOW
// this one is much faster, but has no timeout
void readSignedBytes(int8_t *buffer, size_t n)
{
  size_t i = 0;
  int c;
  while (i < n)
  {
    c = Serial.read();
    if (c < 0)
      break;
    *buffer++ = (int8_t)c; // buffer[i] = (int8_t)c;
    i++;
  }
}

int8_t readI8()
{
  waitForBytes(1, 100); // Wait for 1 byte with a timeout of 100 ms
  return (int8_t)Serial.read();
}

int16_t readI16()
{
  int8_t buffer[2];
  waitForBytes(2, 100); // Wait for 2 bytes with a timeout of 100 ms
  readSignedBytes(buffer, 2);
  return (((int16_t)buffer[0]) & 0xff) | (((int16_t)buffer[1]) << 8 & 0xff00);
}

int32_t readI32()
{
  int8_t buffer[4];
  waitForBytes(4, 200); // Wait for 4 bytes with a timeout of 200 ms
  readSignedBytes(buffer, 4);
  return (((int32_t)buffer[0]) & 0xff) | (((int32_t)buffer[1]) << 8 & 0xff00) | (((int32_t)buffer[2]) << 16 & 0xff0000) | (((int32_t)buffer[3]) << 24 & 0xff000000);
}

void writeOrder(enum Order myOrder)
{
  uint8_t *Order = (uint8_t *)&myOrder;
  Serial.write(Order, sizeof(uint8_t));
}

void writeI8(int8_t num)
{
  Serial.write(num);
}

void writeI16(int16_t num)
{
  int8_t buffer[2] = {(int8_t)(num & 0xff), (int8_t)(num >> 8)};
  Serial.write((uint8_t *)&buffer, 2 * sizeof(int8_t));
}

void writeI32(int32_t num)
{
  int8_t buffer[4] = {(int8_t)(num & 0xff), (int8_t)(num >> 8 & 0xff), (int8_t)(num >> 16 & 0xff), (int8_t)(num >> 24 & 0xff)};
  Serial.write((uint8_t *)&buffer, 4 * sizeof(int8_t));
}
