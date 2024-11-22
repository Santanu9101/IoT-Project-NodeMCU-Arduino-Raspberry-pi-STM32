#include <Wire.h>
#include <MPU6050.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "iQOO Z7 Pro 5G"; // Your WiFi SSID
const char* password = "Santanu@04"; // Your WiFi password
const char* mqtt_server = "broker.hivemq.com"; // HiveMQ server
const char* mqtt_topic = "Gyro_topic"; // Your MQTT topic

MPU6050 mpu;
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1); // Initialize I2C with SDA and SCL pins
  mpu.initialize();
  
  // Check if the MPU6050 is connected
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  // Read data from MPU6050
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  // Prepare JSON formatted string
  String payload = "{\"acceleration\": {\"x\": " + String(ax) + ", \"y\": " + String(ay) + ", \"z\": " + String(az) + "}, ";
  payload += "\"gyroscope\": {\"x\": " + String(gx) + ", \"y\": " + String(gy) + ", \"z\": " + String(gz) + "}}";
  
  // Publish data
  client.publish(mqtt_topic, payload.c_str());
  
  delay(1000); // Publish every second
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}