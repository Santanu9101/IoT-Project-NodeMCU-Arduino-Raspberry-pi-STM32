#define PIN_RED D1 
#define PIN_YELLOW D2
#define PIN_GREEN D3





void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
}

void loop() {
  // red light on
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_YELLOW, LOW);
  digitalWrite(PIN_GREEN, LOW);  
  delay(100);

  // yellow light on
  digitalWrite(PIN_RED, LOW);    
  digitalWrite(PIN_YELLOW, HIGH);
  digitalWrite(PIN_GREEN, LOW); 
  delay(4000); 

  // green light on
  digitalWrite(PIN_RED, LOW);    
  digitalWrite(PIN_YELLOW, LOW); 
  digitalWrite(PIN_GREEN, HIGH);
  delay(4000); 
}