#include "Hand.h"

// Silly translation layer by lack of std::function
void Hand_onPlayPressed(void *self) { ((Hand *)self)->onPlayPressed(); }
void Hand_onPausePressed(void *self) { ((Hand *)self)->onPausePressed(); }
void Hand_onStopPressed(void *self) { ((Hand *)self)->onStopPressed(); }
void Hand_onNextPressed(void *self) { ((Hand *)self)->onNextPressed(); }
void Hand_onPrevPressed(void *self) { ((Hand *)self)->onPrevPressed(); }
void Hand_onRelease(void *self, unsigned long duration) { ((Hand *)self)->onRelease(duration); }

void Hand::onPlayPressed() {
    if (this->isDetached) {
        this->attachServos();
        this->isDetached = false;
    }    

    this->write(this->gestures[this->activeGesture]);
}

void Hand::onPausePressed() {
    Serial.println("Pause!");
    for (int i = 0; i < FingerName::Count; i++) {
        this->fingers[i].servo.detach();
    }
    this->isDetached = true;
}

void Hand::onStopPressed() {
    this->write(this->relaxGesture);
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
    for (int i = 0; i < FingerName::Count; i++) {
        this->fingers[i].servo.attach(this->beginServoPin + i);
    }
}

void Hand::write(Gesture &gesture) {
    Serial.print("Applying gesture ");
    Serial.println(gesture.name);

    /** 
     * Check whether the thumb is in it's 180 position,
     * and whether it's blocking the movement of index
     * if so, move the thumb to it's 0 position,
     * move the index finger to it's designated position
     * and move the thumb back to it's 180 position
     */
    // if (gesture.rotation[0] == 140 && gesture.rotation[1] == 0) {
    //     this->fingers[0].servo.write(0);
    //     this->fingers[1].servo.write(gesture.rotation[1]);
    //     this->fingers[0].servo.write(gesture.rotation[0]);
    // } else if (gesture.rotation[0] == 0 && gesture.rotation[1] == 155) {
    //     this->fingers[1].servo.write(gesture.rotation[1]);
    //     this->fingers[0].servo.write(gesture.rotation[0]);
    // } else {
    //     this->fingers[0].servo.write(gesture.rotation[0]);
    //     this->fingers[1].servo.write(gesture.rotation[1]);
    // }

    for (int i = 0; i < FingerName::Count; i++) { //@edited i = 0
        if (gesture.rotation[i] <= 90) {
            this->fingers[i].servo.write(gesture.rotation[i] + this->fingers[i].sensors[i].correctionVal);
            delay(500); // Add a delay to prevent finger collision
        } 

        if (gesture.rotation[i] > 90) {
            this->fingers[i].servo.write(gesture.rotation[i] - this->fingers[i].sensors[i].correctionVal);
            delay(500); // Add a delay to prevent finger collision
        }
    }
}
