/*
 * (CC BY-NC-SA 4.0) 
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 *
 */
 
#ifndef SWITCH_H
#define SWITCH_H

class Switch {
  private:
    byte pin;
    byte state;
    
  public:
    Switch() {
    } // constructor
    
    void setup(int newPin) {
      pin = newPin;
      state = LOW;
    } // setup(newPin)
    
    
    void toggle() {
      state = !state;
    } // toggle()
    
    void print() {
      if (state) {
        lcd.print("ON ");
      } else {
        lcd.print("OFF");
      }
    }
};


#endif
