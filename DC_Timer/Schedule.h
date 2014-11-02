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
    
  public:
    Time *on, *off;
 
    Schedule() {
      on  = new Time(8, 00);
      off = new Time(16,00);
    } // constructor
    
    boolean isOn() {
    } // boolean isOn()
    
    
};


#endif
