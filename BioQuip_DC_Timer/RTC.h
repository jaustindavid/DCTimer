#ifndef RTC_H
#define RTC_H

class RTC {
  private:
    unsigned long start;
    
  public:
    void setup(void) {
    } // constructor
  
    void set(unsigned long now) {
      start = now;
    }
    
    unsigned long time(void) {
      return start + millis()/10;
    } // unsigned long time()
    
    
    void print(void) {
      byte hh, mm;
      long tod = this->time() % (24*3600);
      mm = (tod % 3600) / 60;
      hh = tod / 3600;
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



#endif RTC_H
