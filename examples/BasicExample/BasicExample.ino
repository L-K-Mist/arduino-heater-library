//For now, and for Arduino IDE, make sure you have these libraries in the same folder as the ino file.
//TempSensor.h contains and uses its own versions of the standard Thermistor and Thermocouple libraries.

#include "Heater.h"
#include "Flasher.h"
#include "TempSensor.h"
#include "MyThermistor.h"
#include "MyThermocouple.h"
#include <AsyncDelay.h>
AsyncDelay delay_6s;


int thermoSCK = 8;
int thermoCS = 9;
int thermoSO = 10;

MyThermistor pm(A0); //input the analogue pin for your thermistor. This creates the Thermistor object for heaterOne to use.
MyThermocouple thermoC(thermoSCK, thermoCS, thermoSO);
// A TempSensor can be either a MyThermistor or a MyThermocouple
// The TempSensor class behaves more like an interface, making sure that 
// either option exposes a getTempC function.
// In this case it is inheritance: A TempSensor *is a* Thermocouple or a Thermistor.
// 
TempSensor *tMistor_PM = &pm; 
TempSensor *tCouple = &thermoC;

Flasher hotFlasher(LED_BUILTIN);


void setup(){
  delay_6s.start(6000, AsyncDelay::MILLIS);
  Serial.begin(115200);
  pm.setup();
  delay(500);
  thermoC.setup();

  hotFlasher.setup();
  hotFlasher.setState(3);
 }

void loop(){
    if (delay_6s.isExpired()) {
    Serial.print("     6s delay millis=");
    Serial.println(millis());
    const double celsiusThermistor = tMistor_PM->getTempC();
    const float celsiusThermocouple = tCouple->getTempC();
    Serial.print("Thermistor: ");
    Serial.println(celsiusThermistor);
    Serial.print("Thermocouple: ");
    Serial.println(celsiusThermocouple); 
    delay_6s.repeat();
  }
  hotFlasher.loop();
}
