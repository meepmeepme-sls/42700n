#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

controller Controller1 = controller();

motor frontLift = motor (PORT11,ratio36_1, true);
motor frontLeftDrive = motor (PORT20,ratio18_1, true);
motor backLeftDrive = motor (PORT16,ratio18_1, true);
motor frontRightDrive = motor (PORT1,ratio18_1, false);
motor backRightDrive = motor (PORT4,ratio18_1, false);
motor intake = motor (PORT19,ratio6_1, false);
motor rearLift = motor (PORT2,ratio36_1, false);
motor stingLift = motor (PORT13,ratio36_1, true);

pot potH = pot (Brain.ThreeWirePort.H);
pot potG = pot  (Brain.ThreeWirePort.G);

pneumatics pneuA = pneumatics (Brain.ThreeWirePort.A);
pneumatics pneuB = pneumatics (Brain.ThreeWirePort.B);


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