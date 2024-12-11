#include <LiquidCrystal.h>

// Initialize the LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(6, 7, 5, 4, 3, 8);

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  // Print a message to the LCD
  lcd.setCursor(0, 0);  // Set the cursor to the top-left
  lcd.print("Hello World");
}

void loop() {
  // No code needed in loop since the message doesn't change
}