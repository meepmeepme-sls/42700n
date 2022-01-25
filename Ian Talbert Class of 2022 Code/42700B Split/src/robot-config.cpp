#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller Controller;

motor frontLeft = motor(PORT6,ratio6_1,true);
motor midLeft = motor(PORT9,ratio6_1,true);
motor rearLeft = motor(PORT10,ratio6_1,true);

motor frontRight = motor(PORT13,ratio6_1,false);
motor midRight = motor(PORT2,ratio6_1,false);
motor rearRight = motor(PORT14,ratio6_1,false);

motor leftLift = motor(PORT20,ratio36_1,false);
motor rightLift = motor(PORT11,ratio36_1,true);

motor_group leftDrive = motor_group(frontLeft,midLeft,rearLeft);
motor_group rightDrive = motor_group(frontRight,midRight,rearRight);
motor_group lift = motor_group(leftLift,rightLift);

inertial imu = inertial(PORT19);

digital_in frontLimit = digital_in(expand.D);
digital_in rearLimit = digital_in(expand.E);

digital_out frontClaw = digital_out(expand.A);
digital_out rearClaw = digital_out(expand.B);

pot potGAuto = pot(expand.G);
pot liftLevel = pot(expand.H);

triport expand = triport(PORT8);

color autoncolor = color(3*(potGAuto.value(pct)),4*(potGAuto.value(pct)),potGAuto.value(pct));

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}