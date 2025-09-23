/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\m.puschmann                                      */
/*    Created:      Mon Sep 22 2025                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// PotentiometerA       pot           A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "string"

using namespace vex;
using namespace std;

void print_to_screen(){

  Brain.Screen.clearScreen(); //clear screen of previous values​

  Brain.Screen.setCursor(1, 1); //place cursor at the top left corner of BRAIN screen​

  Brain.Screen.print("Potentiomter = %d", PotentiometerA.angle(percent)); // print potentiometer value on BRAIN​

  Controller1.Screen.clearScreen(); //clear screen of previous values​

  Controller1.Screen.setCursor(1, 1); //place cursor at the top left corner of CONTROLLER screen​

  Controller1.Screen.print("Potentiomter = %d", PotentiometerA.angle(percent)); // print potentiometer value on CONTROLLER​

  wait(0.001, seconds); //wait 1 millisecond so you can see the value before restarting loop​

}



void set_shake(){
  int shaking = PotentiometerA.angle(percent)/10;
  int l = 10;
  while( shaking < l){
    Controller1.rumble(".");
    l= l - 1;
  }
  Controller1.rumble("-");
}

int main() 

{

// Initializing Robot Configuration. DO NOT REMOVE!​

vexcodeInit();

// Begin project code​

while(1){
  print_to_screen();
  set_shake();
}

}