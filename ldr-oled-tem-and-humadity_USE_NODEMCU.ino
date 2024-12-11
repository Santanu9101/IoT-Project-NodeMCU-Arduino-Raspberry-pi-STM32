#include <DHT.h>
#include <OakOLED.h> // OLED library for specific modules

// Pin Definitions
#define DHTPIN D4               // Pin for DHT sensor
#define DHTTYPE DHT11           // DHT11 or DHT22
#define LDR_PIN A0              // Analog pin for LDR
#define LED_PIN D3              // Digital pin for LED
#define LIGHT_THRESHOLD 500     // Threshold for light/dark

// Initialize OLED and DHT sensor
OakOLED oled;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize serial monitor
  Serial.begin(115200);

  // Initialize sensors and OLED
  dht.begin();
  oled.begin();
  oled.clearDisplay();
  oled.setTextSize(1); // Adjust text size for more data
  oled.setTextColor(1);

  // Initialize LED pin
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Setup complete.");
}

void loop() {
  // Read temperature and humidity
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Read light intensity from LDR
  int ldrValue = analogRead(LDR_PIN);

  // Check sensor validity
  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT sensor!");
    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.println("Sensor Error!");
    oled.display();
    delay(500);
    return;
  }

  // Display data on Serial Monitor
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" °C, Hum: ");
  Serial.print(hum);
  Serial.print(" %, LDR: ");
  Serial.println(ldrValue);

  // Control LED based on light intensity
  if (ldrValue < LIGHT_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH); // Turn LED ON
    Serial.println("LED: ON");
  } else {
    digitalWrite(LED_PIN, LOW); // Turn LED OFF
    Serial.println("LED: OFF");
  }

  // Display data on OLED
  oled.clearDisplay();
  oled.setCursor(0, 0); // Start at the top-left corner
  oled.println("Temp: " + String(temp) + " C");
  oled.println("Hum: " + String(hum) + " %");
  oled.println("LDR: " + String(ldrValue));

  // Indicate LED state on OLED
  oled.setCursor(0, 40); // Adjust position
  if (ldrValue < LIGHT_THRESHOLD) {
    oled.println("LED: ON");
  } else {
    oled.println("LED: OFF");
  }

  oled.display(); // Show the data on OLED

  // Delay for stability
  delay(1000);
}
