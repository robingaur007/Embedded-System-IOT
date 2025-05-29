#include <ESP32Servo.h>

#define trigPin 13     // Use GPIO 13 for Trig
#define echoPin 12     // Use GPIO 12 for Echo
#define MLa 14         // Left motor 1st pin
#define MLb 27         // Left motor 2nd pin
#define MRa 26         // Right motor 1st pin
#define MRb 25         // Right motor 2nd pin
#define servoPin 33    // Servo signal pin

Servo Myservo;
long duration, distance;

void setup() {
  Serial.begin(115200);

  pinMode(MLa, OUTPUT);
  pinMode(MLb, OUTPUT);
  pinMode(MRa, OUTPUT);
  pinMode(MRb, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Myservo.attach(servoPin); // Attach servo to pin 33
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;

  Serial.println(distance);
  delay(10);

  if (distance > 15) {
    Myservo.write(90);
    digitalWrite(MRb, HIGH);
    digitalWrite(MRa, LOW);
    digitalWrite(MLb, HIGH);
    digitalWrite(MLa, LOW);
  } else if ((distance < 10) && (distance > 0)) {
    // Stop
    digitalWrite(MRb, LOW);
    digitalWrite(MRa, LOW);
    digitalWrite(MLb, LOW);
    digitalWrite(MLa, LOW);
    delay(100);

    // Servo sweep
    Myservo.write(0);
    delay(500);
    Myservo.write(180);
    delay(500);
    Myservo.write(90);
    delay(500);

    // Move backward
    digitalWrite(MRb, LOW);
    digitalWrite(MRa, HIGH);
    digitalWrite(MLb, LOW);
    digitalWrite(MLa, HIGH);
    delay(500);

    // Stop
    digitalWrite(MRb, LOW);
    digitalWrite(MRa, LOW);
    digitalWrite(MLb, LOW);
    digitalWrite(MLa, LOW);
    delay(100);

    // Rotate (adjust for turning logic)
    digitalWrite(MRb, HIGH);
    digitalWrite(MRa, LOW);
    digitalWrite(MLb, LOW);
    digitalWrite(MLa, LOW);
    delay(500);
  }
}
