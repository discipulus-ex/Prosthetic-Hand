/**
 * @file        main.cpp
 * @date        2019-06-19
 * @author      Dylan Duunk
 * 
 * @brief       Pin defines and callbacks
 */
#pragma once

#include "Arduino.h"
#include "Hand.h"

const int dataPin = A5;
const int latchPin = A6;
const int clockPin = A7;

// // Callbacks

// /**
//  * @brief       Start gesture
//  */
// void playCallback();

// /**
//  * @brief       Pause gesture
//  */
// void pauseCallback();

// /**
//  * @brief       Stop gesture
//  */
// void stopCallback();

// /**
//  * @brief       Next gesture
//  */
// void nextCallback();

// /**
//  * @brief       Previous gesture
//  */
// void prevCallback();

// /**
//  * @brief       Release callback
//  * @param       Duration of button press
//  */
// void releaseCallback(unsigned long duration);
