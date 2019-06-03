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

// int thumbButtonPin = 8;
// int indexButtonPin = 9;
int middleButtonPin = 2;
int ringButtonPin = 3;
int pinkButtonPin = 4;

int potPin = 0;
int val;

int thumbState = HIGH;
int indexState = HIGH;
int middleState = HIGH;
int ringState = HIGH;
int pinkState = HIGH;

int thumbReading,
    indexReading,
    middleReading,
    ringReading,
    pinkReading;

int prevThumb = LOW;
int prevIndex = LOW;
int prevMiddle = LOW;
int prevRing = LOW;
int prevPink = LOW;

long time = 0;
long debounce = 200;