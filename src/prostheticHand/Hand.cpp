#include "Hand.h"

// Silly translation layer by lack of std::function
void Hand_onPlayPressed(void *self) { ((Hand *)self)->onPlayPressed(); }
void Hand_onPausePressed(void *self) { ((Hand *)self)->onPausePressed(); }
void Hand_onStopPressed(void *self) { ((Hand *)self)->onStopPressed(); }
void Hand_onNextPressed(void *self) { ((Hand *)self)->onNextPressed(); }
void Hand_onPrevPressed(void *self) { ((Hand *)self)->onPrevPressed(); }
void Hand_onRelease(void *self, unsigned long duration) { ((Hand *)self)->onRelease(duration); }

void Hand::onPlayPressed() {
    Serial.println("Start!");

    this->write(this->gestures[this->activeGesture]);
    delay(1000);
}

void Hand::onPausePressed() {
    Serial.println("Pause!");
}

void Hand::onStopPressed() {
    Serial.println("Stop!");
    // for (int i = 0; i < sizeof(handServos) / sizeof(handServos[0]); i++) {
    //     handServos[i].write(0);
    //     delay(1000);
    // } 
}

void Hand::onNextPressed() {
    Serial.println("Next!");
    if (!this->gestures[++(this->activeGesture)].name) {
        this->activeGesture = 0;
    }
}

void Hand::onPrevPressed() {
    Serial.println("Previous!");
    if (this->activeGesture < 0)
        this->activeGesture = 0;
    else 
        this->activeGesture--;  
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
    for (Button *btn = this->buttons; btn->pin; btn++)
    {
        btn->service(this->buttons);
    }
}

void Hand::write(Gesture &gesture) {
    // debug("Applying gesture %s", gesture.name);
    for (int i; i < FingerName::Count; i++) {
        this->fingers[i].servo.write(gesture.rotation[i]);
    }
}
