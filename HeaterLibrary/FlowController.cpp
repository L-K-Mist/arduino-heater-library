#include "Heater.h"
#include "Flasher.h"
#include "TempSensor.h"
#include <arduino.h>



enum FlowStates {
  filling,
  full,
  emptying,
  empty
} flowState_ = filling;  // Must end with a semicolon like a struct
//enum FlowStates flowState_ = filling;
//flowState_ = filling;


//Plastic Melting instantiation
//=============================

Flasher hotFlasher_PM(21); //Flasher is the ChildClass, Heater is the ParentClass. We instantiate a Flasher Object by giving it a name, a pin number and whether or not it works with a thermistor or a thermocouple object.
Flasher fanFlasher_PM(20);

Thermistor pm(A0);

TempSensor *tMistor_PM = &pm;



Heater plasticMelting("Plastic Melting", hotFlasher_PM, fanFlasher_PM, tMistor_PM);
//Notice above that the Flasher object named allocationObj_Flasher is inserted into Heater object named pm, by calling it's name!!!

//The result:  every time we need a new Heater Object for a particular zone, we just give it a new name and attributes.
//------------------end of Plastic Melting Object instantiation



//TODO uncomment after testing limited physical

// //Fluid Transfer instantiation
// //=============================
// Flasher hotFlasher_FT(49); //Flasher is the ChildClass, Heater is the ParentClass. We instantiate a Flasher Object by giving it a name, a pin number and whether or not it works with a thermistor or a thermocouple object.
// Flasher fanFlasher_FT(47);
//
//
// //from buggy example
// Thermistor ft(A1);
// TempSensor * tMistor_FT = &ft;
// //TODO Go through Temp Sensor to make sure that it more directly follows setup and loop other space
// Heater fluidTransfer("Fluid Transfer", hotFlasher_FT, fanFlasher_FT, tMistor_FT);
// //------------------end of Fluid Transfer Object instantiation




//Reaction Chamber instantiation
//=============================
Flasher hotFlasher_RC(49);
Flasher fanFlasher_RC(47);
Thermocouple rc(50,52,44,46,48);
TempSensor *tCouple_RC = &rc;
//TODO Go through Temp Sensor to make sure that it more directly follows setup and loop other space
Heater reactionChamber("Reaction Chamber", hotFlasher_RC, fanFlasher_RC, tCouple_RC);
//------------------end of Reaction Chamber instantiation

//TODO uncomment after testing limited physical
//
//
// //Reboiler Stack instantiation
// //=============================
// Flasher hotFlasher_RS(49); //Flasher is the ChildClass, Heater is the ParentClass. We instantiate a Flasher Object by giving it a name, a pin number and whether or not it works with a thermistor or a thermocouple object.
// Flasher fanFlasher_RS(47);
//
//
// //from buggy example
// Thermistor rs(A2);
// TempSensor * tMistor_RS = &rs;
// //TODO Go through Temp Sensor to make sure that it more directly follows setup and loop other space
// Heater reboilerStack("Reboiler Stack", hotFlasher_RS, fanFlasher_RS, tMistor_RS);
// //------------------end of Fluid Transfer Object instantiation

//    setFlowState();
void setFlowState(FlowStates flowState){
    flowState_ = flowState;
}
void flowStateControl();
void flowStateControl(){

  // Activities here....
  // Now do something based on what the shape is:
  switch(flowState_) {
    case filling:
      plasticMelting.setTargetTemp(260);
      //fluidTransfer.setTargetTemp(260);
      reactionChamber.setTargetTemp(260);
      //reboilerStack.setTargetTemp(300);
     break;
    case full:
      flowState_ = emptying;
      break;
    case emptying:
      plasticMelting.setTargetTemp(180);
      //fluidTransfer.setTargetTemp(40);
      reactionChamber.setTargetTemp(450);
      //reboilerStack.setTargetTemp(300);
      break;
    case empty:
      flowState_ = filling;
      break;
    default:
      Serial.println("Something wrong with Flow Controller!");
      break;
  }
}


void setup(){
  Serial.begin(9600);
  pinMode(14,OUTPUT);
  digitalWrite(14, LOW);
  plasticMelting.setup();
  reactionChamber.setup();
//  fluidTransfer.setup();
  plasticMelting.printInfo();
  plasticMelting.setMinMaxTemp(150, 320);
  reactionChamber.setMinMaxTemp(300, 500);

}

void loop(){

} ///:~]
