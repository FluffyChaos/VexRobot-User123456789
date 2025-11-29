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
// RingMotor            motor         6               
// LineTracker          line          H               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
#include <cmath>
#include <chrono>

competition Competition;

// Axis 4: North-South Motor;
// Axis 3: East-West Motor;


double leftControl = 0, rightControl = 0, leftPower = 0, rightPower = 0, spinControl = 0;
double x = 0, y = 0;
double ringControl = 0;
#define PI 3.14159265358979323846
double maxSpeed = 100;
RingMotor.resetPosition();
bool toggle = false;

// start added variables
double distance_x = 100;
double distance_y = 100;
double angle = 0; // deg
double delta_angle = 0;
bool allignement_toggle = false;
bool angle_toggle = false;
double k = 2; // scaling factor
// end added variables

void pre_auton(void) {

}

void autonomous(void) {
  
  while (LineTracker.reflectivity() < 10) {
    leftControl = 0;
    rightControl = maxSpeed / 2;

    leftPower = (pow(leftControl, 3) / pow(100, 2) + leftControl) / 3;   // y = (x^3 / 100^2 + x) / 2
    rightPower = (pow(rightControl, 3) / pow(100, 2) + rightControl) / 3;

    NorthMotor.spin(forward, leftPower + (spinControl / 2), percent);
    SouthMotor.spin(forward, leftPower - (spinControl / 2), percent);
    EastMotor.spin(forward, rightPower + (spinControl / 2), percent);
    WestMotor.spin(forward, rightPower - (spinControl / 2), percent);
  }
  NorthMotor.stop();
  SouthMotor.stop();
  EastMotor.stop();
  WestMotor.stop();
}

void usercontrol(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Gyroscope.calibrate();
  while(Gyroscope.isCalibrating()) {
    task::sleep(500);
  }
  double original_heading = Gyroscope.heading(degrees);

  while(true) {

    if (Controller1.ButtonA.pressing()) {
      Gyroscope.calibrate();
      while(Gyroscope.isCalibrating()) {
        task::sleep(500);
      }
      double original_heading = Gyroscope.heading(degrees);
    }

    if (Controller1.ButtonB.pressing()) {
      RingMotor.resetPosition();
    }  

    
    if (Controller1.ButtonR2.pressing()) {
      Controller1.Screen.clearLine();
      Controller1.Screen.print("Hello, r");
      RingMotor.spin(forward, maxSpeed/8, percent);
      toggle = false;
    }
    else if (Controller1.ButtonL2.pressing()) {
      Controller1.Screen.clearLine();
      Controller1.Screen.print("Hello, l");
      RingMotor.spin(reverse, maxSpeed, percent);
      toggle = false;
    }
    // Repositioning to pickup position and dunk position
    else if (Controller1.ButtonR1.pressing()) {
      toggle = true;
    }
    else if (Controller1.ButtonL1.pressing()) {
      toggle = false;
      RingMotor.spin(forward, maxSpeed, percent);
      wait(1, seconds);
    }
      // bringing ringmotor into dock
    else if (toggle && RingMotor.position() % 3000 != 0){
      RingMotor.spin(forward, RingMotor.position() % 3000 + 10 * (RingMotor.position()/abs(RingMotor.position()), percent);
    }
    else  {
      RingMotor.stop();
    }

    // start added part
    // using two distance sensors we can let the robot autonoumsly find the correct position to dunk
    if (Controller1.ButtonC.pressing()) {
      allignement_toggle_x = true;
      allignement_toggle_y = true;
      angle_toggle = true;
    }

    // fixing angle
    if (angle_toggle) {
      delta_angle = Gyroscope.rotation(degrees) - angle;
      while (delta_angle != 0) {
        NorthMotor.spin(forward, delta_angle + 10 * ((delta_angle)/(abs(delta_angle))), percent);
        SouthMotor.spin(forward, delta_angle + 10 * ((delta_angle)/(abs(delta_angle))), percent);
        EastMotor.spin(forward, delta_angle + 10 * ((delta_angle)/(abs(delta_angle))), percent);//is actually west on the robot
        WestMotor.spin(forward, delta_angle + 10 * ((delta_angle)/(abs(delta_angle))), percent);
      }}

    // fixing y_position
    while (allignement_toggle) {
      if (Distance.objectDistance(cm) != distance_x) {
        NorthMotor.spin(forward, (Distance_x.objectDistance(cm) - distance_x)*k + 10 * (((Distance_x.objectDistance(cm)) - distance_x)/(abs(Distance_x.objectDistance(cm) - distance_x))), percent);
        SouthMotor.spin(forward, (Distance_x.objectDistance(cm) - distance_x)*k + 10 * (((Distance_x.objectDistance(cm)) - distance_x)/(abs(Distance_x.objectDistance(cm) - distance_x))), percent);
      }
      if (Distance.objectDistance(cm) != distance_y) {
        EastMotor.spin(forward, (Distance_y.objectDistance(cm) - distance_y)*k + 10 * (((Distance_y.objectDistance(cm)) - distance_y)/(abs(Distance_y.objectDistance(cm)) - distance_y)), percent);
        WestMotor.spin(forward, (Distance_y.objectDistance(cm) - distance_y)*k + 10 * (((Distance_y.objectDistance(cm)) - distance_y)/(abs(Distance_y.objectDistance(cm)) - distance_y)), percent);
      }
      if (Distance.objectDistance(cm) == distance_x && Distance.objectDistance(cm) == distance_y) {
        allignement_toggle = false
    }}
    
    // end added part

    // The gyroscope should always keep in consideration the orientation of the robot, and change the input by the degrees rotated
    double delta = original_heading - Gyroscope.rotation(degrees);
    if (delta > 180) delta -= 360;
    if (delta < -180) delta += 360;
    double delta_rad = delta * PI / 180;
    double screenCounter = 0;
    screenCounter += 20;
    
    double light_sensed = LineTracker.reflectivity();
    
    Brain.Screen.clearLine(1);
    //Brain.Screen.printAt(10, 20, "Δ: %.2f°", delta);
    Brain.Screen.printAt(10, 30, "light sensed: %.2f", light_sensed);
    screenCounter = 0;

    
    y = Controller1.Axis3.position();
    x = -Controller1.Axis4.position();
    spinControl = Controller1.Axis1.position();

    // define cos, sin for rotation matrix
    double c = cos(delta_rad);
    double s = sin(delta_rad);

    leftControl = x*c - y*s;
    rightControl = x*s + y*c;

    leftPower = (pow(leftControl, 3) / pow(100, 2) + leftControl) / 3;   // y = (x^3 / 100^2 + x) / 2
    rightPower = (pow(rightControl, 3) / pow(100, 2) + rightControl) / 3;

    NorthMotor.spin(forward, leftPower - (spinControl / 2), percent);
    SouthMotor.spin(forward, leftPower + (spinControl / 2), percent);
    EastMotor.spin(forward, rightPower + (spinControl / 2), percent);//is actually west on the robot
    WestMotor.spin(forward, rightPower - (spinControl / 2), percent);//is actually east


    task::sleep(20);
  }
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
