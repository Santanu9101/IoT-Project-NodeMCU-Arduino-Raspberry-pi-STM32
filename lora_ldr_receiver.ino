#include <SPI.h>
#include <LoRa.h>
#include <LiquidCrystal.h>

// LoRa module pin definitions
#define ss 10
#define rst 9
#define dio0 2

// LCD pin connections
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;

// Ultrasonic sensor pins
#define trigPin 6
#define echoPin 5

// Initialize the LCD (16 columns and 2 rows)
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Sender");

  // Initialize LoRa module
  LoRa.setPins(ss, rst, dio0);

  // Initialize LoRa frequency (adjust according to your location)
  while (!LoRa.begin(866E6)) { // 866 MHz for Europe
    Serial.print(".");
    delay(500);
  }

  // Set sync word to avoid interference with other LoRa networks
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");

  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Measuring...");

  // Set pin modes for the ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Measure distance using the ultrasonic sensor
  long duration;
  float distance;

  // Send a trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo time
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  distance = duration * 0.034 / 2;

  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance, 2);
  Serial.println(" cm");

  // Display distance on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.setCursor(0, 1);
  lcd.print(distance, 2);
  lcd.print(" cm");

  // Send the distance via LoRa
  LoRa.beginPacket();
  LoRa.print("Distance: ");
  LoRa.print(distance, 2); // Send distance with two decimal places
  LoRa.println(" cm");
  LoRa.endPacket();

  // Add a small delay between measurements
  delay(1000);
}