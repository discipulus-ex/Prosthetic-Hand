/**
 * @file        NA
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
    /**
     * @brief       Stores a value for the use of presets
     *              with OyMotion Pro band
     */
    const char *presetVal;
    
    /**
     * @brief       Stores an array for the rotation
     *              of each servo
     */
    const int rotation[5]; 

    /**
     * @brief       Called on gesture activation
     */
    const void (*onActivate)(void);
};
