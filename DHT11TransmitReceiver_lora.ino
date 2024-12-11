#include <SPI.h>
#include <LoRa.h>

#define LDR_PIN A0   // Analog pin connected to LDR
#define LED_PIN 3    // Digital pin connected to LED
#define THRESHOLD 500 // Threshold value for light intensity

#define ss 10
#define rst 9
#define dio0 2

int counter = 0;

void setup() {
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Sender - LDR and LED");

  LoRa.setPins(ss, rst, dio0);
  while (!LoRa.begin(866E6)) {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xF3); // Set a custom sync word for your network
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  int lightIntensity = analogRead(LDR_PIN); // Read light intensity from LDR
  Serial.print("Light Intensity: ");
  Serial.println(lightIntensity);

  // Check if light intensity is below the threshold
  if (lightIntensity < THRESHOLD) {
    digitalWrite(LED_PIN, HIGH); // Turn LED ON
    Serial.println("LED ON (Dark environment)");
  } else {
    digitalWrite(LED_PIN, LOW); // Turn LED OFF
    Serial.println("LED OFF (Bright environment)");
  }

  // Send data via LoRa
  LoRa.beginPacket();
  LoRa.print("Light Intensity: ");
  LoRa.print(lightIntensity);
  LoRa.print(", LED Status: ");
  LoRa.print(lightIntensity < THRESHOLD ? "ON" : "OFF");
  LoRa.endPacket();

  counter++;
  Serial.println("Packet sent!");
  delay(10000); // Delay for 10 seconds before sending the next packet
}