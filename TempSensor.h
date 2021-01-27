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
