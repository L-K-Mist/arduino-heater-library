#include <Arduino.h>
#include "Flasher.h"

//FLASHER SWITCH CASE STATES
//==================
#define IDLE      1
#define TROT      2
#define CRAWL     3
#define GALLOP    4
#define SHUTDOWN  5

Flasher::Flasher(int flasherPin)
{
  flasherPin_ = flasherPin;
}

void Flasher::setup()
{
  pinMode(flasherPin_, OUTPUT);
}

void Flasher::loop()
{
  // check to see if it's time to change the state of the LED
  unsigned long currentMillis = millis();

  if((_pinState == HIGH) && (currentMillis - _previousMillis >= _onTime))
  {
    _pinState = LOW;  // Turn it off
    _previousMillis = currentMillis;  // Remember the time
    digitalWrite(flasherPin_, _pinState);  // Update the actual LED
  }
  else if ((_pinState == LOW) && (currentMillis - _previousMillis >= _offTime))
  {
    _pinState = HIGH;  // turn it on
    _previousMillis = currentMillis;   // Remember the time
    digitalWrite(flasherPin_, _pinState);	  // Update the actual LED
  }
}

void Flasher::setState(unsigned char state)
{
  _state = state; 
  switch(_state)
  {
    case IDLE:
      _onTime = 1500;
      _offTime = 8000;
    break;

    case CRAWL:
    _onTime = 4000;
    _offTime = 6000;
    break;

    case TROT:
    _onTime = 5000;
    _offTime = 5000;
    break;

    case GALLOP:
    digitalWrite(flasherPin_, HIGH);
    break;

    case SHUTDOWN:
    digitalWrite(flasherPin_, LOW);
    break;
  }
}
