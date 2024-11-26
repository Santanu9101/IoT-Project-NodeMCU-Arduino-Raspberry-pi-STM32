#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// WiFi credentials
const char* ssid = "iQOO Z7 Pro 5G";  // Replace with your WiFi SSID
const char* password = "Santanu@04";  // Replace with your WiFi password

// HiveMQ credentials
const char* mqtt_server = "192.168.64.189";  // HiveMQ broker address
const char* distance_topic = "ultrasonic/distance";  // MQTT topic for distance
const char* humidity_topic = "sensor/humidity";      // MQTT topic for humidity
const char* temperature_topic = "sensor/temperature"; // MQTT topic for temperature

WiFiClient espClient;
PubSubClient client(espClient);
// Ultrasonic sensor pins
const int trigPin = D1; // Trigger pin
const int echoPin = D2; // Echo pin

// DHT sensor setup
#define DHTPIN D3         // DHT sensor pin
#define DHTTYPE DHT11     // DHT11 or DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  dht.begin(); // Initialize DHT sensor

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
}

long readUltrasonicDistance() {
  // Trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echo pin
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance in cm
  long distance = duration * 0.034 / 2; 
  return distance;
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Read distance from ultrasonic sensor
  long distance = readUltrasonicDistance();
  Serial.print("Distance: ");
  Serial.println(distance);
  
  // Publish distance to MQTT
  String distanceStr = String(distance);
  client.publish(distance_topic, distanceStr.c_str());

  // Read data from DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if DHT readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");

    // Publish humidity and temperature to MQTT
    String humidityStr = String(humidity);
    String temperatureStr = String(temperature);
    client.publish(humidity_topic, humidityStr.c_str());
    client.publish(temperature_topic, temperatureStr.c_str());
  }

  delay(2000); // Delay between readings
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("NodeMCUClient")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}
