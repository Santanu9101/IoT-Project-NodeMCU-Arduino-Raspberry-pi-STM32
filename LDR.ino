int ledPin = 12;      // Pin connected to the LED
int ldrPin = A0;      // Pin connected to the LDR (analog pin)

void setup() {
  pinMode(ledPin, OUTPUT);  // Configure the LED pin as output
  Serial.begin(9600);       // Initialize serial communication for debugging
}

void loop() {
  int ldrValue = analogRead(ldrPin);  // Read the LDR value
  Serial.println(ldrValue);          // Print LDR value to the Serial Monitor for debugging

  // Control the LED based on the light level
  if (ldrValue < 500) { // Adjust threshold based on your environment
    digitalWrite(ledPin, HIGH); // Turn on LED if it's dark
  } else {
    digitalWrite(ledPin, LOW);  // Turn off LED if it's bright
  }

  delay(100); // Small delay for stability
}
