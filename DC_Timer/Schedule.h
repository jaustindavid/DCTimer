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
    Time on, off;
    
  public:
    Schedule() {
    } // constructor
    
    boolean isOn() {
    } // boolean isOn()
};


#endif
