#include <Arduino.h>

#include "Timer.h"
#include "MemoryFree.h"


#define SERIAL_DEBUG

#define BUTT_NONE 0
#define BUTT_MODE 1
#define BUTT_SET  2
#define BUTT_UP   3
#define BUTT_DOWN 4

#define SWITCH_A  0
#define SWITCH_B  1

#define USE_ADAFRUIT
#ifdef USE_ADAFRUIT
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>
#include "Adafruit_Shield.h"

#endif


#include "RTC.h"
RTC rtc;


#include "Switch.h"
Switch switches[2];


#include "Schedule.h"
// Schedule schedules[2];



#define MANUAL_SCREEN   1
#define AUTO_SCREEN     2
#define SCHEDULE_SCREEN 3
byte screen = AUTO_SCREEN;


#include "manual_screen.h"
#include "auto_screen.h"



void setup(void) {
  #ifdef SERIAL_DEBUG
  Serial.begin(115200);
  Serial.println("Starting up!");
#endif
  setupDisplay();
  lcd_cursor(0,0);
  lcd_print("BioQuip DC Timer");
  delay(2000);
  
  rtc.set(153);

  // if there are programs / schedules
  if (true) {
    screen = AUTO_SCREEN;
  } else {
    screen = MANUAL_SCREEN;
  }
  
  lcd.clear();
} // setup()


void loop(void) {
  static byte button = BUTT_NONE;
  
  // update states based on button press
  if (button == BUTT_MODE) {
    Serial.print("mode!  screen=");
    Serial.println(screen);
    lcd.clear();
    if (screen == MANUAL_SCREEN) {
      screen = AUTO_SCREEN;
    } else {
      screen = MANUAL_SCREEN;
    }
  } else if (button == BUTT_SET) {
  }
  
  switch (screen) {
    case MANUAL_SCREEN:
      manual_screen();
      break;
    case SCHEDULE_SCREEN:
      break;
    default:
      auto_screen();
  }
  
  #ifdef MEMORY_FREE_H
    Serial.print("free memory: ");
    Serial.println(freeMemory());
  #endif

  button = get_button(5000);
  
  Serial.print("button: ");
  Serial.println(button);
}
