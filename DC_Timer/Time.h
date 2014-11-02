/*
 * (CC BY-NC-SA 4.0) 
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 *
 */
 
#ifndef TIME_H
#define TIME_H

#include <Arduino.h>
#include <Adafruit_RGBLCDShield.h>


class Time {
  private:
    static int id;
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
      Serial.print("Time->set1: ");
      Serial.print(secs);      
      unsigned long tod = secs % (24L*3600L);
      byte _mm = (tod % 3600L) / 60L;
      byte _hh = tod / 3600L;
      Serial.print(" ");
      Serial.print(_hh);
      Serial.print(",");
      Serial.println(_mm);
      set(_hh, _mm);
    } // set(unsigned long secs)
    
    
    void set(byte _hh, byte _mm) {
      Serial.print("Time->set2: ");
      Serial.print(_hh);
      Serial.print(":");
      Serial.println(_mm);
      hh = _hh;
      mm = _mm;
    } // set(byte hh, byte mm)


    unsigned long get() {
      Serial.print("{Time->get(): ");
      Serial.print(hh);
      Serial.print(":");
      Serial.print(mm);
      Serial.println("}");
      return (unsigned long)hh * 3600L + (unsigned long)mm * 60L;
    } // get()
    

    unsigned long time() {
      Serial.print("Time[");
      Serial.print(hh);
      Serial.print(":");
      Serial.print(mm);
      Serial.print("]->time(): ");
      unsigned long ret = (unsigned long)(hh) * 3600 + (unsigned long)(mm) * 60;
      Serial.println(ret);
      return ret;
    } // time()


    // returns seconds until the specified event
    // "now" is clock time
    // this is a switch event
    unsigned long time_until(unsigned long now) {
      unsigned long event = time();
      unsigned long delta;
      Serial.print("Time[");
      Serial.print(event);
      Serial.print("]->time_until(");
      Serial.print(now);
      Serial.print("): ");
      if (event < now) {
        // next intersect is tomorrow
        delta = 24L*3600L + event - now;
      } else {
        delta = event - now;
      }
      Serial.println(delta);
      return delta;
    } // unsigned long next(unsigned long now)
    

 /*   
    static void print(Adafruit_RGBLCDShield lcd, unsigned long secs) {
      Time time;
      time.set(secs);
      time.print(lcd);
    } // print()
*/

    void printField(Adafruit_RGBLCDShield lcd, byte value) {
      if (value < 10) {
        lcd.print("0");
      }
      lcd.print(value);

    }

    void print(Adafruit_RGBLCDShield lcd) {      
      Serial.print("Time->print: ");
      Serial.print(hh);
      Serial.print(":");
      Serial.println(mm);

      printField(lcd, hh);
      lcd.print(":");
      printField(lcd, mm);
    } // print()
    
    
    byte editField(Adafruit_RGBLCDShield lcd, byte x, byte y, byte value, byte cap) {
      Serial.print("Starting Time -> editField(");
      Serial.print("lcd, ");
      Serial.print(x);
      Serial.print(",");
      Serial.print(y);
      Serial.print(",");
      Serial.print(value);
      Serial.print(",");
      Serial.print(cap);
      Serial.println(")");
      
      byte button = BUTT_NONE;
      do {
        if (button == BUTT_UP) {
          value = (value + 1) % cap;
        } else if (button == BUTT_DOWN) {
          if (value == 0) {
            value = cap;
          }
          value --;
        }
        lcd.setCursor(x, y);
        printField(lcd, value);
        lcd.setCursor(x, y);
        lcd.blink();
        button = get_button(10000);
      } while (button == BUTT_UP || 
               button == BUTT_DOWN);
      Serial.print("Finishing Time : returning ");
      Serial.println(value);
      return value;
    } // byte editField(Adafruit_RGBLCDShield lcd, byte x, byte y, byte value)


    void edit(Adafruit_RGBLCDShield lcd, byte x, byte y) {
      byte _hh, _mm;
      lcd.setCursor(x, y);
      print(lcd);
      _hh = editField(lcd, x, y, hh, 24);
      Serial.print("edit HH -> ");
      Serial.println(_hh);
      if (last_button() == BUTT_SET) {
        _mm = editField(lcd, x+3, y, mm, 60);
        Serial.print("edit MM -> ");
        Serial.println(_mm);
        if (last_button() == BUTT_SET) {
          set(_hh, _mm);
          lcd.setCursor(x, y);
          lcd.print("SAVED");
          delay(250);
          lcd.setCursor(x, y);
          print(lcd);
        }
      }
    } // edit(lcd, x, y)

};


#endif
