using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor leftDrive;
extern motor rightDrive;
extern motor liftLeft;
extern motor liftRight;
extern motor intakeLeft;
extern motor intakeRight;
extern motor centerDrive;
extern motor tilterMotor;
extern pot autonomousSelector;
extern controller Controller1;

extern motor_group driveMotors;
extern motor_group intakeGroup;
extern motor_group  liftGroup;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );