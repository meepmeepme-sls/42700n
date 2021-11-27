using namespace vex;

//initializes brain and controller
extern brain Brain;
extern controller Controller1;

//initializes motors.
  extern motor frontLift;
  extern motor frontLeftDrive;
  extern motor backLeftDrive;
  extern motor frontRightDrive;
  extern motor backRightDrive;
  extern motor intake;
  extern motor rearLift;

  extern pot potH;
  extern pot potG;

  extern pneumatics pneuA;
  extern pneumatics pneuB;

extern motor_group leftDriveMotorGroup;
extern motor_group rightDriveMotorGroup;

//end device initialization.

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
