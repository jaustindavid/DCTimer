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
  rtc.print(lcd);
  lcd.print("   MANUAL");
  
  lcd_cursor(0,1);
  lcd.print("  A ");
  switches[SWITCH_A]->print();
  lcd.print("   B ");
  switches[SWITCH_B]->print();
  if (which == SWITCH_A) {
    lcd_cursor(4,1);
    lcd.blink();
  } else {
    lcd_cursor(12,1); 
    lcd.blink();
  }
} // print_manual_screen()


void manual_screen() {
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
      switches[which]->toggle();
    }
  } while (button != BUTT_MODE);
  
  // leave this by passing along the MODE button press
  unget_button(BUTT_MODE);
  lcd.noBlink();
} // manual_screen()
