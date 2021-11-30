#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

controller Controller1 = controller();

motor frontLift = motor (PORT11,ratio36_1, false);
motor frontLeftDrive = motor (PORT20,ratio18_1, false);
motor backLeftDrive = motor (PORT16,ratio18_1, false);
motor frontRightDrive = motor (PORT1,ratio18_1, true);
motor backRightDrive = motor (PORT4,ratio18_1, true);
motor intake = motor (PORT19,ratio18_1, false);
motor rearLift = motor (PORT6,ratio36_1, false);
motor stingLift = motor (PORT13,ratio36_1, false);

pot potHside = pot (Brain.ThreeWirePort.H); // bot one physically.
pot potGauto = pot  (Brain.ThreeWirePort.G);// top one physically

digital_out pneuA = digital_out (Brain.ThreeWirePort.A);
digital_out pneuB = digital_out (Brain.ThreeWirePort.B);


motor_group leftDriveMotorGroup(frontLeftDrive, backLeftDrive);
motor_group rightDriveMotorGroup(frontRightDrive, backRightDrive);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}