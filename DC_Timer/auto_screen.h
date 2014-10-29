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
 

void print_auto_screen() {
  lcd_cursor(0,0);
  lcd.print("  ");
  rtc.print(lcd);
  lcd.print("   AUTO");
  
  lcd_cursor(0,1);
  lcd.print(" @16:44   A ON");
} // print_auto_screen() 
 
 
void auto_screen() {
  #ifdef SERIAL_DEBUG
  Serial.println("Entering Auto mode");
  #endif

  print_auto_screen();
} // auto_screen()
