/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\f.battistoni                                     */
/*    Created:      Wed Sep 24 2025                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// NorthMotor           motor         1               
// SouthMotor           motor         2               
// Controller1          controller                    
// EastMotor            motor         3               
// WestMotor            motor         4               
// Gyroscope            inertial      5               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// Axis 4: North-South Motor;
// Axis 3: East-West Motor;


double leftControl = 0, rightControl = 0, leftPower = 0, rightPower = 0;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Gyroscope.calibrate();
  double original_heading = Gyroscope.heading(degrees);
  const double turnVelocity = 10.0; // Speed of the turn
  const double robot_radius = 1.0;
  const double wheel_radius = 0.5;

  while(true) {

    // Button A will reorient the Robot
    if (Controller1.ButtonA.pressing()) {
      double delta = Gyroscope.heading(degrees) - original_heading; // We have to rotate around by "delta" degrees.degrees
      double distance_to_cover = delta/360 * 2 * 3.141 * robot_radius;
      double rotate = distance_to_cover / wheel_radius;
      double delta_time = rotate / turnVelocity;
      Brain.Timer.clear();
      while(Brain.Timer.time() < delta_time) {
          NorthMotor.spin(forward, rotate, dps);
          SouthMotor.spin(forward, rotate, dps);
          WestMotor.spin(forward, rotate, dps);
          EastMotor.spin(forward, rotate, dps);
      }

    }
    
    leftControl = Controller1.Axis3.position();
    rightControl = Controller1.Axis4.position();

    leftPower = (pow(leftControl, 3) / pow(100, 2) + leftControl) / 2;   // y = (x^3 / 100^2 + x) / 2
    rightPower = (pow(rightControl, 3) / pow(100, 2) + rightControl) / 2;

    NorthMotor.spin(forward, (Controller1.Axis3.value() / 2), percent);
    SouthMotor.spin(forward, (Controller1.Axis3.value() / 2), percent);
    EastMotor.spin(forward, (Controller1.Axis4.value() / 2), percent);
    WestMotor.spin(forward, (Controller1.Axis4.value() / 2), percent);

    task::sleep(20);
  }
}
