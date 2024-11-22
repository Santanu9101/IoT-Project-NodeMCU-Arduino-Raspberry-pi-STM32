#include <ESP8266WiFi.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include<OakOLED.h> 

OakOLED oled;

#define AQIpin A0
   //class DHT   object dht 
void setup()
{
Serial.begin(115200); 
oled.begin();//we need to initialize the OLED object using the begin() function.
oled.clearDisplay();//clear all text
oled.setTextSize(1);//Sets the size of text that follows. The default size is “1”. Each change in size increases the text by 10 pixels in height.
oled.setTextColor(1);//set the text color
oled.setCursor(0,0); //set the coordinates to start writing text
oled.println("Air quality"); //prints the message
oled.display(); //calls this method to display character on the screen

}
void loop() {
 // put your main code here, to run repeatedly:
int sensorValue = analogRead(AQIpin);  // Read the sensor value
  Serial.print("MQ-135 Sensor Value: ");
  Serial.println(sensorValue);               // Print the sensor value


oled.clearDisplay();
oled.setCursor(0, 0);
  oled.print("air qaulity ");
  oled.print(sensorValue);
  
  oled.display();



delay(4000); //calls this method to display character on the screen
}