#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

class TempSensor {
  protected:
  public:
    double zoneTempC;
    virtual double getTempC() =0;
    virtual void setup() =0;
    virtual void loop() =0;
};

#endif
