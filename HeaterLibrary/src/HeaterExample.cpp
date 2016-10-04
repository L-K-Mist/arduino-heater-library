#include "Heater.h"
#include "Flasher.h"
#include "TempSensor.h"
#include <arduino.h>

//heaterOne instantiation - This is an example using a thermistor - check heaterTwo if you want to rather use a Thermocouple.
//=============================
Flasher hotFlasher_PM(21); //input the digital pin that you want to flash some kind of heater element with eg. the pin attached to an SSR Relay, attached to a stove.
Flasher fanFlasher_PM(20); //input the digital pin that you want to use for cooling.  When the Target Temp is close or surpassed this pin goes HIGH to prevent over-shooting.
Thermistor pm(A0); //input the analogue pin for your thermistor. This creates the Thermistor object for heaterOne to use.
TempSensor *tMistor_PM = &pm; //to allow you to choose whether you want your heater to use a thermistor or thermocouple we need some pointers. In the next line we put tMistor_PM into heaterOne.
Heater heaterOne("Plastic Melting", hotFlasher_PM, fanFlasher_PM, tMistor_PM);
//Notice above that the Flasher object named allocationObj_Flasher is inserted into Heater object named pm, by calling it's name!!!

//The result:  every time we need a new Heater Object for a particular zone, we just give it a new name and attributes.
//------------------end of heaterOne instantiation

//heaterTwo instantiation - This is an example using a thermocouple. Perhaps developers could help give other options for TempSensing in the heater?
//=============================
Flasher hotFlasher_RC(19);
Flasher fanFlasher_RC(18);
Thermocouple rc(50,52,44,46,48); //input your thermocouple pins as follows: vccPin, gndPin, sclk, cs, miso - You can put all your pins in a line. The thermocouple code will make any given digital pin into gnd and vcc.

TempSensor *tCouple_RC = &rc; //notice that this time we are able to put a thermocouple object into heaterTwo; instead of a thermistor as in heaterOne.
Heater heaterTwo("Reaction Chamber", hotFlasher_RC, fanFlasher_RC, tCouple_RC);
//------------------end of Reaction Chamber instantiation


void setup(){
  Serial.begin(9600);
  pinMode(14,OUTPUT); //in my case this code is just here to make pin 14 into a groundpin
  digitalWrite(14, LOW); //in my case this code is just here to make pin 14 into a groundpin

  heaterOne.setup(); //sets up the required pins
  heaterOne.printInfo(); // optional (more for debugging)
  heaterOne.setMinMaxTemp(5, 25); // set up the operating range for the heater. Think room-temp to Max operating temp.
  heaterOne.setTargetTemp(20); // set target temp in C. Probably the most important function. In my application this function will be used repeatedly to set new target temps for each heater.

  heaterTwo.setup();
  heaterTwo.printInfo(); // optional (more for debugging)
  heaterTwo.setMinMaxTemp(5, 8);
  heaterTwo.setTargetTemp(23);
 }

void loop(){
  heaterOne.loop();
  delay(1000);
  heaterTwo.loop();
  heaterOne.controlFlasher(); //This initiates the Heater Finite State Machine, so that the flash-rate at the digital pin decreases the closer we get to targetTemp.
  delay(1000);
  heaterTwo.controlFlasher();
  delay(1000);
}
