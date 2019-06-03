#pragma once

// #include "Arduino.h"  
#include "Servo.h"
#include "Keypad.h"

#define BAUD_RATE 9600

Servo handServos[4]; // A servo for each finger      
int beginServoPin = 8; // Start counting from pin 8 for the servo's

struct Button {
    char name[20];
    int pin;
    int state;
    int reading;
    int prev;
};

Button fingerButtons[] = {
    { "Thumb", 5, HIGH, 0, LOW }, //TODO: Change pin
    { "Indexfinger", 6, HIGH, 0, LOW }, //TODO: Change pin
    { "Middlefinger", 2, HIGH, 0, LOW },
    { "Ringfinger", 3, HIGH, 0, LOW },
    { "Pink", 4, HIGH, 0, LOW },
}

int potPin = 0;
int val;

long time = 0;
long debounce = 200;