/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\f.battistoni                                     */
/*    Created:      Wed Sep 17 2025                                           */
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

int main(){

  // Initializing Robot Configuration. DO NOT REMOVE!​

  vexcodeInit();

  Brain.Screen.print("Arcade Left Joystick Program Started");

  Controller1.Screen.clearScreen();

  while (true) {
    LeftMotor.spin(forward, (Controller1.Axis3.value() + Controller1.Axis4.value())/2, percent);   //(Axis3+Axis4)/2;​

    RightMotor.spin(forward, (Controller1.Axis3.value() - Controller1.Axis4.value())/2, percent); //(Axis3-Axis4)/2;​

    Controller1.Screen.setCursor(1, 1);

    Controller1.Screen.print("Left Pwr = %3.0f",(Controller1.Axis3.value() + Controller1.Axis4.value())/2);

    RightMotor.spin(forward, rightPower, pct);

    Controller1.Screen.setCursor(2, 1); 

    Controller1.Screen.print("Right Pwr = %3.0f", (Controller1.Axis3.value() - Controller1.Axis4.value())/2);

    task::sleep(20);

  }