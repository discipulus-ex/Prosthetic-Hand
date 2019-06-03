#include <Servo.h>

Servo myservo;
Servo myservo2;

int potpin = 0;
int val;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  myservo2.attach(10);
}

void loop() {
  val = analogRead(potpin);
  val = map(val, 0, 1023, 0, 180);
  
  Serial.println(val);
  
  myservo.write(val);
  myservo2.write(val);
  delay(15);
}
