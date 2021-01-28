#include "Heater.h"
#include "Flasher.h"
#include "TempSensor.h"
#include "MyThermistor.h"
#include "MyThermocouple.h"
#include <AsyncDelay.h>


int thermoSCK = 8;
int thermoCS = 9;
int thermoSO = 10;

MyThermistor pm(A0); //input the analogue pin for your thermistor. This creates the Thermistor object for heaterOne to use.
MyThermocouple thermoC(thermoSCK, thermoCS, thermoSO);
// A TempSensor can be either a MyThermistor or a MyThermocouple
// The TempSensor class behaves more like an interface, making sure that 
// either option exposes a getTempC function.
// In this case it is inheritance: A TempSensor *is a* Thermocouple or *is a* Thermistor.

TempSensor *thermistorMain = &pm; 
TempSensor *tCouple = &thermoC;

Flasher hotFlasher(LED_BUILTIN);
Flasher fanFlasher(12);

// Now the heater receives the TempSensor, hotFlasher (usually going to a relay for an element), and coolFlasher (usually going to a fan/radiator)
// This being an example of composition, and a hardware version of dependency injection.
// The user still instantiates these dependancies, but gives them to the Heater to control.
Heater mainHeater(thermistorMain, hotFlasher, fanFlasher);

enum FlashRate
{
  IDLE  = 1,     // Long off short on.
  TROT = 2,
  CRAWL = 3,
  GALLOP = 4,    // Long on short off.
  SHUTDOWN = 5
};
AsyncDelay delay_6s;
AsyncDelay delay_1s;

void setup(){
  delay_6s.start(6000, AsyncDelay::MILLIS);
  delay_1s.start(1000, AsyncDelay::MILLIS);
  Serial.begin(115200);
  pm.setup();
  delay(500);
  thermoC.setup();
  mainHeater.setup();
  mainHeater.setMinMaxTemp(25, 35);
  mainHeater.setTargetTemp(32);
 }

void loop(){
    if (delay_6s.isExpired()) {
    Serial.print("     6s delay millis=");
    Serial.println(millis());
    const double celsiusThermistor = thermistorMain->getTempC();
    const double celsiusThermocouple = tCouple->getTempC();
    Serial.print("Thermistor: ");
    Serial.println(celsiusThermistor);
    Serial.print("Thermocouple: ");
    Serial.println(celsiusThermocouple); 
    delay_6s.repeat();
  }
  if (delay_1s.isExpired()) {
    mainHeater.loop();
    delay_1s.repeat();
  }
}
