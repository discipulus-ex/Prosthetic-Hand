/**
 * @file        Hand.cpp
 * @date        2019-06-19
 * @author      Dylan Duunk
 * 
 * @brief       Hand handler
 */
#pragma once

#include "Arduino.h"
#include "Finger.h"
#include "Gesture.h"
#include "Button.h"

// Silly translation layer by lack of std::function
void Hand_onPlayPressed(void *self);
void Hand_onPausePressed(void *self);
void Hand_onStopPressed(void *self);
void Hand_onNextPressed(void *self);
void Hand_onPrevPressed(void *self);
void Hand_onRelease(void *self, unsigned long duration);

class Hand {
    // Configuration
    const int beginServoPin = 2; 

    int activeGesture;

    // Pre-defined gestures
    Gesture gestures[11] = {
    //    Gesture name      Rotation for each servo
        { "Thumb up", {0, 180, 180, 180, 180} },
        { "Pointy finger", {180, 0, 180, 180, 180} },
        { "Give em the finger", {180, 180, 0, 180, 180} },
        { "Puttin a ring on it", {180, 180, 180, 0, 180} },
        { "Pinky pinky", {180, 180, 180, 180, 0} },
        { "Imma shoot you", {0, 0, 180, 180, 180} },
        { "Peace out", {180, 0, 0, 180, 180} },
        { "Rockin it", {180, 0, 180, 180, 0} },
        { "Imma slap you", {0, 0, 0, 0, 0} },
        { "Imma slap harder", {180, 180, 180, 180, 180} },
        /**
         * Add more??
         */
        { 0 } // End of list
    };

    /**
     * @brief       Physical buttons on hand palm
     */
    Button buttons[6] = {
    //         Button name   Pin    Press callback          Release callback
        Button("Play",       11,    Hand_onPlayPressed,     Hand_onRelease),
        Button("Pause",      10,    Hand_onPausePressed,    Hand_onRelease),
        Button("Stop",       9,     Hand_onStopPressed,     Hand_onRelease),
        Button("Next",       8,     Hand_onNextPressed,     Hand_onRelease),
        Button("Previous",   7,     Hand_onPrevPressed,     Hand_onRelease),
        Button::EOL()
    };

public:

    /**
     * @brief       Button press event for xxxxx buttons
     */
    void onPlayPressed();

    /**
     * @brief       Button press event for xxxxx buttons
     */
    void onPausePressed();

    /**
     * @brief       Button press event for xxxxx buttons
     */
    void onStopPressed();

    /**
     * @brief       Button press event for xxxxx buttons
     */
    void onNextPressed();

    /**
     * @brief       Button press event for xxxxx buttons
     */
    void onPrevPressed();

    /**
     * @brief       Button press event for xxxxx buttons
     * @param       Duration that the button was pressed
     */
    void onRelease(unsigned long duration);

    /**
     * @brief       Hand initialzer
     */
    Hand();

    /**
     * @brief       Service hand
     *              Call periodically in loop
     */
    void service(void);

    /**
     * @brief       Fingers attached to hand
     */
    Finger fingers[FingerName::Count];

    /**
     * @brief       Write the given gesture to the handler
     * @param       The gesture
     */
    void write(Gesture &gesture);
};
