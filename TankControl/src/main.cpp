/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\f.battistoni                                     */
/*    Created:      Thu Sep 18 2025                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftMotor            motor         1               
// RightMotor           motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {

  	// Initializing Robot Configuration. DO NOT REMOVE!​

  vexcodeInit();

  Brain.Screen.print("Tank Control Program Started");

	Controller1.Screen.clearScreen();

	while(true)

	{

	     //Drive Control​

      LeftMotor.spin(forward, Controller1.Axis3.position(), pct);

 	    RightMotor.spin(forward, Controller1.Axis2.position(), pct);

	    Controller1.Screen.setCursor(1, 1); Controller1.Screen.print("Left Axis 3 %5d",Controller1.Axis3.position());

	    Controller1.Screen.setCursor(2, 1); Controller1.Screen.print("Right Axis 2 %5d",Controller1.Axis2.position());

	     task::sleep(20);}

}