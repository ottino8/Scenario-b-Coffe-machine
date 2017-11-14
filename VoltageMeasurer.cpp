#include "Timer.h"
#include "Energia.h"
#include <msp430.h>
#include "VoltageMeasurer.h"

#define Voltage1 P1_3


VoltageMeasurer::VoltageMeasurer() {
  averageVoltage=0;
  flowVoltage = 0;
}
void VoltageMeasurer::measure(){
  Timer *timer= new Timer ();
  int firstVoltage=0;
  int cachedVoltage;
  (*timer).StartTimer();
  int currentVoltage;
  int currentDelta;
  (*timer).StartTimer();
  for (int i=0; i<800; i++){
    currentVoltage = analogRead(Voltage1);
    if(i=0){
      firstVoltage = currentVoltage;
    }
    averageVoltage += currentVoltage;
  }
  averageVoltage /= 800;
  Serial.println(averageVoltage);
  flowVoltage= (1000*((currentVoltage- firstVoltage)/((*timer).Lap())));
}

int VoltageMeasurer::getAverageVoltage() {
  return averageVoltage;
}

int VoltageMeasurer::getFlowVoltage() {
  return flowVoltage;
}

void VoltageMeasurer::Reset(){
  averageVoltage=0;
  flowVoltage=0;
}

VoltageMeasurer::~VoltageMeasurer (){}
