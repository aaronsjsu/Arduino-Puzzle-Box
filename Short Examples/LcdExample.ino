// Example for using 16x2 LCD with arduino.

// Library for lcd display.
#include <LiquidCrystal.h>

// Pin numbers for the display.
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;

// Initialize the display.
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  // Set up the LCD's columns and rows.
  lcd.begin(16, 2);
}

void loop() {
  // This blinks "hello, world!" on the display.
  lcd.print("hello, world!");
  delay(500);
  lcd.clear();
  delay(500);
}
