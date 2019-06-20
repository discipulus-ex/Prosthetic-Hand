/**
 * @file        Gesture.cpp
 * @date        2019-06-19
 * @author      Dylan Duunk
 * 
 * @brief       Gesture handler
 */
#pragma once

/**
 * @brief       Gesture object
 *              Define in a zero-terminated array
 */
struct Gesture {
    const char *name;
    const int rotation[5]; // Array of rotation for each servo

    /**
     * @brief       Called on gesture activation
     */
    const void (*onActivate)(void);
};
