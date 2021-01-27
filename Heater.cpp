#include "Heater.h"
#include "Flasher.h"

#include "TempSensor.h"
#include <arduino.h>
//FLASHER SWITCH CASE STATES
//==================
#define IDLE      1
#define TROT      2
#define CRAWL     3
#define GALLOP    4
#define SHUTDOWN  5


Heater::Heater(String name, Flasher allocHot, Flasher allocFan, TempSensor* allocSense=NULL)
: name_ (name), hotAllocation (allocHot), fanAllocation(allocFan), senseAllocation (allocSense)
  {
  }

void Heater::printInfo(){
  Serial.print(name_);
  Serial.println(" Heater, is now in control of: ");
  hotAllocation.printFlasherAllocation();
  fanAllocation.printFlasherAllocation();
  }
void Heater::setup(){
  senseAllocation->setup();
  hotAllocation.setup();
  fanAllocation.setup();
  }

void Heater::loop(){
  senseAllocation->loop();
  hotAllocation.loop();
  fanAllocation.loop();
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
  double sensorReading = senseAllocation->getTempC();

  sensorMax_ = targetTemp_;
  // map the sensor range to a range of four options:
  int range = map(sensorReading, sensorMin_, sensorMax_, 0, 10);
  Serial.print("Range is: ");
  Serial.println(range); //just for debugging
  // do something different depending on the
  // range value:
  if (range > 0 && range < 7) { //always gallop when temp is below sensorMin
    hotAllocation.setState(GALLOP);
    Serial.println("flasher below Min Temp... Galloping");
  }
  switch (range) {
    case 0:    // temp is at sensorMin Celsius
      {
        hotAllocation.setState(GALLOP);
        Serial.println("flasher Galloping");
      }
      break;
    case 7:    // 70% towards Target
      {
        hotAllocation.setState(TROT);
        Serial.println("flasher Trotting");
      }

      break;
    case 8:    // 80% towards Target
      {
        hotAllocation.setState(CRAWL);
        Serial.println("flasher Crawling");
      }
      break;
    case 9:    // 90%
      {
        hotAllocation.setState(IDLE);
        fanAllocation.setState(GALLOP); //255 is Max spinning of fan.
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