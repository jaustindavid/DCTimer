/*
 * (CC BY-NC-SA 4.0) 
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 *
 */
 
#ifndef RTC_H
#define RTC_H

#include <Arduino.h>
#include "Time.h"

class RTC {

  private:
    unsigned long start;
    
  public:
    void setup(void) {
    } // constructor
    
  
    void set(unsigned long now) {
      Serial.print("RTC->set(");
      Serial.print(now);
      Serial.println(")");
      start = now - (millis()/1000L);
    } // set(unsigned long now)
    
    
    unsigned long time(void) {
      return (start + millis()/1000L) % (24L*3600L);
    } // unsigned long time()
    
    
    void print(Adafruit_RGBLCDShield lcd) {
      Time *temp = new Time();
      temp->set(time());
      temp->print(lcd);
    } // print(lcd)
};

#endif
