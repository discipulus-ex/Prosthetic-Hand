#include "main.h"

void setup() {
    // Start serial monitor
    Serial.begin(9600);

    // Attach pins to the servo's
    for (int i = 0; i < sizeof(handServos) / sizeof(handServos[0]); i++) {
        handServos[i].attach(i + beginServoPin);
    }

    // Configure pinMode for each button
    Button_start(inputButtons);

    // Configure pinMode for shift register
    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
}

void playCallback() {
    Serial.println("Start!");
}

void pauseCallback() {
    Serial.println("Pause!");
}

void stopCallback() {
    Serial.println("Stop!");
}

void nextCallback() {
    Serial.println("Next!");
}

void prevCallback() {
    Serial.println("Previous!");
}

void releaseCallback(unsigned long duration) {
    Serial.print("Button was pressed for ");
    Serial.print(duration);
    Serial.println(" ms");
}


void loop() {
    // Handle buttons
    serviceButtons(inputButtons);

    // Handle other things ...
}

void shiftByte(uint8_t val) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, val);
    digitalWrite(latchPin, HIGH);
}