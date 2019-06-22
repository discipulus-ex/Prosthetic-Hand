/**
 * @file        NA
 * @date        2019-06-19
 * @author      Dylan Duunk
 * 
 * @brief       Finger handler attaches a ForceSensor to a servo 
 */
#pragma once

#include "Arduino.h"
#include "Servo.h"

/**
 * @brief       Names of the fingers
 */
enum FingerName { 
    Thumb, Index, Middle, Ring, Pink, Count
};

/**
 * @brief       Finger object
 *              Define in a zero-terminated array
 */
struct Finger {
    // ForceSensor sensor; 
    Servo servo;
};