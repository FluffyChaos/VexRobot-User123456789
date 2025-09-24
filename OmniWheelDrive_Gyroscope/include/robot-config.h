using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor NorthMotor;
extern motor SouthMotor;
extern controller Controller1;
extern motor EastMotor;
extern motor WestMotor;
extern inertial Gyroscope;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );