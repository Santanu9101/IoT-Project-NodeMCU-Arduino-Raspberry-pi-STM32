#include <OakOLED.h>

// Define ultrasonic sensor pins
#define TRIG_PIN D5
#define ECHO_PIN D6

// Define LED pins
#define LED1_PIN D4
#define LED2_PIN D3
#define LED3_PIN D7

OakOLED oled; // Initialize the OLED display

void setup() {
  Serial.begin(9600);        // Initialize Serial communication
  oled.begin();              // Initialize OLED display
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(1);

  // Set up pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the echo pulse duration
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in centimeters
  float distance = duration * 0.034 / 2;

  // Print distance to Serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Display distance on OLED
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.println("Dist:");
  oled.setCursor(0, 20);  // Move to next line for value
  oled.println(String(distance) + " cm");
  oled.display();

  // Control LEDs based on distance
  if (distance <= 20) {
    digitalWrite(LED1_PIN, HIGH); // Turn on LED1
  } else {
    digitalWrite(LED1_PIN, LOW);  // Turn off LED1
  }

  if (distance > 20 && distance <= 30) {
    digitalWrite(LED2_PIN, HIGH); // Turn on LED2
  } else {
    digitalWrite(LED2_PIN, LOW);  // Turn off LED2
  }

  if (distance > 30 && distance <= 40) {
    digitalWrite(LED3_PIN, HIGH); // Turn on LED3
  } else {
    digitalWrite(LED3_PIN, LOW);  // Turn off LED3
  }

  delay(500); // Delay before the next measurement
}
