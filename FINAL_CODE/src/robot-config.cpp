#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor NorthMotor = motor(PORT1, ratio18_1, true);
motor SouthMotor = motor(PORT2, ratio18_1, false);
controller Controller1 = controller(primary);
motor EastMotor = motor(PORT3, ratio18_1, false);
motor WestMotor = motor(PORT4, ratio18_1, true);
inertial Gyroscope = inertial(PORT5);
motor RingMotor = motor(PORT6, ratio18_1, false);
line LineTracker = line(Brain.ThreeWirePort.H);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}