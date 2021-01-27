#include <Arduino.h>
#include "Flasher.h"
//#include <Heater.h>
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

Flasher::Flasher(int flasherPin, long on, long off) 
  {
   flasherPin_ = flasherPin;
   _onTime = on;
   _offTime = off;
   _digiState = LOW;
   _previousMillis = 0;
    }

void Flasher::printFlasherAllocation(){
  Serial.print("Flasher on pin ");
  Serial.print(flasherPin_);
  Serial.println(".");
  }

void Flasher::setup(){
  pinMode(flasherPin_, OUTPUT);
  }

void Flasher::loop(){
  this->update();

  }

  void Flasher::update() {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();

    if((_digiState == HIGH) && (currentMillis - _previousMillis >= _onTime))
    {
      _digiState = LOW;  // Turn it off
      _previousMillis = currentMillis;  // Remember the time
      digitalWrite(flasherPin_, _digiState);  // Update the actual LED
    }
    else if ((_digiState == LOW) && (currentMillis - _previousMillis >= _offTime))
    {
      _digiState = HIGH;  // turn it on
      _previousMillis = currentMillis;   // Remember the time
      digitalWrite(flasherPin_, _digiState);	  // Update the actual LED
    }
  }

  // void Flasher::setTimes(long setOn, long setOff) {
  //   _onTime = setOn;
  //   _offTime = setOff;
  // }

  void Flasher::setState(unsigned char state)
  {

//TODO elevate states to functions
    _state = state; 

    switch(_state)
    {
      case IDLE:
      Serial.print(" yes, idling");
        _onTime = 1000;
        _offTime = 16000;
      break;

      case CRAWL:
      Serial.print(" yes, crawling");
      _onTime = 2000;
      _offTime = 8000;
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
