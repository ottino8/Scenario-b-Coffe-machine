#include <msp430.h>
#include "LCDdriver.h"
#include "Timer.h"
#include "Energia.h"
#include "VoltageMeasurer.h"

unsigned long TimeToPrint;
unsigned long TimeStopped=0;
int cupVoltage;
int voltage;
int voltageAverage;
int voltageRate;
boolean FirstMeasure=true;
boolean FirstCycle=true;
int Voltage=P1_0;
int greenLED=P1_1;
int redLED=P1_2;
int yellowLED=P1_3;
int whiteLED=P1_4;
int seconds;
int minutes=0;
LCD *mylcd = new LCD(0x3E);
Timer *PourTimer;
Timer *StopTimer;
VoltageMeasurer *firstMeasurer;
VoltageMeasurer *secondMeasurer;
VoltageMeasurer *normalMeasurer;
VoltageMeasurer *stoppedMeasurer;

void setup() {
  /*Timer *t = new Timer();
  Timer *timer2 = new Timer();
  (*t).StartTimer();
  delay(3000);
  unsigned long timerValue = (*t).StopTimer();
  delete t;*/
  Serial.begin(9600);
  Serial.print("entered");
  pinMode(Voltage, INPUT);
   PourTimer = new Timer();
   StopTimer = new Timer();
   *firstMeasurer = new VoltageMeasurer();
   *secondMeasurer = new VoltageMeasurer();
   *normalMeasurer = new VoltageMeasurer();
   *stoppedMeasurer = new VoltageMeasurer();
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(whiteLED, OUTPUT);  
  (*mylcd).init();
  (*mylcd).backLight(500);
  (*mylcd).writeString("Time Weight Rate");
  (*mylcd).down();
  (*mylcd).writeString("");
  (*mylcd).blinkOff();
  (*mylcd).cursorOff();
}

void loop() {
  /*while(FirstMeasure==true){
    (*firstMeasurer).measure();
  }*/
  digitalWrite(yellowLED, LOW);
  if(FirstMeasure==true){
    int firstValue = 0;
    digitalWrite(redLED, HIGH);
    while (firstValue == 0) {
      (*firstMeasurer).measure();
      firstValue = (*firstMeasurer).getFlowVoltage();
      Serial.print("firstValue is:");
    Serial.println(firstValue);
      (*firstMeasurer).Reset();
    }
    digitalWrite(redLED, LOW);
    FirstMeasure=false;
  }
  if(FirstCycle==true){ 
  int secondValue =0;
  digitalWrite(whiteLED, HIGH);
  while(secondValue==0){
    (*secondMeasurer).measure();
    cupVoltage=(*secondMeasurer).getAverageVoltage();
    secondValue=(*secondMeasurer).getFlowVoltage();
    (*secondMeasurer).Reset();
  }
    (*PourTimer).StartTimer();
    voltageRate=1;
  }
    digitalWrite(whiteLED, LOW);
    digitalWrite(greenLED, HIGH);
  while(voltageRate!=0){
    (*normalMeasurer).measure();
    voltage=((*normalMeasurer).getAverageVoltage() - cupVoltage);
    voltageRate=(*normalMeasurer).getFlowVoltage();
    TimeToPrint = (*PourTimer).Lap()- TimeStopped;
    seconds= TimeToPrint/1000 - minutes*60;
    if(seconds==60){
      minutes++;
    }
    Serial.print("Time is:");
    Serial.println(minutes);
    Serial.println(seconds);
    Serial.print("Weight is:");
    Serial.println(voltage);
    Serial.print("Flow is");
    Serial.println(voltageRate);   
  }
  TimeToPrint = (*PourTimer).Lap();
  (*StopTimer).StartTimer();
  int stoppedRate=0;
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, HIGH);
  while(stoppedRate == 0){
    (*stoppedMeasurer).measure();
    stoppedRate=(*stoppedMeasurer).getFlowVoltage();
    TimeStopped=(*StopTimer).Lap();
    if(TimeStopped>=45000){
      return;
    }
  }  
 }
  

