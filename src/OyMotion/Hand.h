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
#include "Communication.h"

// Silly translation layer by lack of std::function
void Hand_onPlayPressed(void *self);
void Hand_onPausePressed(void *self);
void Hand_onStopPressed(void *self);
void Hand_onNextPressed(void *self);
void Hand_onPrevPressed(void *self);
void Hand_onRelease(void *self, unsigned long duration);

const int gestureArraySize = 12;
const int liveGestureArraySize = 7;

class Hand {
    // Configuration
    const int beginServoPin = 2; 

    bool isAttached = false;
    bool isPaused = false;

    int activeGesture = 1; // Make sure we skip the NULL value
    const int gestureSize = gestureArraySize;
    const int liveGestureSize = liveGestureArraySize;

    // Pre-defined gestures
    Gesture gestures[gestureArraySize] = {
        { 0 },
//        Gesture name                  Rotation for each servo
        { "Thumb up",               "", {0, 155, 175, 170, 170} },
        { "Pointy finger",          "", {140, 0, 175, 170, 170} },
        { "Give em the finger",     "", {140, 155, 0, 170, 170} },
        { "Puttin a ring on it",    "", {140, 155, 175, 0, 170} },
        { "Pinky pinky",            "", {140, 155, 175, 170, 0} },
        { "Imma shoot you",         "", {0, 0, 175, 170, 170} },
        { "Peace out",              "", {140, 0, 0, 170, 170} },
        { "Rockin it",              "", {140, 0, 175, 170, 0} },
        { "Imma slap you",          "", {0, 0, 0, 0, 0} },
        { "Imma slap harder",       "", {140, 155, 175, 170, 170} },
        /**
         * Add more??
         */
        { 0 } // End of list
    };

    // We'd have to define gestures again because of the limited value of
    // presets the OyMotion Pro band offers to the user (6 to be exact)
    Gesture liveGestures[liveGestureArraySize] = {
//        Gesture name      Preset number   Rotation for each servo
        { "Open Hand",      "1",            {0, 0, 0, 0, 0} },
        { "Closed Hand",    "2",            {140, 155, 175, 170, 170} },
        { "Thumb up",       "3",            {0, 155, 175, 170, 170} },
        { "",               "4",            {} },
        { "",               "5",            {} },
        { "",               "6",            {} },
        { 0 } // End of list
    };

    // Create a seperate gesture for the relaxed position
    Gesture relaxGesture = { "Stop", "", {0, 0, 0, 0, 0} }; 

    /**
     * @brief       Physical buttons on hand palm
     */
    Button buttons[6] = {
//      Button name          Pin    Press callback          Release callback
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
     * @brief       Attach the servo's  
     */
    void attachServos(void);

    /**
     * @brief       Fingers attached to hand
     */
    Finger fingers[FingerName::Count];

    /**
     * @brief       Write the given gesture to the handler
     * @param       The gesture
     */
    void write(Gesture &gesture);

    /**
     * @brief       Live gesture control using the OyMotion Pro band
     */
    void liveControl();
};
