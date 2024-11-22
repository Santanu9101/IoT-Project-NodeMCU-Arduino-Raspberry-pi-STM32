#define BLYNK_TEMPLATE_ID "TMPL3ZyYXb-CX"
#define BLYNK_TEMPLATE_NAME "CONTROL LED"
#define BLYNK_AUTH_TOKEN "SttpVf7k3IZGaiZTVqAunanSMZW"

                
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>  
#include <BlynkSimpleEsp8266.h>
 

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "IQOO Z7 Pro 5G ";  // Enter your Wifi Username
char pass[] = "Santanu@04";  // Enter your Wifi password

int ledpin = D4;
void setup()
{     
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);    
  pinMode(ledpin,OUTPUT);
}

void loop()
{
  Blynk.run(); 
}