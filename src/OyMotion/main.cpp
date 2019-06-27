#include "main.h"

Hand *hand;

void setup() {
    // Start serial monitor
    Serial.begin(9600);

    // Create a hand
    hand = new Hand();
}

void loop() {
    // Handle hand
    hand->service();

    // Handle other things ...
}