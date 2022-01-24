#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller Controller;

motor frontLeft = motor(PORT7,ratio6_1,false);
motor midLeft = motor(PORT2,ratio6_1,false);
motor rearLeft = motor(PORT1,ratio6_1,false);

motor frontRight = motor(PORT10,ratio6_1,true);
motor midRight = motor(PORT9,ratio6_1,true);
motor rearRight = motor(PORT8,ratio6_1,true);

motor claw = motor(PORT3,ratio36_1,false);
motor lift = motor(PORT11,ratio36_1,true);

motor_group leftDrive = motor_group(frontLeft,midLeft,rearLeft);
motor_group rightDrive = motor_group(frontRight,midRight,rearRight);

inertial imu = inertial(PORT19);

digital_in rearLimit = digital_in(Brain.ThreeWirePort.A);

digital_out sauron = digital_out(Brain.ThreeWirePort.C);
digital_out rearClaw = digital_out(Brain.ThreeWirePort.D);

pot potGAuto = pot(Brain.ThreeWirePort.F);
pot liftLevel = pot(Brain.ThreeWirePort.B);
pot clawLevel = pot(Brain.ThreeWirePort.E);

color autoncolor = color(3*(potGAuto.value(pct)),4*(potGAuto.value(pct)),potGAuto.value(pct));

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}