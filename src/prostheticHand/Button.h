/**
 * @file        Button.cpp
 * @date        2019-06-19
 * @author      Dylan Duunk
 * 
 * @brief       Button handler with press/release callback
 */
#pragma once

#include "Arduino.h"

/**
 * @brief       Button object
 *              Define in a zero-terminated array
 */
class Button {
    void (*onPress)(void *self);
    void (*onRelease)(void *self, unsigned long duration);
    unsigned long lastPushed;
    unsigned long lastPressed;

public:
    const char *name;
    const int pin;

    // Configuration
    unsigned long debounce = 20;

    /**
     * @brief       Initialize a button
     * @param       The button's name
     * @param       The hardware pin number
     * @param       Button press callback
     * @param       Button release callback
     */
    Button(const char *name,
           const int pin,
           void (*onPress)(void *self) = nullptr,
           void (*onRelease)(void *self, unsigned long duration) = nullptr);

    /**
     * @brief       Check if button is Pressed
     * @return      True when pressed, false otherwise
     */
    bool pressed();

    /**
     * @brief       Service the button, checking if the state changed
     * @param       User data to pass to *self of callbacks
     */
    void service(void *userData);

    static Button EOL(void);
};
