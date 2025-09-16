/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\m.puschmann                                      */
/*    Created:      Fri Sep 12 2025                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotor            motor         1               
// RightMotor           motor         2               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main(){

  	// Initializing Robot Configuration. DO NOT REMOVE!​

  vexcodeInit();

  double leftControl = 0, rightControl = 0, leftPower = 0, rightPower=0, li = 0, ri = 0;

  Brain.Screen.print("Our Control Program Started");

	Controller1.Screen.clearScreen();

	while(true) {

	  //Saving the joystick values from the​

    leftControl = Controller1.Axis3.position();

    rightControl = Controller1.Axis2.position();

    leftPower = leftControl;

    rightPower = rightControl;

    /*
    if(leftControl > 0){
      li = li + 0.0001;
    }
    else{
      li = 0;
    }

    if(rightControl > 0){
      ri = ri + 0.0001;
    }
    else{
      ri = 0;
    }*/

    LeftMotor.spin(forward, leftPower + li, pct);

  	RightMotor.spin(forward, rightPower +ri, pct);


   Controller1.Screen.setCursor(1, 1); Controller1.Screen.print("Left  = %3.0f Pwr = %3.0f",leftControl, leftPower);

	 Controller1.Screen.setCursor(2, 1); Controller1.Screen.print("Right = %3.0f Pwr = %3.0f",rightControl, rightPower);

	task::sleep(20);
  }
}