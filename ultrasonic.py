import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

trigPin = 20
echoPin = 21

GPIO.setup(trigPin, GPIO.OUT)
GPIO.setup(echoPin, GPIO.IN)

def ultraSonic():
    GPIO.output(trigPin, GPIO.LOW)
    time.sleep(0.000002)
    GPIO.output(trigPin, GPIO.HIGH)
    time.sleep(0.000005)
    GPIO.output(trigPin, GPIO.LOW)
    time.sleep(0.000002)
    
    while GPIO.input(echoPin) == GPIO.LOW:
        signaloff = time.time()
    while GPIO.input(echoPin) == GPIO.HIGH:
        signalonn = time.time()
        
    timePassed = signalonn - signaloff   
    distance  = (timePassed * 34300)/2
    finalDistance = round(distance)
    print("Distance: " , finalDistance, "cm")
    
while True:
    ultraSonic()
    time.sleep(1)
    
    





