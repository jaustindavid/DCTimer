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
      start = now;
    } // set(unsigned long now)
    
    
    unsigned long time(void) {
      return start + millis()/10;
    } // unsigned long time()
    
    
    void print(Adafruit_RGBLCDShield lcd) {
       Time::print(lcd, time());
    } // print(lcd)
};

#endif RTC_H
