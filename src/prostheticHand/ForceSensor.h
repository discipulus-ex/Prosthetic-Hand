/**
 * @file        ForceSensor.cpp
 * @date        2019-06-19
 * @author      Dylan Duunk
 * 
 * @brief       Force sensor handler 
 */
#pragma once

#include "Arduino.h"

/**
 * @brief       Force sensor object
 */
class ForceSensor {

public:
    const char *name;
    const int pin;
    int val;
    int correctionVal;

    /**
     * @brief       Service the Force sensor
     */
    void service(int rotation);
};