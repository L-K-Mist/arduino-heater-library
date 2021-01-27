#ifndef MYTHERMISTOR_H
#define MYTHERMISTOR_H

#include <Arduino.h>
#include <Thermistor.h>
#include <NTC_Thermistor.h>
#include <SmoothThermistor.h>
#include "TempSensor.h"

#define REFERENCE_RESISTANCE   100000
#define NOMINAL_RESISTANCE     90000
#define NOMINAL_TEMPERATURE    25
#define B_VALUE                3950
/**
  Smoothing factor of a temperature value.
*/
#define SMOOTHING_FACTOR 5
Thermistor* thermistor;
class MyThermistor: public TempSensor {
  protected:
    int analoguePin_;
  public:
    MyThermistor(int analoguePin)
        : analoguePin_(analoguePin) // Call Base(int) constructor with value id!
    {
    }
    void setup (){
      Thermistor* originThermistor = new NTC_Thermistor(
        analoguePin_,
        REFERENCE_RESISTANCE,
        NOMINAL_RESISTANCE,
        NOMINAL_TEMPERATURE,
        B_VALUE
      );
      thermistor = new SmoothThermistor(originThermistor, SMOOTHING_FACTOR);
    }
    double getTempC (void)
      {
       thermistor->readCelsius();
      }
    void loop (){
      this->getTempC();
    }
};

#endif