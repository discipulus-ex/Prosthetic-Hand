#include "Hand.h"

// Silly translation layer by lack of std::function
void Hand_onPlayPressed(void *self) { ((Hand *)self)->onPlayPressed(); }
void Hand_onPausePressed(void *self) { ((Hand *)self)->onPausePressed(); }
void Hand_onStopPressed(void *self) { ((Hand *)self)->onStopPressed(); }
void Hand_onNextPressed(void *self) { ((Hand *)self)->onNextPressed(); }
void Hand_onPrevPressed(void *self) { ((Hand *)self)->onPrevPressed(); }
void Hand_onRelease(void *self, unsigned long duration) { ((Hand *)self)->onRelease(duration); }

void Hand::onPlayPressed() {
    if (this->isPaused) {
        if (!this->isAttached)
            this->attachServos();

        this->write(this->gestures[this->activeGesture]);
    }
}

void Hand::onPausePressed() {
    this->isPaused = true;
    // Start manual gesture control
}

void Hand::onStopPressed() {
    if (this->isPaused) {
        this->write(this->relaxGesture);
    } else {
        this->isPaused = false; // If stop is pressed resume running
    }
}

void Hand::onNextPressed() {
    if (this->isPaused) {
        if (!this->gestures[++(this->activeGesture)].name)
            this->activeGesture = 1; // Make sure we skip the NULL value
    }
}

void Hand::onPrevPressed() {
    if (this->isPaused) {
        if (!this->gestures[--(this->activeGesture)].name)
           this->activeGesture = this->gestureSize - 2; // Make sure we skip the NULL value
    }
}

void Hand::onRelease(unsigned long duration) {
    Serial.print("Button was pressed for ");
    Serial.print(duration);
    Serial.println(" ms");
}

Hand::Hand() {
    this->attachServos();
}

void Hand::service(void) {
    for (Button *btn = this->buttons; btn->pin; btn++) {
        btn->service(this);
    }

    // for (int i = 0; i < FingerName::Count; i++) {
    //     this->fingers[i].sensors[i].service(this->gestures[this->activeGesture].rotation[i]);
    // }

    // Start live gesture control
    this->liveControl();
}

void Hand::attachServos(void) {
    for (int i = 0; i < FingerName::Count; i++) {
        this->fingers[i].servo.attach(this->beginServoPin + i);
    }
    this->isAttached = true;
}

void Hand::write(Gesture &gesture) {
    Serial.print("Applying gesture ");
    Serial.println(gesture.name);

    for (int i = 0; i < FingerName::Count; i++) { //@edited i = 0
        if (gesture.rotation[i] <= 90) {
            this->fingers[i].servo.write(gesture.rotation[i]);
            delay(500); // Add a delay to prevent finger collision
        } 

        if (gesture.rotation[i] > 90) {
            this->fingers[i].servo.write(gesture.rotation[i]);
            delay(500); // Add a delay to prevent finger collision
        }
    }
}

void Hand::liveControl() {
    if (!this->isPaused) {
        /**
         * There are 2 ways to achieve live control using the OyMotion Pro band
         * 
         * 1. Using presets, assigning another value to Gesture for a "preset value"
         * 
         * 2. Using raw data
         */
        Serial.println(this->communication->gesturePresetValue);
    }
}