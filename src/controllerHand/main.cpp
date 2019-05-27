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
}

void loop() {
    // TODO: make the code compatible with presets

    // for now we make use of a potmeter to control
    // all servo's for testing purposes.

    // read the value of the potmeter
    val = analogRead(potPin);
    
    // convert the value of the potmeter (0->1023) to 
    // a value for the servo's (0->180)
    val = map(val, 0, 1023, 0, 180);

    // print the value to serial for debuggging purposes
    Serial.println(val);

    // write the same value to all servo's 
    thumbServo.write(val);
    indexServo.write(val);
    middleServo.write(val);
    ringServo.write(val);
    pinkServo.write(val);

    // add a little delay so we don't overload the arduino
    delay(15); 
}
