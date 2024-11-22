
#define AnalogPIN A0
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  float val = analogRead(A0);
  Serial.print("Air quality=");
  Serial.println(val);
  delay(1000);
  
}
