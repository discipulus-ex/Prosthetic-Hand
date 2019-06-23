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
#include "ForceSensor.h"

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
    ForceSensor sensors[6] = {
    //    Sensor name   Pin
        { "Thumb",      A0},
        { "Index",      A1},
        { "Middle",     A2},
        { "Ring",       A3},
        { "Pinky",      A4},
        { 0 },
    };
    Servo servo;
};