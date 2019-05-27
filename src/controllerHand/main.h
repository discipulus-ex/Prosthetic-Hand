#pragma once

// #include "Arduino.h"  
#include "Servo.h"
#include "Keypad.h"

#define BAUD_RATE 9600

Servo thumbServo, 
      indexServo, 
      middleServo, 
      ringServo, 
      pinkServo;

int thumbServoPin = 8;
int indexServoPin = 9;
int middleServoPin = 10;
int ringServoPin = 11;
int pinkServoPin = 12;

int potPin = 0;
int val;

const byte ROWS =  3;
const byte COLS = 3;

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

byte rowPins[ROWS] = {7, 6, 5};
byte colPins[COLS] = {4, 3, 2};

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

