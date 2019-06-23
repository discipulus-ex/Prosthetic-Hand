#include "main.h"

Hand *hand;

void setup() {
    // Start serial monitor
    Serial.begin(9600);

    // Create a hand
    hand = new Hand();

    // Configure pinMode for shift register
    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
}

void loop() {
    // Handle hand
    hand->service();

    // Handle other things ...
}

void shiftByte(uint8_t val) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, val);
    digitalWrite(latchPin, HIGH);
}