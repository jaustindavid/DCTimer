/*
 * "Schedule" screen
 *
 *   1234567890123456
 *   SCHECDULE    A    
 *   ON HHMM OFF HHMM
 *
 */
 
#include <Adafruit_RGBLCDShield.h>

void print_schedule_screen(byte which) {

  lcd_cursor(0,0);
  lcd.print("SCHEDULE  ");
  lcd.print(which == SWITCH_A ? "A" : "B");
  
  lcd_cursor(0,1);
  lcd.print("^ ");
  schedules[which]->on->print(lcd);
  lcd.print("  v ");
  schedules[which]->off->print(lcd);
  
  lcd.blink();
  lcd_cursor(10, 0);
} // print_schedule_screen(byte which)



void edit_schedule(byte which) {
  schedules[which]->on->edit(lcd, 2, 1);
  if (last_button() == BUTT_SET) {
    schedules[which]->off->edit(lcd, 11, 1);      
  }
} // edit_schedule(byte which)

 
void schedule_screen(void) {
  static byte which = SWITCH_A;
      
  #ifdef SERIAL_DEBUG
  Serial.println("Entering Schedule mode");
  #endif

  byte button;
  do {
    print_schedule_screen(which);
    button = get_button(5000);
    if (button == BUTT_UP || button == BUTTON_DOWN) {
      which = which == SWITCH_A ? SWITCH_B : SWITCH_A;      
    } else if (button == BUTT_SET) {
      edit_schedule(which);
    }
  } while (button != BUTT_MODE);
  
  // leave this by passing along the MODE button press
  unget_button(BUTT_MODE);
  lcd.noBlink();


} // auto_screen()
