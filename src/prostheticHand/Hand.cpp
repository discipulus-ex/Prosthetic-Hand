#include "Hand.h"

// Silly translation layer by lack of std::function
void Hand_onPlayPressed(void *self) { ((Hand *)self)->onPlayPressed(); }
void Hand_onPausePressed(void *self) { ((Hand *)self)->onPausePressed(); }
void Hand_onStopPressed(void *self) { ((Hand *)self)->onStopPressed(); }
void Hand_onNextPressed(void *self) { ((Hand *)self)->onNextPressed(); }
void Hand_onPrevPressed(void *self) { ((Hand *)self)->onPrevPressed(); }
void Hand_onRelease(void *self, unsigned long duration) { ((Hand *)self)->onRelease(duration); }

void Hand::onPlayPressed() {
    this->write(this->gestures[this->activeGesture]);
}

/** TODO */
void Hand::onPausePressed() {
    Serial.println("Pause!");
    Serial.println(this->activeGesture);
}

/** TODO */
void Hand::onStopPressed() {
    Serial.println("Stop!");
    // this->write(0);
}

void Hand::onNextPressed() {
    if (!this->gestures[++(this->activeGesture)].name)
        this->activeGesture = 1; // Make sure we skip the NULL value
}

void Hand::onPrevPressed() {
    if (!this->gestures[--(this->activeGesture)].name)
        this->activeGesture = this->gestureSize - 2; // Make sure we skip the NULL value
}

void Hand::onRelease(unsigned long duration) {
    Serial.print("Button was pressed for ");
    Serial.print(duration);
    Serial.println(" ms");
}

Hand::Hand() {
    // Attach servos
    for (int i = 0; i < FingerName::Count; i++) {
        this->fingers[i].servo.attach(this->beginServoPin + i);
    }
}

void Hand::service(void) {
    for (Button *btn = this->buttons; btn->pin; btn++) {
        btn->service(this);
    }

    for (int i = 0; i < FingerName::Count; i++) {
        this->fingers[i].sensors[i].service(this->gestures[this->activeGesture].rotation[i]);
    }
}

void Hand::write(Gesture &gesture) {
    Serial.print("Applying gesture ");
    Serial.println(gesture.name);

    for (int i = 0; i < FingerName::Count; i++) {
        this->fingers[i].servo.write(gesture.rotation[i]);
        delay(500); // Add a delay to prevent finger collision
    }
}
