#ifndef MYTHERMOCOUPLE_H
#define MYTHERMOCOUPLE_H

#include <Arduino.h>

#include "TempSensor.h"
#include "max6675.h"

class MyThermocouple: public TempSensor {
  protected:
    int _thermoSCK;
    int _thermoCS;
    int _thermoSO;
    MAX6675 * thermocouple;
  public:
    MyThermocouple(int thermoSCK, int thermoCS, int thermoSO)
        : _thermoSCK(thermoSCK), _thermoCS(thermoCS), _thermoSO(thermoSO)
    {
    }
    void setup (){
      thermocouple = new MAX6675 (_thermoSCK, _thermoCS, _thermoSO);
    }
    double getTempC (void)
    {
      return (double)thermocouple->readCelsius();
    }
    void loop (){
      this->getTempC();
    }
};

#endif