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
Switch* switches[2];


#include "Schedule.h"
Schedule* schedules[2];


#define FIRST_SCREEN    1
#define AUTO_SCREEN     1
#define MANUAL_SCREEN   2
#define SCHEDULE_SCREEN 3
#define TIME_SCREEN     4
#define NUM_SCREENS     4
byte screen = AUTO_SCREEN;

 
#include "auto_screen.h"
#include "manual_screen.h"
#include "schedule_screen.h"
#include "time_set_screen.h"



void setupSwitches() {
  for (byte i = 0; i < 2; i ++) {
    switches[i] = new Switch(i);
    schedules[i] = new Schedule();
  }
}




void setup(void) {
  #ifdef SERIAL_DEBUG
  Serial.begin(115200);
  Serial.println("Starting up!");
#endif
  setupDisplay();
  setupSwitches();
  lcd_cursor(0,0);
  lcd_print("BioQuip DC Timer");
  lcd_cursor(0,1);
  lcd.print("Free mem: ");
  lcd.print(freeMemory());
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
    screen ++;
    if (screen > NUM_SCREENS) {
      screen = FIRST_SCREEN;
    }
  } else if (button == BUTT_SET) {
  }
  
  switch (screen) {
    case MANUAL_SCREEN:
      manual_screen();
      break;
    case SCHEDULE_SCREEN:
      schedule_screen();
      break;
    case TIME_SCREEN:
      time_set_screen();
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

