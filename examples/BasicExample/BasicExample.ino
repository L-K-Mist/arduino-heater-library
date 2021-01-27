//For now, and for Arduino IDE, make sure you have these libraries in the same folder as the ino file.
//TempSensor.h contains and uses its own versions of the standard Thermistor and Thermocouple libraries.

#include "Heater.h"
#include "Flasher.h"
#include "TempSensor.h"
#include "MyThermistor.h"
#include "MyThermocouple.h"

int thermoSCK = 8;
int thermoCS = 9;
int thermoSO = 10;

MyThermistor pm(A0); //input the analogue pin for your thermistor. This creates the Thermistor object for heaterOne to use.
MyThermocouple thermoC(thermoSCK, thermoCS, thermoSO);
TempSensor *tMistor_PM = &pm; 




void setup(){
  Serial.begin(115200);
  pm.setup();
  delay(500);
  thermoC.setup();
 }

void loop(){
  const double celsiusThermistor = tMistor_PM->getTempC();
  const float celsiusThermocouple = thermoC.getTempC();
  Serial.print("Thermistor: ");
  Serial.println(celsiusThermistor);
  Serial.print("Thermocouple: ");
  Serial.println(celsiusThermocouple);
  delay(2000);
}
