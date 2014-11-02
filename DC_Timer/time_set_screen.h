/*
 * "Time set" screen
 *
 *   1234567890123456
 *      SET TIME    
 *       HH:MM
 *
 */
 

void print_time_set_screen() {

  lcd_cursor(0,0);
  lcd.print("    TIME SET");
  
  lcd_cursor(5,1);
  rtc.print(lcd);
} // print_auto_screen() 
 
 
void time_set_screen(void) {
  Time *time_field = new Time();
  time_field->set(rtc.time());
  
  #ifdef SERIAL_DEBUG
  Serial.println("Entering Time Set mode");
  #endif
  
  do {
    print_time_set_screen();
    time_field->edit(lcd, 5, 1);
    if (last_button() == BUTT_SET) {
      Serial.print("1 Set time: ");
      Serial.println(time_field->get());
      rtc.set(time_field->get());
    }  
  } while (last_button() != BUTT_MODE);
  // leave this by passing along the MODE button press
  unget_button(BUTT_MODE);
} // time_set_screen()
