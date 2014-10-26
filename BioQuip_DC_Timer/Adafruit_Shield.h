/*
 * (CC BY-NC-SA 4.0) 
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 *
 */

#ifndef ADAFRUIT_SHIELD_H
#define ADAFRUIT_SHIELD_H

// include the library code:
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7


void setupDisplay() {
  lcd.begin(16, 2);
  lcd.setBacklight(WHITE);
}


void lcd_clear(void) {
  lcd.clear();
}


void lcd_cursor(byte x, byte y) {
  lcd.setCursor(x, y);
}


void lcd_print(const char* input) {
  lcd.print(input);
}


byte get_button(int timeout_ms) {
  Timer timer = Timer(timeout_ms);
  byte button = BUTT_NONE;
  Serial.println("starting read");
  while (! timer.isExpired() && !button) {
    button = lcd.readButtons();   
  } // while (! timer.isExpired())

  if (button) {
    Serial.print("Got ");
    Serial.println(button);
  }
  
  byte butt = 0;
  switch(button) {
    case 2:  button = BUTT_SET; break;
    case 4:  button = BUTT_DOWN; break;
    case 8:  button = BUTT_UP; break;
    case 16: button = BUTT_MODE; break;
  } // switch(button)
  
  return button;
}

#endif
