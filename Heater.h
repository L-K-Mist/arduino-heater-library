#ifndef HEATER_H
#define  HEATER_H
#include "Flasher.h"
#include "TempSensor.h"
#include <Arduino.h>

class Heater
{
public:
  Heater(TempSensor* tempSensor, Flasher hotFlasher, Flasher coolFlasher);
  void setTargetTemp(unsigned int targetTemp);
  void setMinMaxTemp(int sensorMin, int sensorMax);
  void controlFlasher();
  void setup();
  void loop();
  double zoneTempC = 0;
protected:
  int _sensorMin;
  int _sensorMax;
  unsigned int _targetTemp;
  Flasher _hotFlasher;
  Flasher _coolFlasher;
  TempSensor* _tempSensor;
};

#endif
