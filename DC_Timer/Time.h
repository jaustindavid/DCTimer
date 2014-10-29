/*
 * (CC BY-NC-SA 4.0) 
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 *
 */
 
#ifndef TIME_H
#define TIME_H

#include <Arduino.h>
// eww
// #include <Adafruit_RGBLCDShield.h>


class Time {
  private:
    byte id;
    byte hh, mm;


  public:
    Time() {
      set(0);
    } // constructor
    
    
    Time(byte _hh, byte _mm) {
      set(_hh, _mm);
    } // constructor (hh, mm);
    
    
    // secs can be arbitrarily huge, but assumes 0 was 00:00:00
    void set(unsigned long secs) {
      Serial.print("Time_HHMM set: ");
      Serial.println(secs);      
      long tod = secs % (24*3600);
      mm = (tod % 3600) / 60;
      hh = tod / 3600;
    } // set(unsigned long secs)
    
    
    void set(byte _hh, byte _mm) {
      Serial.print("Time_HHMM set: ");
      Serial.print(_hh);
      Serial.print(":");
      Serial.println(_mm);
      hh = _hh;
      mm = _mm;
    } // set(byte hh, byte mm)
    
 /*   
    static void print(Adafruit_RGBLCDShield lcd, unsigned long secs) {
      Time time;
      time.set(secs);
      time.print(lcd);
    } // print()
*/

    void print(Adafruit_RGBLCDShield lcd) {      
      Serial.print("Time_HHMM print: ");
      Serial.print(hh);
      Serial.print(":");
      Serial.println(mm);

      if (hh < 10) {
        lcd.print("0");
      }
      lcd.print(hh);
      lcd.print(":");
      if (mm < 10) {
        lcd.print("0");
      }
      lcd.print(mm);
    } // print()

};


#endif
