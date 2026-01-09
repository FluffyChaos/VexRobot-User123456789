using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor NorthMotor;
extern motor SouthMotor;
extern controller Controller1;
extern motor EastMotor;
extern motor WestMotor;
extern inertial Gyroscope;
extern motor RingMotor;
extern line LineTracker;
extern distance Distance_x;
extern distance Distance_y;
extern motor Ramp1;
extern motor Ramp2;
extern motor RampTurn;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );
