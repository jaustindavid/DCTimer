/*
 * (CC BY-NC-SA 4.0) 
 * http://creativecommons.org/licenses/by-nc-sa/4.0/
 *
 */

#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <Arduino.h>
#include "Time.h"

class Schedule {
  private:
    byte id;
    Time* on, off;
    
  public:
    Schedule() {
      on = new Time(8, 00);
      /*
      on = .set(8, 00);
      off.set(16, 00);
      */
    } // constructor
    
    boolean isOn() {
    } // boolean isOn()
};


#endif
