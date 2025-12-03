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
// Distance_x           distance      10              
// Distance_y           distance      7               
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
double delta = 0;
double ringControl = 0;
double rotation_ratio = 1720;
#define PI 3.14159265358979323846
double maxSpeed = 100;
bool toggle = false;

// start added variables
double distance_x = 14.8;
double distance_y = 14.57;
double angle_end = 0; // deg
double delta_angle = 0;
double delta_x = 0;
double delta_y = 0;
bool allignement_toggle = false;
bool angle_toggle = false;
double k = 1.5; // scaling factor
// end added variables


void pre_auton(void) {

}

void autonomous(void) {

  // Idea for new autonomous

  // end Idea
  
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
  RingMotor.resetPosition();
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
      //toggle = false;
      RingMotor.spin(reverse, maxSpeed, percent);
      wait(0.6, seconds);
    }
      // bringing ringmotor into dock
    else if (toggle && fabs(remainder(RingMotor.position(degrees), rotation_ratio)) != 0){
      RingMotor.spin(forward, -remainder(RingMotor.position(degrees), rotation_ratio)/100 + 10 * int((-RingMotor.position(degrees)/abs(RingMotor.position(degrees)))), percent);
    }
    else  {
      RingMotor.stop();
    }

    // fixing angle
    if (Controller1.ButtonX.pressing()) {
      RingMotor.stop();
      delta_angle = Gyroscope.rotation(degrees) - angle_end;
      if (delta_angle > 180) delta_angle -= 360;
      if (delta_angle < -180) delta_angle += 360;
      while (abs(delta_angle) >= 2) {
        NorthMotor.spin(forward, delta_angle/2 + 10 * ((delta_angle)/(abs(delta_angle))), percent);
        SouthMotor.spin(forward, -delta_angle/2 - 10 * ((delta_angle)/(abs(delta_angle))), percent);
        EastMotor.spin(forward, -delta_angle/2 - 10 * ((delta_angle)/(abs(delta_angle))), percent);//is actually west on the robot
        WestMotor.spin(forward, delta_angle/2 + 10 * ((delta_angle)/(abs(delta_angle))), percent);
        wait(20, msec);
        delta_angle = Gyroscope.rotation(degrees) - angle_end;
        if (delta_angle > 180) delta_angle -= 360;
        if (delta_angle < -180) delta_angle += 360;
      }
      NorthMotor.stop();
      SouthMotor.stop();
      EastMotor.stop();
      WestMotor.stop();

      angle_toggle = false;
      allignement_toggle = true;
      }
      
    // fixing position
    while (allignement_toggle) {
      delta_x = Distance_x.objectDistance(inches) - distance_x;
      delta_y = Distance_y.objectDistance(inches) - distance_y;
      double delta_variation = Gyroscope.rotation(degrees) - angle_end;
      while (delta_variation > 180) delta_variation -= 360;
      while (delta_variation < -180) delta_variation += 360;
      //double c = cos(delta_variation);
      //double s = sin(delta_variation);
      x = -(delta_x)*k - 5 * ((delta_x)/(fabs(delta_x)));
      y = -(delta_y)*k - 5 * ((delta_y)/(fabs(delta_y)));
      double k_angle = 1;
      if (fabs(delta_x) >= 0.3) {
        NorthMotor.spin(forward, x + delta_variation*k_angle, percent);
        SouthMotor.spin(forward, x - delta_variation*k_angle, percent);
      }
      else {
        NorthMotor.stop();
        SouthMotor.stop();
      }
      if (fabs(delta_y) >= 0.3) {
        EastMotor.spin(forward, y - delta_variation*k_angle, percent);
        WestMotor.spin(forward, y + delta_variation*k_angle, percent);
      } 
      else {
        EastMotor.stop();
        WestMotor.stop();
      }
      if (fabs(delta_x) < 0.3 && fabs(delta_y) < 0.3) {
        NorthMotor.stop();
        SouthMotor.stop();
        EastMotor.stop();
        WestMotor.stop();
        allignement_toggle = false;
      }
     wait(20, msec);
    }
    
    // end added part

    // The gyroscope should always keep in consideration the orientation of the robot, and change the input by the degrees rotated
    delta = original_heading - Gyroscope.rotation(degrees);
    if (delta > 180) delta -= 360;
    if (delta < -180) delta += 360;
    double delta_rad = delta * PI / 180;
    double screenCounter = 0;
    screenCounter += 20;
    
    double light_sensed = LineTracker.reflectivity();
    
    Brain.Screen.clearLine(1);
    //Brain.Screen.printAt(10, 20, "Δ: %.2f°", delta);
    //Brain.Screen.printAt(10, 30, "light sensed: %.2f", light_sensed);
    screenCounter = 0;

    double Distance_to_x = Distance_x.objectDistance(inches);
    double Distance_to_y = Distance_y.objectDistance(inches);
    Brain.Screen.clearLine(1);
    Brain.Screen.clearLine(2);
    Brain.Screen.printAt(10, 30, "Distance_to_x: %.2f", Distance_to_x);
    //Brain.Screen.printAt(10, 60, "Distance_to_y: %.2f", Distance_to_y);

    
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
