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
    Serial.print(" yes, idling");
      _onTime = 1000;
      _offTime = 9000;
    break;

    case CRAWL:
    Serial.print(" yes, crawling");
    _onTime = 4000;
    _offTime = 6000;
    break;

    case TROT:
    Serial.print(" yes, trotting");
    _onTime = 5000;
    _offTime = 5000;
    break;

    case GALLOP:
    Serial.print(" yes, galloping");
    _onTime = 9000;
    _offTime = 1000;
    break;

    case SHUTDOWN:
    Serial.print(" yes, shutting down");
    digitalWrite(flasherPin_, LOW);
    break;
  }
}
