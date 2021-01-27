#ifndef HEATER_H
#define  HEATER_H
#include "Flasher.h"
#include "TempSensor.h"
#include <Arduino.h>


class Heater
{
public:
  Heater(String name, Flasher allocHot, Flasher allocFan, TempSensor* allocSense);
  void setTargetTemp(unsigned int targetTemp);
  void setMinMaxTemp(int sensorMin, int sensorMax);
  void controlFlasher();
  void printInfo();
  void setup();
  void loop();
  double zoneTempC = 0;
protected:
  int sensorMin_;
  int sensorMax_;
  unsigned int targetTemp_;
  String name_;
  Flasher hotAllocation;
  Flasher fanAllocation;
  TempSensor* senseAllocation;
};

#endif
