

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

int16_t fader0Pos = 0;
int16_t fader1Pos = 0;

int16_t oldFader0Pos = 0;
int16_t oldFader1Pos = 0;

bool fader0Updating = false;
bool fader1Updating = false;

unsigned long lastDebug;

Adafruit_Keypad numpad = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{
  // Init Serial
  Serial.begin(SERIAL_BAUD);

  pinMode(fader0Up, OUTPUT);
  digitalWrite(fader0Up, LOW);
  pinMode(fader0Down, OUTPUT);
  digitalWrite(fader0Down, LOW);

  pinMode(fader1Up, OUTPUT);
  digitalWrite(fader1Up, LOW);
  pinMode(fader1Down, OUTPUT);
  digitalWrite(fader1Down, LOW);

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
  int16_t fader0CurrentPos;
  int16_t fader1CurrentPos;

  fader0CurrentPos = analogRead(fader0Read);
  fader1CurrentPos = analogRead(fader1Read);

  if (!fader0Updating && (fader0CurrentPos < (oldFader0Pos - faderHysteresis) || fader0CurrentPos > (oldFader0Pos + faderHysteresis)))
  {
    writeOrder(FADER0);
    writeI16(fader0CurrentPos);
    Serial.write('\n');
    oldFader0Pos = fader0CurrentPos;
  }
  if (!fader1Updating && (fader1CurrentPos < (oldFader1Pos - faderHysteresis) || fader1CurrentPos > (oldFader1Pos + faderHysteresis)))
  {
    writeOrder(FADER1);
    writeI16(fader1CurrentPos);
    Serial.write('\n');
    oldFader1Pos = fader1CurrentPos;
  }
}

void setFaders()
{
  int16_t fader0CurrentPos;
  int16_t fader1CurrentPos;

  if (fader0Updating)
  {
    fader0CurrentPos = analogRead(fader0Read);
    oldFader0Pos = fader0CurrentPos;
    if (fader0CurrentPos > (fader0Pos - faderHysteresis) && fader0CurrentPos < (fader0Pos + faderHysteresis))
    {
      fader0Updating = false;
      digitalWrite(fader0Down, LOW);
      digitalWrite(fader0Up, LOW);
    }
    else if (fader0Pos < fader0CurrentPos)
    {
      digitalWrite(fader0Up, LOW);
      analogWrite(fader0Down, motorSpeed);
    }
    else if (fader0Pos > fader0CurrentPos)
    {
      digitalWrite(fader0Down, LOW);
      analogWrite(fader0Up, motorSpeed);
    }
  }

  if (fader1Updating)
  {
    fader1CurrentPos = analogRead(fader1Read);
    oldFader1Pos = fader1CurrentPos;
    if (fader1CurrentPos > (fader1Pos - faderHysteresis) && analogRead(fader1Read) < (fader1Pos + faderHysteresis))
    {
      fader1Updating = false;
      digitalWrite(fader1Down, LOW);
      digitalWrite(fader1Up, LOW);
    }
    else if (fader1Pos < fader1CurrentPos)
    {
      digitalWrite(fader1Up, LOW);
      analogWrite(fader1Down, motorSpeed);
    }
    else if (fader1Pos > fader1CurrentPos)
    {
      digitalWrite(fader1Down, LOW);
      analogWrite(fader1Up, motorSpeed);
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
        fader0Pos = readI16();
        fader0Updating = true;
        break;
      }
      case FADER1:
      {
        fader1Pos = readI16();
        fader1Updating = true;
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
