import RPi.GPIO as GPIO
import adafruit_DHT
import time
GPIO.setmode(GPIO.BCM)
sensor=adafruit_DHT.DHT11
pin=24
def read_sensor():
    temperature, humidity =adafruit_DHT.read_retry(sensor,pin)
    #print("temperature")
    if humidity is not None and temperature is not None:
        print('temperature',temperature,'*c')
        print('Humidity ',humidity,'%')
    else:
        print('Failed to get reading. Try again!')
while True:  
    read_sensor()
    time.sleep(2)
