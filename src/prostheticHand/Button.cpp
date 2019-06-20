#include "Button.h"

long time = 0;

void Button_start(const Button *btns) {
    for (Button *btn = (Button *)btns; btn->pin; btn++) {
        pinMode(btn->pin, INPUT_PULLUP);
    }
}

void Button_service(const Button *btns) {
    // Get current time
    time = millis();

    // Iterate over the inputButtons
    for (Button *btn = (Button *)btns; btn->pin; btn++) {
        // Store time if pushed
        if (digitalRead(btn->pin) == LOW)
            btn->lastPushed = btn->lastPushed ? btn->lastPushed : time;

        // Otherwise, reset state and last push time
        else {
            if (btn->lastPressed && btn->onRelease) {
                btn->onRelease(time - btn->lastPressed);
            }
            btn->lastPressed = btn->lastPushed = 0;
        }

        // Check if last pushed time more than `debounce` in the past
        if (!btn->lastPressed && btn->lastPushed && time > btn->lastPushed + debounce) {
            btn->lastPressed = time;
            if (btn->onPress)
                btn->onPress();
        }
    }
}
