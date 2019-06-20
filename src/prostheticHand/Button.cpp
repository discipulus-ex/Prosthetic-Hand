#include "Button.h"

Button::Button(const char *name,
               const int pin,
               void (*onPress)(void *self) = nullptr,
               void (*onRelease)(void *self, unsigned long duration) = nullptr):
    name(name),
    pin(pin),
    onPress(onPress),
    onRelease(onRelease)
{
    // Set button to input with pull up
    pinMode(this->pin, INPUT_PULLUP);
}

void Button::service(void *userData) {
    // Get current time
    unsigned long time = millis();

    // Store time if pushed
    if (digitalRead(this->pin) == LOW)
        this->lastPushed = this->lastPushed ? this->lastPushed : time;

    // Otherwise, reset state and last push time
    else {
        if (this->lastPressed && this->onRelease) {
            this->onRelease((void *)userData, time - this->lastPressed);
        }
        this->lastPressed = this->lastPushed = 0;
    }

    // Check if last pushed time more than `debounce` in the past
    if (!this->lastPressed && this->lastPushed && time > this->lastPushed + this->debounce) {
        this->lastPressed = time;
        if (this->onPress)
            this->onPress((void *)userData);
    }
}

bool Button::pressed() {
    return !!this->lastPressed;
}

static Button Button::EOL(void) {
    return Button(nullptr, 0);
}
