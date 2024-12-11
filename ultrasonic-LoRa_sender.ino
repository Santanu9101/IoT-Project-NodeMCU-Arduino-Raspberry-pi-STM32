#include <SPI.h>
#include <LoRa.h>
#include <LiquidCrystal.h>

// LoRa module pin definitions
#define ss 10
#define rst 9
#define dio0 2

// LCD pin connections
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;

// Initialize the LCD (16 columns and 2 rows)
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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

  // Set sync word to match the transmitter
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");

  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Waiting for Data");
}

void loop() {
  // Check if there are any packets available
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Read the packet
    String receivedData = "";
    while (LoRa.available()) {
      receivedData += (char)LoRa.read();
    }

    // Extract the distance value (assuming format "Distance: XX.XX cm")
    float distance = 0;
    int startIdx = receivedData.indexOf(':') + 2; // Start after "Distance: "
    int endIdx = receivedData.indexOf(' ', startIdx); // End at the next space
    if (startIdx > 0 && endIdx > startIdx) {
      distance = receivedData.substring(startIdx, endIdx).toFloat();
    }

    // Print received data to Serial Monitor
    Serial.print("Received: ");
    Serial.println(receivedData);

    // Display received data on the LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distance:");
    lcd.setCursor(0, 1);
    lcd.print(distance, 2); // Show distance with two decimal places
    lcd.print(" cm");
  }

  // Add a small delay to prevent unnecessary CPU usage
  delay(100);
}