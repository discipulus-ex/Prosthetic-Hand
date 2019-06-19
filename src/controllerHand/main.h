/**
 * @file        Main.cpp
 * @date        2019-06-19
 * @author      Dylan Duunk
 * 
 * @brief       Pin defines and callbacks
 */
#pragma once
 
#include "Servo.h"
#include "Button.h"

const int dataPin = A5;
const int latchPin = A6;
const int clockPin = A7;

Servo handServos[5]; // A servo for each finger      
int beginServoPin = 2; // Start counting from pin 2 for the servo's

// Callbacks

/**
 * @brief       Start gesture
 */
void playCallback();

/**
 * @brief       Pause gesture
 */
void pauseCallback();

/**
 * @brief       Stop gesture
 */
void stopCallback();

/**
 * @brief       Next gesture
 */
void nextCallback();

/**
 * @brief       Previous gesture
 */
void prevCallback();

/**
 * @brief       Release callback
 * @param       Duration of button press
 */
void releaseCallback(unsigned long duration);

// Pre-defined buttons for each finger
Button inputButtons[] = {
//    Button name   Pin Press callback  Release callback
    { "Play",       11, playCallback,   releaseCallback },
    { "Pause",      10, pauseCallback,  releaseCallback },
    { "Stop",       9,  stopCallback,   releaseCallback },
    { "Next",       8,  nextCallback,   releaseCallback },
    { "Previous",   7,  prevCallback,   releaseCallback },
    { 0 } // End of list
};

uint8_t value;
long time = 0;
const long debounce = 20;

