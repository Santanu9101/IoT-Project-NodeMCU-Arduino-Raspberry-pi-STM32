#include <LiquidCrystal.h>
#include <DHT.h>

// Initialize the LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(6, 7, 5, 4, 3, 8);

// Define the pin for the DHT sensor
#define DHTPIN 2
// Define the DHT sensor type
#define DHTTYPE DHT11
// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize LCD and DHT sensor
  lcd.begin(16, 2);  // Set up the LCD's number of columns and rows
  dht.begin();       // Start the DHT sensor
  
  // Display a message during initialization
  lcd.setCursor(0, 0);  
  lcd.print("DHT11 Sensor");
  lcd.setCursor(0, 1);  
  lcd.print("Initializing...");
  delay(2000);  // Pause for 2 seconds
}

void loop() {
  // Read temperature and humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Clear the LCD
  lcd.clear();
  
  // Display the readings on the LCD
  lcd.setCursor(0, 0);  // First row
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  
  lcd.setCursor(0, 1);  // Second row
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print(" %");
  
  delay(2000);  // Update every 2 seconds
}