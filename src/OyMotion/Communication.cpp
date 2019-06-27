#include "Communication.h"

void Communication::Communication() {
    // Setup communication over serial port
    this->gesturePresetValue = 0;
}

void Communication::getGesturePreset() {
    // Get a preset value over serial port
    // use for assigning a gesture
}