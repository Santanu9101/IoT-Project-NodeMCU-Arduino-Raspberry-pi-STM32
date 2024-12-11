import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
pushBtn = 16
led_pin=24

GPIO.setup(led_pin,GPIO.OUT)
GPIO.setup(pushBtn,GPIO.IN)

while True:
    if GPIO.input(pushBtn):        
        GPIO.output(led_pin,GPIO.HIGH)
    else:       
        GPIO.output(led_pin,GPIO.LOW)
