#pragma once
 
#include "Servo.h"

Servo handServos[5]; // A servo for each finger      
int beginServoPin = 8; // Start counting from pin 8 for the servo's

struct Button {
    char name[20];
    int pin;
    int state;
    int reading;
    int prev;
};

// Pre-defined buttons for each finger
Button fingerButtons[] = {
    { "Thumb", 2, HIGH, 0, LOW },
    { "Indexfinger", 3, HIGH, 0, LOW },
    { "Middlefinger", 4, HIGH, 0, LOW },
    { "Ringfinger", 5, HIGH, 0, LOW },
    { "Pinky", 6, HIGH, 0, LOW },
};

int potPin = A0;
int val;

long time = 0;
long debounce = 200;