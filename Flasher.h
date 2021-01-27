#ifndef FLASHER_H
#define  FLASHER_H
#include <Arduino.h>

class Flasher
{
  private:
    int flasherPin_;
    long _onTime;     // milliseconds of on-time
    long _offTime;    // milliseconds of off-time
    unsigned char _state;
    int _pinState;                //ledState used to set the LED
    unsigned long _previousMillis; // will store last time LED was updated
  public:
    Flasher(int flasherPin);
    void setup();
    void loop();
    void setState(unsigned char state);
};

#endif
