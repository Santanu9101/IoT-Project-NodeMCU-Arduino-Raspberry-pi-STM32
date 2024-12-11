// Define pin connections
#define IR_SENSOR_PIN D5  // IR sensor output pin
#define LED_PIN D6        // LED output pin

// Variables to store the sensor state
int sensorState = 0;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Set up the pins
  pinMode(IR_SENSOR_PIN, INPUT);  // IR sensor as input
  pinMode(LED_PIN, OUTPUT);       // LED as output

  // Ensure the LED is initially off
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Read the state of the IR sensor
  sensorState = digitalRead(IR_SENSOR_PIN);

  // Check if an object is detected
  if (sensorState == LOW) {  // Assuming LOW means detection
    Serial.println("Object detected! Turning on the light.");
    digitalWrite(LED_PIN, HIGH);  // Turn on the LED
  } else {
    Serial.println("No object detected. Light is off.");
    digitalWrite(LED_PIN, LOW);  // Turn off the LED
  }

  // Add a small delay to avoid rapid state changes
  delay(100);
}