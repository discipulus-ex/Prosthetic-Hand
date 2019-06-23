#include "Hand.h"

// Silly translation layer by lack of std::function
void Hand_onPlayPressed(void *self) { ((Hand *)self)->onPlayPressed(); }
void Hand_onPausePressed(void *self) { ((Hand *)self)->onPausePressed(); }
void Hand_onStopPressed(void *self) { ((Hand *)self)->onStopPressed(); }
void Hand_onNextPressed(void *self) { ((Hand *)self)->onNextPressed(); }
void Hand_onPrevPressed(void *self) { ((Hand *)self)->onPrevPressed(); }
void Hand_onRelease(void *self, unsigned long duration) { ((Hand *)self)->onRelease(duration); }

/** TODO generalize the servo attaching */
void Hand::onPlayPressed() {
    if (this->isDetached) {
        this->attachServos();
        this->isDetached = false;
    }    

    this->write(this->gestures[this->activeGesture]);
}

/** TODO */
void Hand::onPausePressed() {
    Serial.println("Pause!");
    for (int i = 0; i < FingerName::Count; i++) {
        this->fingers[i].servo.detach();
    }
    this->isDetached = true;
}

void Hand::onStopPressed() {
    Gesture gesture = { "Stop", {0, 0, 0, 0, 0} };
    this->write(gesture);
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
    this->attachServos();
}

void Hand::service(void) {
    for (Button *btn = this->buttons; btn->pin; btn++) {
        btn->service(this);
    }

    for (int i = 0; i < FingerName::Count; i++) {
        this->fingers[i].sensors[i].service(this->gestures[this->activeGesture].rotation[i]);
    }
}

void Hand::attachServos(void) {
    // Attach servos
    for (int i = 0; i < FingerName::Count; i++) {
        this->fingers[i].servo.attach(this->beginServoPin + i);
    }
}

/**
 * @brief       Prevent finger collision by 
 *              guessing thumb movement 
 */
void Hand::write(Gesture &gesture) {
    Serial.print("Applying gesture ");
    Serial.println(gesture.name);

    for (int i = 0; i < FingerName::Count; i++) {
        this->fingers[i].servo.write(gesture.rotation[i]);
        delay(500); // Add a delay to prevent finger collision
    }
}
