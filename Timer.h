#include <msp430.h>
#include "Energia.h"

#ifndef Timer_h
#define Timer_h

class Timer {

  private:
    unsigned long startTime;
    unsigned long endTime;
  
  public:
    Timer();
    void StartTimer();
    
    unsigned long Lap();

    ~Timer();
};

#endif
