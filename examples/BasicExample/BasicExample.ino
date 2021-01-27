//For now, and for Arduino IDE, make sure you have these libraries in the same folder as the ino file.
//TempSensor.h contains and uses its own versions of the standard Thermistor and Thermocouple libraries.

#include "Heater.h"
#include "Flasher.h"
#include "TempSensor.h"
#include "MyThermistor.h"

MyThermistor pm(A0); //input the analogue pin for your thermistor. This creates the Thermistor object for heaterOne to use.
TempSensor *tMistor_PM = &pm; 


void setup(){
  Serial.begin(115200);
  pm.setup();

 }

void loop(){
  const double celsius = tMistor_PM->getTempC();
  Serial.print("Temperature: ");
  Serial.println(celsius);
  delay(2000);
}
