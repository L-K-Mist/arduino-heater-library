//For now, and for Arduino IDE, make sure you have these libraries in the same folder as the ino file.
//TempSensor.h contains and uses its own versions of the standard Thermistor and Thermocouple libraries.

#include "Heater.h"
#include "Flasher.h"
#include "TempSensor.h"
//#include <arduino.h> //My IDE required this. Don't think arduino ide needs it.

//heaterOne instantiation - This is an example using a thermistor - check heaterTwo if you want to rather use a Thermocouple.
//=============================
Flasher hotFlasher_PM(21); //input the digital pin that you want to flash some kind of heater element with eg. the pin attached to an SSR Relay, attached to a stove.
Flasher fanFlasher_PM(20); //input the digital pin that you want to use for cooling.  When the Target Temp is approaching or surpassed, this pin goes HIGH to prevent over-shooting.
Thermistor pm(A0); //input the analogue pin for your thermistor. This creates the Thermistor object for heaterOne to use.
TempSensor *tMistor_PM = &pm; //Sorry for pointers in the Sourcefile. To allow you to choose whether you want your heater to use a thermistor or thermocouple we need some pointers. In the next line we put tMistor_PM into heaterOne.
Heater heaterOne("Heater One", hotFlasher_PM, fanFlasher_PM, tMistor_PM);
//Notice above that the Flasher object named allocationObj_Flasher is inserted into Heater object named pm, by calling it's name.

//The result:  every time we need a new Heater Object for a particular zone, we just give it a new name and attributes.
//------------------end of heaterOne instantiation

//heaterTwo instantiation - This is an example using a thermocouple. Perhaps developers could help give other options for TempSensing in tempSensor.h 
//=============================
Flasher hotFlasher_RC(19);
Flasher fanFlasher_RC(18);
Thermocouple rc(50,52,44,46,48); //input your thermocouple pins as follows: vccPin, gndPin, sclk, cs, miso - physically you can put all your pins in a line. The thermocouple code will make any given digital pin into gnd and vcc.

TempSensor *tCouple_RC = &rc; //notice that this time we are able to put a thermocouple object into heaterTwo; instead of a thermistor as in heaterOne.
Heater heaterTwo("Heater Two", hotFlasher_RC, fanFlasher_RC, tCouple_RC);
//------------------end of heaterTwo instantiation

//If you require more heaters just copy and tweak one of the above instantiation examples.


void setup(){
  Serial.begin(9600);
  pinMode(14,OUTPUT); digitalWrite(14, LOW); //in my case this code is just here to make pin 14 into a groundpin

  heaterOne.setup(); //sets up the required pins
  heaterOne.printInfo(); // optional (more for debugging)
  heaterOne.setMinMaxTemp(5, 45); // set up the operating range for the heater. Think room-temp to Max operating temp. Here it is set to 45 deg C for testing with a coffee-cup
  heaterOne.setTargetTemp(43); // set target temp in C. This is the Heater Object's most important function. In my application this function will be used repeatedly to set new target temps for each heater, according to the Emptying or Filling state of the different Heat Zones.

  heaterTwo.setup();
  heaterTwo.printInfo(); // optional (more for debugging)
  heaterTwo.setMinMaxTemp(20, 60);
  heaterTwo.setTargetTemp(54);
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
