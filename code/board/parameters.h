#ifndef PARAMETERS_H
#define PARAMETERS_H

#define SERIAL_BAUD 115200 // Baudrate

const int fader0Up = 3;
const int fader0Down = 5;
const int fader1Up = 6;
const int fader1Down = 9;

const int fader0Read = A1;
const int fader1Read = A0;
const int faderHysteresis = 15;

const int fader0Cap = A2;
const int fader1Cap = A3;

const int waitTime = 100;
const int outputs[] = {fader0Up, fader0Down, fader1Up, fader1Down, fader0Cap, fader1Cap, 2, 4};

const int faderReads[] = {A1, A0};
const int faderUps[] = {3, 6};
const int faderDowns[] = {5, 9};

const int motorSpeed = 255;

const byte ROWS = 4; // rows
const byte COLS = 3; // columns
// define the symbols on the buttons of the keypads
char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};
byte rowPins[ROWS] = {15, 14, 16, 10};
byte colPins[COLS] = {7, 8, 1};

// If DEBUG is set to true, the arduino will send back all the received messages
#define DEBUG false

#endif
