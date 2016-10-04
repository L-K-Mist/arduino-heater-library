#include <arduino.h>
//#include "DeeThermistor.h"
//#include "Thermocouple.h"
//think of TempSensor header
#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H


class TempSensor {
  protected:

    //virtual ~TempSensor()=0;  // This is the destructor: declaration

  public:
    // TempSensor(int analoguePin):
    //   analoguePin_(analoguePin){};
    // TempSensor(int analoguePin, int VCC, int GND, int thermoCLK, int thermoCS, int thermoDO):
    // analoguePin_(analoguePin), vccPin(VCC), gndPin(GND), sclk(thermoCLK), cs(thermoCS), miso(thermoDO){};

    double zoneTempC;
    virtual double getTempC() =0;
    virtual void setup() =0;
    virtual void loop() =0;
    void setMisterPin (int analoguePin);
    void setCouplePins (int VCC, int GND, int thermoCLK, int thermoCS, int thermoDO);
    void printarea();
};

class Thermistor: public TempSensor {
  protected:
    int analoguePin_;
  public:
    Thermistor(int analoguePin)
        : analoguePin_(analoguePin) // Call Base(int) constructor with value id!
    {
    }
    double getTempC (void)
      {
        #define THERMISTORNOMINAL 80000
        // temp. for nominal resistance (almost always 25 C)
        #define TEMPERATURENOMINAL 25
        // how many samples to take and average, more takes longer
        // but is more 'smooth'
        #define NUMSAMPLES 10
        // The beta coefficient of the thermistor (usually 3000-4000)
        #define BCOEFFICIENT 3950
        // the value of the 'other' resistor
        #define SERIESRESISTOR 80000

        int samples[NUMSAMPLES];
          //Serial.print ("analogRead: ");
          //Serial.println (analogRead(analoguePin_));
          // take N samples in a row, with a slight delay
          uint8_t i;
          for (i=0; i< NUMSAMPLES; i++) {
          samples[i] = analogRead(analoguePin_);
          //delay(10);   //TODO ditch the delay with State Machine
          }
          // average all the samples out
          float average = 0;
          for (i=0; i< NUMSAMPLES; i++) {
             average += samples[i];
          }
          average /= NUMSAMPLES;

        //Serial.print("Average analog reading "); //TODO Move to Main
      //  Serial.println(average);                  //TODO Move to Main

          // convert the value to resistance
          average = 1023 / average - 1;
          average = SERIESRESISTOR / average;
          //Serial.print("Thermistor resistance ");
          //Serial.println(average);
          float steinhart;
          steinhart = average / THERMISTORNOMINAL;     // (R/Ro)
          steinhart = log(steinhart);                  // ln(R/Ro)
          steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
          steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
          steinhart = 1.0 / steinhart;                 // Invert
          steinhart -= 273.15;                         // convert to C

          Serial.print("Current Temperature ");
          Serial.print(steinhart);
          Serial.println(" *C");
          double tempC2 = steinhart;
          zoneTempC = tempC2;
          return zoneTempC;

      }
    void setup (){
      }
    void loop (){
      this->getTempC();
    }
      //{this->getTempC(); }// depricated
};

class Thermocouple: public TempSensor {
protected:
   int vccPin, gndPin, sclk, cs, miso;
  public:
    Thermocouple(int VCC, int GND, int thermoCLK, int thermoCS, int thermoDO)
        : vccPin(VCC), gndPin(GND), sclk(thermoCLK), cs(thermoCS), miso(thermoDO)
        //, TempSensor(GND), TempSensor(thermoCLK), TempSensor(thermoCS), TempSensor(thermoDO) // Call Base(int) constructor with value id!
    {
    }
    double getTempC (void)
      {
        Serial.print("Thermocouple tempC: ");
        uint16_t v;
        digitalWrite(cs, LOW);
        _delay_ms(1);
        v = spiread();
        v <<= 8;
        v |= spiread();
        digitalWrite(cs, HIGH);

        if (v & 0x4) {
          // uh oh, no thermocouple attached!
          return NAN;
          //return -100;
        }
        v >>= 3;
        Serial.println(v*0.25);
        return v*0.25;
      }

  byte spiread(void) {
    int i;
    byte d = 0;
    for (i=7; i>=0; i--){
      digitalWrite(sclk, LOW);
      _delay_ms(1);
      if (digitalRead(miso)) {
        //set the bit to 0 no matter what
        d |= (1 << i);
      }

      digitalWrite(sclk, HIGH);
      _delay_ms(1);
    }
    return d;
  }

  void setup (){
      //Exploring the possibilities of merging but first gonna try initializing
        pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
        pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);
        pinMode(cs, OUTPUT);
        pinMode(sclk, OUTPUT);
        pinMode(miso, INPUT);
        digitalWrite(cs, HIGH);

      }
  void loop (){
    this->getTempC();
  }
};
#endif
