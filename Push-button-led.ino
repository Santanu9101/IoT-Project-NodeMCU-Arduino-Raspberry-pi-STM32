int buttonPin = 7;
int ledPin = 12;

void setup() {
  pinMode(buttonPin,INPUT);
  pinMode(ledPin,OUTPUT);
}
void loop() {
  int buttonState = digitalRead(buttonPin);
  if(buttonState == LOW){
    digitalWrite(ledPin,HIGH);
  }
  else{
    digitalWrite(ledPin,LOW);
  }
}