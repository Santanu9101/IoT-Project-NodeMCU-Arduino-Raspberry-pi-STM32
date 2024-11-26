#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// WiFi credentials
const char* ssid = "iQOO Z7 Pro 5G";  // Replace with your WiFi SSID
const char* password = "Santanu@04";  // Replace with your WiFi password

// HiveMQ credentials
const char* mqtt_server = "192.168.64.189";  // HiveMQ broker address
const char* topic = "ultrasonic/topic";  // Your MQTT topic

WiFiClient espClient;
PubSubClient client(espClient);

const int trigPin = D1; // Trigger pin
const int echoPin = D2; // Echo pin
const int led1 = D3;    // LED1 pin (20 cm threshold)
const int led2 = D4;    // LED2 pin (30 cm threshold)
const int led3 = D5;    // LED3 pin (40 cm threshold)

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  
  // Sensor and LED pins setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  // Initialize LEDs as off
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW)
  }
  display.clearDisplay();
  display.setTextSize(1); // Normal text size
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(F("Initializing..."));
  display.display();

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void setup_wifi() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

long readUltrasonicDistance() {
  // Trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echo pin
  long duration = pulseIn(echoPin, HIGH, 30000); // Timeout after 30ms
  if (duration == 0) {
    Serial.println("Ultrasonic sensor timeout");
    return -1; // Invalid reading
  }
  
  // Calculate distance in cm
  return duration * 0.034 / 2; 
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("NodeMCUClient")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void handleLEDs(long distance) {
  // Reset all LEDs
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  // Turn on LEDs based on distance thresholds
  if (distance >= 0 && distance <= 20) {
    digitalWrite(led1, HIGH);
  }
  if (distance > 20 && distance <= 30) {
    digitalWrite(led2, HIGH);
  }
  if (distance > 30 && distance <= 40) {
    digitalWrite(led3, HIGH);
  }
}

void updateDisplay(long distance) {
  display.clearDisplay();
  display.setCursor(0, 0);

  if (distance >= 0) {
    display.println(F("Distance:"));
    display.print(distance);
    display.println(F(" cm"));
  } else {
    display.println(F("Error reading sensor"));
  }

  // Add LED status
  display.println(F("LEDs:"));
  display.print(F("LED1 (<=20): "));
  display.println(digitalRead(led1) ? F("ON") : F("OFF"));
  display.print(F("LED2 (<=30): "));
  display.println(digitalRead(led2) ? F("ON") : F("OFF"));
  display.print(F("LED3 (<=40): "));
  display.println(digitalRead(led3) ? F("ON") : F("OFF"));

  display.display();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected, reconnecting...");
    setup_wifi();
  }
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long distance = readUltrasonicDistance();
  if (distance >= 0) { // Only publish valid readings
    Serial.print("Distance: ");
    Serial.println(distance);

    // Handle LED status
    handleLEDs(distance);

    // Update OLED display
    updateDisplay(distance);

    // Publish distance to MQTT
    String distanceStr = String(distance);
    client.publish(topic, distanceStr.c_str());
  }
  
  delay(2000); // Delay between readings
}
