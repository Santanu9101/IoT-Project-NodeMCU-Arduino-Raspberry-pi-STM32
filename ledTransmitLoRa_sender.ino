#include <SPI.h>
#include <LoRa.h>

#define ss 10        // LoRa module pin definitions
#define rst 9
#define dio0 2
#define buttonPin 7  // Push button pin
#define ledPin 13    // Optional LED for feedback

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Transmitter");

  // Initialize LoRa module
  LoRa.setPins(ss, rst, dio0);

  // Initialize LoRa frequency (adjust according to your location)
  while (!LoRa.begin(866E6)) { // 866 MHz for Europe
    Serial.print(".");
    delay(500);
  }

  // Set sync word to avoid other LoRa traffic
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");

  // Set button and LED pins
  pinMode(buttonPin, INPUT_PULLUP);  // Use internal pull-up resistor for the button
  pinMode(ledPin, OUTPUT);           // LED feedback
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(buttonPin) == LOW) {  // Button is pressed (active LOW)
    Serial.println("Button pressed! Sending message...");

    // Turn on the LED to indicate message transmission
    digitalWrite(ledPin, HIGH);

    // Send the message
    LoRa.beginPacket();
    LoRa.print("Button Pressed!");
    LoRa.endPacket();

    // Wait a bit before turning off the LED
    delay(500); // LED stays on for half a second

    // Turn off the LED after sending the message
    digitalWrite(ledPin, LOW);

    // Debounce the button (simple delay)
    delay(300); // Adjust if necessary
  }
}