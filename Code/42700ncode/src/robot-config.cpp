#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;
controller Controller1 = controller();
// VEXcode device constructors
motor  leftDrive = motor(PORT11, ratio18_1, false);
 motor rightDrive=motor( PORT15, ::ratio18_1,true);
 motor liftLeft=motor( PORT2, ::ratio36_1,true);
 motor liftRight=motor( PORT8, ::ratio36_1,false);
 motor intakeLeft=motor( PORT9, ::ratio18_1,true);
 motor intakeRight=motor( PORT1, ::ratio18_1,false);
 motor centerDrive=motor( PORT13, ::ratio18_1,true);
 motor tilterMotor=motor( PORT10, ::ratio36_1,false);

 motor_group driveMotors =motor_group(leftDrive,rightDrive,centerDrive);

 motor_group intakeGroup =motor_group(intakeLeft,intakeRight);

pot autonomousSelector=pot(Brain.ThreeWirePort.E);

// VEXcode generated functions

//defines a controller named "Controller1"
/* controller Controller1;
 brain       Brain;

//defines the motor name(port#,gear ratio, reversed setting);
 motor leftDrive( PORT15,::ratio18_1,true);
 motor rightDrive( PORT11, ::ratio18_1,false);
 motor liftLeft( PORT3, ::ratio36_1,true);
 motor liftRight( PORT8, ::ratio36_1,false);
 motor intakeLeft( PORT9, ::ratio18_1,true);
 motor intakeRight( PORT1, ::ratio18_1,false);
 motor strafingDrive( PORT13, ::ratio18_1,false);
 motor tilterMotor( PORT10, ::ratio36_1,false);

 pot autonomousSelector(Brain.ThreeWirePort.H);
*/

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}