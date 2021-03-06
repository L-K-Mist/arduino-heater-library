#include "Heater.h"
#include "Flasher.h"

#include "TempSensor.h"
#include <Arduino.h>

enum FlashRate
{
  IDLE  = 1,
  TROT = 2,
  CRAWL = 3,
  GALLOP = 4,
  SHUTDOWN = 5
};


Heater::Heater(TempSensor* tempSensor, Flasher hotFlasher, Flasher coolFlasher)
: _tempSensor(tempSensor), _hotFlasher(hotFlasher), _coolFlasher(coolFlasher)
  {
  }

void Heater::setup(){
  _tempSensor->setup();
  _hotFlasher.setup();
  _coolFlasher.setup();
  }


void Heater::setMinMaxTemp(int sensorMin, int sensorMax)
{
    _sensorMin = sensorMin;
    _sensorMax = sensorMax;
}

void Heater::setTargetTemp(unsigned int targetTemp)
{
    _targetTemp = targetTemp;
}

double Heater::getTempC()
{
    return _tempSensor->getTempC();
}

unsigned char Heater::getHeaterState()
{
  return _hotFlasher._state;
}

unsigned char Heater::getCoolerState()
{
  return _coolFlasher._state;
}

void Heater::loop()
{
  _tempSensor->loop();
  _hotFlasher.loop();
  _coolFlasher.loop();
  this->controlFlasher();
}


  // the main State Machine
  //=======================
void Heater::controlFlasher()  {
  // read the sensor:
  double sensorReading = _tempSensor->getTempC();

  if(sensorReading >= _sensorMax || sensorReading >= _targetTemp) {
    Serial.println("Too Hot Dee! Cool off ekse2!");
    _coolFlasher.setState(FlashRate::GALLOP); 
    _hotFlasher.setState(FlashRate::SHUTDOWN);
    return;
  }

  int range = map(sensorReading, _sensorMin, _targetTemp, 0, 10);
  Serial.print("Range is: ");
  Serial.println(range); //just for debugging
  switch (range) {
    case -2 ... 3:    // temp is at sensorMin Celsius
      {
        _hotFlasher.setState(FlashRate::GALLOP);
        Serial.println("flasher Galloping");
      }
      break;
    case 4 ... 5:    
      {
        _hotFlasher.setState(FlashRate::TROT);
        Serial.println("flasher Trotting");
      }
      break;
    case 6:    
      {
        _hotFlasher.setState(FlashRate::CRAWL);
        Serial.println("flasher Crawling");
      }
      break;
    case 7 ... 9:    // 90%
      {
        _hotFlasher.setState(FlashRate::IDLE);
        _coolFlasher.setState(FlashRate::GALLOP); 
        Serial.println("flasher Idle and fan cooling");
      }
      break;
  }
  delay(1);        // delay in between reads for stability
}
