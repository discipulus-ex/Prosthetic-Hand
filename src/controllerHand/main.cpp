#include "main.h"

void setup() {
    // start serial monitor
    Serial.begin(BAUD_RATE);

    // attach pins to the servo's
    thumbServo.attach(thumbServoPin);
    indexServo.attach(indexServoPin);
    middleServo.attach(middleServoPin);
    ringServo.attach(ringServoPin);
    pinkServo.attach(pinkServoPin);

    pinMode(middleButtonPin, INPUT_PULLUP);
    pinMode(ringButtonPin, INPUT_PULLUP);
    pinMode(pinkButtonPin, INPUT_PULLUP);
}

void loop() {
    // read the value of the potmeter and map to
    // this value compatible with servo's
    val = analogRead(potPin);
    val = map(val, 0, 1023, 0, 180);

    // print the value to serial for debuggging purposes
    Serial.println(val);

    // thumbReading = digitalRead(thumbButtonPin);
    // indexReading = digitalRead(indexButtonPin);
    middleReading = digitalRead(middleButtonPin);
    ringReading = digitalRead(ringButtonPin);
    pinkReading = digitalRead(pinkButtonPin);

    if (middleReading == HIGH && prevMiddle == LOW && millis() - time > debounce) {
        if (middleState == HIGH)
            middleState = LOW;
        else 
            middleState = HIGH;   

        time = millis();     
    }

    if (ringReading == HIGH && prevRing == LOW && millis() - time > debounce) {
        if (ringState == HIGH)
            ringState = LOW;
        else 
            ringState = HIGH;   

        time = millis();     
    }

    if (pinkReading == HIGH && prevPink == LOW && millis() - time > debounce) {
        if (pinkState == HIGH)
            pinkState = LOW;
        else 
            pinkState = HIGH;   

        time = millis();     
    }


    prevMiddle = middleReading;
    prevRing = ringReading;
    prevPink = pinkReading;
}

void handleServos() {
    // if (thumbState) {
    //     thumbServo.write(val);
    //     delay(15);
    // } else {
    //     thumbServo.write(0);
    //     delay(15);
    // }

    // if (indexState) {
    //     indexServo.write(val);
    //     delay(15);
    // } else {
    //     indexServo.write(0);
    //     delay(15);
    // }

    if (middleState) {
        middleServo.write(val);
        delay(15);
    } else {
        middleServo.write(0);   
        delay(15); 
    }

    if (ringState) {
        ringServo.write(val);
        delay(15);
    } else {
        ringServo.write(0);   
        delay(15); 
    }

    if (pinkState) {
        pinkServo.write(val);
        delay(15);
    } else {
        pinkServo.write(0);   
        delay(15); 
    }
}