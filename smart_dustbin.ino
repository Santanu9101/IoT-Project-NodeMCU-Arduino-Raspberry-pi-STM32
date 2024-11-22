#include <Servo.h>

const int trigPin = D1;
const int echoPin = D2;
const int distanceThreshold = 100; // Distance threshold in cm
Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(D5); // Connect servo signal pin to pin 11
  myServo.write(0);   // Set initial position to 0 degrees
  Serial.begin(9600);
}

void loop() {
  long duration, distance;
  
  // Send a 10us pulse to the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin to get the pulse duration
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance in cm
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If distance is less than 50 cm, rotate servo to 180 degrees
  if (distance < distanceThreshold) {
    myServo.write(180);  // Move to 180 degrees
  } else {
    myServo.write(0);    // Return to 0 degrees
  }
  
  delay(200); // Delay to avoid excessive checking
}
