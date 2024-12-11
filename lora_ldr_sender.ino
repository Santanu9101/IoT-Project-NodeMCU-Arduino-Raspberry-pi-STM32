#include <SPI.h>
#include <LoRa.h>

#define LDR_PIN A4    
#define SS_PIN 10    
#define RST_PIN 9     
#define DIO0_PIN 2    

int counter = 0;  

void setup() {
  
  Serial.begin(115200);
  while (!Serial) {
    
    Serial.println("LoRa Sender");
  }
  Serial.println();

  
  Serial.println("Initializing LoRa...");
  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);  
  
  while (!LoRa.begin(866E6)) {
    Serial.print(".");
    delay(500);
  }
  
  
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  
  int LDR_VALUE = analogRead(LDR_PIN);
  
  
  Serial.print("Sending packet #");
  Serial.print(counter);
  Serial.print(" with LDR value: ");
  Serial.println(LDR_VALUE);

  
  LoRa.beginPacket();
  LoRa.print(LDR_VALUE);
  LoRa.endPacket();

  
  counter++;

  
  delay(10000);
}