#include "Heater.h"
#include "Flasher.h"

#include "TempSensor.h"
#include <Arduino.h>
//FLASHER SWITCH CASE STATES
//==================
#define IDLE      1
#define TROT      2
#define CRAWL     3
#define GALLOP    4
#define SHUTDOWN  5


Heater::Heater(TempSensor* tempSensor = NULL, Flasher hotFlasher, Flasher coolFlasher)
: _tempSensor(tempSensor), _hotFlasher(hotFlasher), _coolFlasher(coolFlasher)
  {
  }

void Heater::setup(){
  _tempSensor->setup();
  _hotFlasher.setup();
  _coolFlasher.setup();
  }

void Heater::loop(){
  _tempSensor->loop();
  _hotFlasher.loop();
  _coolFlasher.loop();
  //this->setTargetTemp(44);
  }

//bring to the top

void Heater::setMinMaxTemp(int sensorMin, int sensorMax){
    sensorMin_ = sensorMin;
    sensorMax_ = sensorMax;
  }


void Heater::setTargetTemp(unsigned int targetTemp){
    targetTemp_ = targetTemp;
  }

  // the main State Machine
  //=======================
void Heater::controlFlasher()  {
  // read the sensor:
  double sensorReading = _tempSensor->getTempC();

  sensorMax_ = targetTemp_;
  // map the sensor range to a range of four options:
  int range = map(sensorReading, sensorMin_, sensorMax_, 0, 10);
  Serial.print("Range is: ");
  Serial.println(range); //just for debugging
  // do something different depending on the
  // range value:
  if (range > 0 && range < 7) { //always gallop when temp is below sensorMin
    _hotFlasher.setState(GALLOP);
    Serial.println("flasher below Min Temp... Galloping");
  }
  switch (range) {
    case 0:    // temp is at sensorMin Celsius
      {
        _hotFlasher.setState(GALLOP);
        Serial.println("flasher Galloping");
      }
      break;
    case 7:    // 70% towards Target
      {
        _hotFlasher.setState(TROT);
        Serial.println("flasher Trotting");
      }

      break;
    case 8:    // 80% towards Target
      {
        _hotFlasher.setState(CRAWL);
        Serial.println("flasher Crawling");
      }
      break;
    case 9:    // 90%
      {
        _hotFlasher.setState(IDLE);
        _coolFlasher.setState(GALLOP); //255 is Max spinning of fan.
        Serial.println("flasher Idle and fan cooling");
      }
      default:
      {
        Serial.print("Something Wrong with Temp FSM.");
      }
      break;
  }
  delay(1);        // delay in between reads for stability
}
