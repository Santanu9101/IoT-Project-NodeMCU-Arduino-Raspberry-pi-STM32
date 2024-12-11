#include <SPI.h>
#include <LoRa.h>

#define ss 10        // LoRa module pin definitions
#define rst 9
#define dio0 2
#define ledPin 7    // Pin for LED indicator

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receiver");

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

  // Set LED pin as OUTPUT
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Check if data is available to read
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Turn on the LED when a packet is received
    digitalWrite(ledPin, HIGH);
    
    // Print received data
    Serial.print("Received packet: ");
    
    // Read the packet and display it on the Serial Monitor
    while (LoRa.available()) {
      char c = LoRa.read();
      Serial.print(c);
    }
    Serial.println();

    // Keep the LED on for 500ms after receiving the message
     delay(1000);
    
    // Turn off the LED after the message has been received
    digitalWrite(ledPin, LOW);
  }
}