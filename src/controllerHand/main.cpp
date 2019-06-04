#include "main.h"

void setup() {
    // Start serial monitor
    Serial.begin(9600);

    // Attach pins to the servo's
    for (int i = 0; i < sizeof(handServos) / sizeof(handServos[0]); i++) {
        Serial.println(i);
        handServos[i].attach(i + beginServoPin);
    }

    // Configure pinMode for each button
    for (int i = 0; i < sizeof(fingerButtons) / sizeof(fingerButtons[0]); i++) {
        pinMode(fingerButtons[i].pin, INPUT_PULLUP);
    }
}

void loop() {
    // Read the value of the potmeter and map to
    // this value compatible with servo's
    val = analogRead(potPin);
    val = map(val, 0, 1023, 0, 180);

    // Iterate over the fingers
    for (int i = 0; i < sizeof(fingerButtons) / sizeof(fingerButtons[0]); i++) {
        fingerButtons[i].reading = digitalRead(fingerButtons[i].pin);

        // Makes the each button act like a switch
        if (fingerButtons[i].reading == HIGH && fingerButtons[i].prev == LOW && millis() - time > debounce) {
            if (fingerButtons[i].state == HIGH) 
                fingerButtons[i].state = LOW;
            else 
                fingerButtons[i].state = HIGH;

            time = millis();        
        }

        if (fingerButtons[i].state == HIGH) {
            // Makes the fingers response to the potmeter when
            // button state == HIGH
            handServos[i].write(val);

            // Print te value of potmeter with is asociated finger
            // Serial.print(fingerButtons[i].name);
            // Serial.print(" ");
            // Serial.println(val);

            delay(15);
        } else {
            handServos[i].write(0);
            Serial.println("UIT");
            delay(15);
        }

        fingerButtons[i].prev = fingerButtons[i].reading;
    }
}