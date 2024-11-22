#include<DHT.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
#include<OakOLED.h> 

OakOLED oled;

#define DHTPIN D4
#define DHTTYPE DHT11 
DHT dht(D4,DHTTYPE);   //class DHT   object dht 
void setup()
{
Serial.begin(9600);
oled.begin();//we need to initialize the OLED object using the begin() function.
oled.clearDisplay();//clear all text
oled.setTextSize(1);//Sets the size of text that follows. The default size is “1”. Each change in size increases the text by 10 pixels in height.
oled.setTextColor(1);//set the text color
oled.setCursor(0,0); //set the coordinates to start writing text
oled.println("TEMP AND HUM"); //prints the message
oled.display(); //calls this method to display character on the screen
dht.begin();
}
void loop() {
 // put your main code here, to run repeatedly:
int temp=dht.readTemperature();  //
int hum=dht.readHumidity();
Serial.print("temperature=");
Serial.print(temp);
Serial.println(" ");
Serial.print("humidity=");
Serial.print(hum);
oled.clearDisplay();
oled.setCursor(0, 0);
  oled.print(" ");
  oled.print(temp);
  oled.println(" C");
  oled.print("Humidity: ");
  oled.print(hum);
  oled.println(" %");
  oled.display();



delay(4000); //calls this method to display character on the screen
}