/*
 * (CC BY-NC-SA 4.0) 
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 *
 */
 
#ifndef SWITCH_H
#define SWITCH_H

class Switch {
  private:
    byte _pin;
    byte _state;
    
  public:
    Switch(byte pin) {
      setup(pin);
    } // constructor
    
    void setup(byte pin) {
      _pin = pin;
      _state = LOW;
    } // setup(newPin)
    
    
    void toggle() {
      set(!_state);
    } // toggle()
    
    
    void set(boolean state) {
      Serial.print("Switch[");
      Serial.print(_pin);
      Serial.print("]->set(");
      Serial.print(state);
      Serial.println(")");
      
      _state = state;
    } // set(state)
    
    
    boolean get() {
      return _state;
    }
    
    void print() {
      if (_state) {
        lcd.print("ON ");
      } else {
        lcd.print("OFF");
      }
    }
};


#endif
