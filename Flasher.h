#ifndef FLASHER_H
#define  FLASHER_H
//#include <TempSensor.h>
#include <arduino.h>

// //FLASHER SWITCH CASE STATES
// //==================
// #define IDLE      1
// #define TROT      2
// #define CRAWL     3
// #define GALLOP    4
// #define SHUTDOWN  5
//

class Flasher
{
public:
  Flasher(int flasherPin);
  Flasher(int flasherPin, long on, long off);
  void printFlasherAllocation();
  void setup();
  void loop();


  void update();
  void setTimes(long setOn, long setOff);
  void setState(unsigned char state);
  // Constructor - creates a Flasher
  // and initializes the membe r variables and state


protected:
private:
  int flasherPin_;
  long _onTime;     // milliseconds of on-time
  long _offTime;    // milliseconds of off-time
  unsigned char _state;
  // These maintain the current state
  int _digiState;                //ledState used to set the LED
  unsigned long _previousMillis; // will store last time LED was updated

};

#endif
