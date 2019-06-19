/**
 * @file        Button.cpp
 * @date        2019-06-19
 * @author      Dylan Duunk
 * 
 * @brief       Button handler with press/release callback
 */
#pragma once

/**
 * @brief       Button object
 *              Define in a zero-terminated array
 */
struct Button {
    const char name[20];
    const int pin;

    /**
     * @brief       Called on button press
     */
    const void (*onPress)(void);

    /**
     * @brief       Called on release of button
     * @param[in]   Duration that the button was pressed in milliseconds
     */
    const void (*onRelease)(unsigned long duration);

    // Private variables
    unsigned long lastPushed;
    unsigned long lastPressed;
};

/**
 * @brief       Initialize an array of Buttons
 * @param       Zero-terminated button array
 */
void Button_start(Button *btns);

/**
 * @brief       Service an array of Buttons
 * @param       Zero-terminated button array
 */
void Button_service(Button *btns);
