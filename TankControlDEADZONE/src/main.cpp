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

	double leftControl = 0, rightControl = 0, leftPower = 0, rightPower=0;

  Brain.Screen.print("Tank Control Program Started");

	Controller1.Screen.clearScreen();

	while(true) 

	{

       		leftControl = Controller1.Axis3.position();

       		rightControl = Controller1.Axis2.position();

       		if (fabs(leftControl)<20)

			leftPower = 0;

		else

			leftPower = leftControl;

		if (fabs(rightControl)<20)

			rightPower = 0;

		else

			rightPower = rightControl;



    LeftMotor.spin(forward, leftPower, pct);
   	RightMotor.spin(forward, rightPower, pct);


    Controller1.Screen.setCursor(1, 1); Controller1.Screen.print("Left  = %3.0f Pwr = %3.0f",leftControl, leftPower);

   	Controller1.Screen.setCursor(2, 1); Controller1.Screen.print("Right = %3.0f Pwr = %3.0f",rightControl, rightPower);
    
    task::sleep(20);}

	} 
