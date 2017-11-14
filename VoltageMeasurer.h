#include "Timer.h"
#include "Energia.h"
#include <msp430.h>

#ifndef VoltageMeasurer_h
#define VoltageMeasurer_h

class VoltageMeasurer {
  private:
    float averageVoltage;
    float flowVoltage;

  public:
    VoltageMeasurer();
    void measure();
    
    int getAverageVoltage() ;
    
    int getFlowVoltage();

    void Reset();

    ~VoltageMeasurer ();
};

#endif