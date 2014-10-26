/*
 * (CC BY-NC-SA 4.0) 
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 *
 */
 
#include <Arduino.h>
#include <stdio.h>

#include "Timer.h"

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
#include "Switch.h"

RTC rtc;
Switch switches[2];


/*
 * Classes
 * TOD: "time of day", interface to the RTC module
 *        returns TOD if set
 *        accepts a new TOD
 * 
 * Button: a debounced analog button
 *         + unpress (ungetc)
 *
 * Schedule: a timed event class
 *     given a TOD, returns the time + state of next event
 * 
 */


class TOD {
};

TOD tod;


#define BUTTON_PIN A1

/*
 * Buttons:
 *   GND - MODE - R1 - BUTTON_PIN
 *   GND - SET  - R2 - BUTTON_PIN
 *   GND -  UP  - R3 - BUTTON_PIN
 *   GND - DOWN - R4 - BUTTON_PIN
 *
 *   R1 < R2 < R3 < R4
 *
 * set *_BUTTON_VALUES appropriately :)
 * Use the Serial output, press each button, shoot for the middle
 * between adjacent buttons.
 * Note that two buttons (like down + up) might look like a lower
 * button. 
 */


#define MODE_BUTTON_LEVEL 9
#define SET_BUTTON_LEVEL 18
#define DOWN_BUTTON_LEVEL 27
#define UP_BUTTON_LEVEL 36

// returns whether, and which, button has been pressed
int get_button_pressed() {
  // debounce here?
  int button_value = analogRead(BUTTON_PIN);
  
#ifdef SERIAL_DEBUG
  if (button_value < 1023) {
    Serial.print("Button: ");
    Serial.println(button_value);
  }
#endif
  
  if (button_value < DOWN_BUTTON_LEVEL) {
    return BUTT_DOWN;
  } else if (button_value < UP_BUTTON_LEVEL) {
    return BUTT_UP;
  } else if (button_value < SET_BUTTON_LEVEL) {
    return BUTT_SET;
  } else if (button_value < MODE_BUTTON_LEVEL) {
    return BUTT_MODE;
  }
  return BUTT_NONE;
}



class Button {
};

Button button;


class Schedule {
};

Schedule schedules[10];




/*
 *  "Set time" screen
 *
 *   1234567890123456
 *     Current Time
 *       12:00 am
 *   
 *   (populate with TOD)
 *
 *   * Flash HH; up/down to change, set to accept
 *   * Flash MM; up/down to change, set to accept
 *   * Flash am/pm; up/down to toggle, set to accept
 *   return
 */
void time_set_mode() {
#ifdef SERIAL_DEBUG
  Serial.println("Entering Time Set mode");
#endif
} // time_set_mode()


/*
 * "Programming" screen
 *
 *   1234567890123456
 *     Schedule 1
 *   HH:MMa - HH:MMp
 *
 *   * Flash Schedule #; up/down to change, set to accept
 *      * on up/down, display the appropriate schedule
 *      *  --:-- - --:--    indicates no schedule
 */
void programming_mode() {
  if (false) {
    time_set_mode();
  }
} // programming_mode()


/*
 * "Manual" screen
 *
 *   1234567890123456
 *     HH:MM   MANUAL
 *     A OFF   B ON
 */
 
void print_manual_screen(byte which) {
  lcd_cursor(0,0);
  lcd.print("  ");
  rtc.print();
  lcd.print("   MANUAL");
  
  lcd_cursor(0,1);
  lcd.print("  A ");
  switches[SWITCH_A].print();
  lcd.print("   B ");
  switches[SWITCH_B].print();
  if (which == SWITCH_A) {
    lcd_cursor(4,1);
    lcd.blink();
  } else {
    lcd_cursor(12,1); 
    lcd.blink();
  }
} // print_manual_screen()

void manual_mode() {
  static byte which = SWITCH_A;
  #ifdef SERIAL_DEBUG
  Serial.println("Entering Manual mode");
  #endif
  
  int button;
  do {
    print_manual_screen(which);
    button = get_button(5000);
    if (button == BUTT_UP || button == BUTTON_DOWN) {
      which = which == SWITCH_A ? SWITCH_B : SWITCH_A;      
    } else if (button == BUTT_SET) {
      switches[which].toggle();
    }
  }   while (button != BUTT_MODE);
  lcd.noBlink();
}

/*
 * "Auto" screen
 *
 *   1234567890123456
 *     Auto  HH:MMa    *blinking cursor*
 *   On; Off @ HH:MMp  (state, next event)
 *
 *  If no programs, enter programming mode
 *
 *  Buttons:
 *    * mode    -> Manual (fallthrough)
 *    * set     -> programming_mode()
 *    * up/down -> NOP
 */
void auto_mode() {
  #ifdef SERIAL_DEBUG
  Serial.println("Entering Auto mode");
  #endif

  lcd_cursor(0,0);
  lcd.print("  ");
  rtc.print();
  lcd.print("   AUTO");
  
  lcd_cursor(0,1);
  lcd.print(" @16:44   A ON");
} // auto_mode()

#define MANUAL_STATE 1
#define AUTO_STATE 2
int state = AUTO_STATE;



/*
 * power up:
 *  if no time, set up timer first
 *
 * if there are programs
 *   enter "auto" mode
 * else
 *   enter "manual" mode
 */
void setup() {
#ifdef SERIAL_DEBUG
  Serial.begin(115200);
  Serial.println("Starting up!");
#endif
  setupDisplay();
  lcd_cursor(0,0);
  lcd_print("Hello, World!");
  delay(500);
  return;
  // if timer is not set
  if (false) {
     time_set_mode();
  }
  
  rtc.set(153);
  switches[0].setup(0);
  switches[1].setup(1);
  
  // if there are programs / schedules
  if (true) {
    state = AUTO_STATE;
  } else {
    state = MANUAL_STATE;
  }
} // setup()


/*
 * main screen
 * "mode" -> toggle auto/manual
 * "set"  -> programming mode
 */
void loop() {
  int button = get_button(5000);
  
  Serial.print("button: ");
  Serial.println(button);
/*  
  lcd_cursor(0,1);
  lcd.print(millis()/1000);
  lcd.print(": ");
  lcd.print(button);
*/

  // update states based on button press
  if (button == BUTT_MODE) {
    Serial.print("mode!  state=");
    Serial.println(state);
    lcd.clear();
    if (state == MANUAL_STATE) {
      state = AUTO_STATE;
    } else {
      state = MANUAL_STATE;
    }
  } else if (button == BUTT_SET) {
  }
  
  // show the appropriate screen
  if (state == MANUAL_STATE) {
    manual_mode();
  } else {
    auto_mode();
  }
}
