
const int mq135Pin = A0;  // Analog pin connected to MQ-135

void setup() {
  Serial.begin(115200);   // Start Serial communication
}

void loop() {
  int sensorValue = analogRead(mq135Pin);  // Read the sensor value
  Serial.print("MQ-135 Sensor Value: ");
  Serial.println(sensorValue);               // Print the sensor value

  // Add any threshold or processing logic here

  delay(1000);  // Delay for 1 second
}