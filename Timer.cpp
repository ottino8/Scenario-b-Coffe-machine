#include "Timer.h"
#include <msp430.h>
#include "Energia.h"

Timer::Timer() { }
void Timer::StartTimer() {
  startTime = millis();
}

unsigned long Timer::Lap() {
  endTime = millis();
  return endTime - startTime;
}


