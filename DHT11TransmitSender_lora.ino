#include<SPI.h>
#include<LoRa.h>
#include<DHT.h>
#define DHTPIN 4 
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);
#define ss 10
#define rst 9
#define dio0 2

int counter=0;

void setup(){
dht.begin();
Serial.begin(115200);
while(!Serial)
Serial.println("LoRa Sender");
Serial.println();
Serial.println();

Serial.println("Temperature");
Serial.println("And humidity");
LoRa.setPins(ss,rst,dio0);
while (!LoRa.begin(866E6)) {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}


void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);
float humidity = dht.readHumidity();
 float temprature = dht.readTemperature();
 
Serial.print("current humidity=");
  Serial.print(humidity);
  Serial.print("%,");
  Serial.print("current temperature=");
  Serial.print(temprature);
  Serial.println("C");
  
  LoRa.beginPacket();
  LoRa.print(temprature);
   LoRa.print(" ");
   LoRa.print("C");
   LoRa.print(" ");
   LoRa.print(humidity);
  LoRa.endPacket();

  counter++;

 delay(10000);
}