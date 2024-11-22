#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// WiFi credentials
const char* ssid = "iQOO Z7 Pro 5G"; // Replace with your WiFi SSID
const char* password = "Santanu@04"; // Replace with your WiFi Password


const int mq135Pin = A0;
// ThingSpeak settings
unsigned long channelID = 2726814; // Replace with your ThingSpeak Channel ID
const char* apiKey = "66RE8UZIEDP4G3S0"; // Replace with your ThingSpeak Write API Key

WiFiClient client;

void setup() {
  Serial.begin(115200); ;
 
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  
  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  int sensorValue = analogRead(mq135Pin);  // Read the sensor value
  Serial.print("MQ-135 Sensor Value: ");
  Serial.println(sensorValue);               // Print the sensor value

   
  // Write to ThingSpeak
  ThingSpeak.setField(1, sensorValue);
  
  
  // Write the fields to ThingSpeak
  int httpCode = ThingSpeak.writeFields(channelID, apiKey);
  if (httpCode == 200) {
    Serial.println("Data sent to ThingSpeak successfully.");
  } else {
    Serial.print("Failed to send data. HTTP error code: ");
    Serial.println(httpCode);
  }

  // Wait 20 seconds before the next loop
  delay(20000);
}