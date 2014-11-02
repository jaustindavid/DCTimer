/*
 * "Auto" screen
 *
 *   1234567890123456
 *    HH:MM AUTO   A^
 *   @HH:MM B ON   Bv
 *
 *  If no programs, enter programming mode
 *
 *  Buttons:
 *    * mode    -> Manual (fallthrough)
 *    * set     -> programming_mode()
 *    * up/down -> NOP
 */
 
 

void run_auto_mode() {
  Serial.println("running auto mode");
  
  unsigned long now = rtc.time();
  for (byte s = 0; s < 2; s++) {
    if (schedules[s]->on->get() == now) {
      switches[s]->set(true);
    } else if (schedules[s]->off->get() == now) {
      switches[s]->set(false);
    }
  }
} // run_auto_mode()


void print_states() {
  lcd.setCursor(14,0);
  lcd.print("A");
  lcd.print(switches[SWITCH_A]->get() ? "^" : "v");
  
  lcd.setCursor(14,1);
  lcd.print("B");
  lcd.print(switches[SWITCH_B]->get() ? "^" : "v");
}


void print_next_event(byte which, boolean state, Time *time) {
  Serial.println("print_next_event()");
  lcd_cursor(0,1);
  lcd.print("@");
  time->print(lcd);
  lcd.print(" ");
  lcd.print(which == SWITCH_A ? "A" : "B");
  lcd.print(state ? " ON" : " OFF");
} // print_next_event(byte which, boolean state, Time *time)


/*
 * now = 43200 // noon
 * a.on = 28800 // 0800
 * a.off = 57600 // 1600
 * b.on = 20000
 * b.off = 40000
 *
 */
 
void get_next_event() {
  unsigned long now = rtc.time();
  unsigned long shortest = 49L*3600L; // a crazy long time
  unsigned long delta;
  byte next_state, next_switch;
  Time* next_time;

  Serial.println("get_next_event():");
  Serial.print("shortest: ");
  Serial.println(shortest);
  for (byte s = 0; s < 2; s++) {
    if (schedules[s]->on->time_until(now) < shortest) {    
      // next_time = schedules[s]->on->time();
      shortest = schedules[s]->on->time_until(now);
      Serial.print("shortest: ");
      Serial.println(shortest);
      print_next_event(s, true, schedules[s]->on);
    } else if (schedules[s]->off->time_until(now) < shortest) {
      // next = schedules[s]->off->time();
      shortest = schedules[s]->off->time_until(now);
      print_next_event(s, false, schedules[s]->off);
    }
  }
} // get_next_event()


void print_auto_screen() {
  lcd_cursor(1,0);
  rtc.print(lcd);
  lcd.print(" AUTO");
  
  get_next_event();
  print_states();
  
  return;
  lcd_cursor(0,1);
  lcd.print(" @16:44   A ON");
} // print_auto_screen() 
 
 
void auto_screen() {
  #ifdef SERIAL_DEBUG
  Serial.println("Entering Auto mode");
  #endif
  lcd.noBlink();
  print_auto_screen();
  run_auto_mode();
} // auto_screen()
