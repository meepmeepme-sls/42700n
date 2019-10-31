#include "vex.h"

using namespace vex;

//dead brain ports | 1; 3; 4; 7; 8; 12; 13; 18;
brain Brain;
controller Controller1;
motor LF = motor(PORT10, ratio18_1, false);
motor LB = motor(PORT19, ratio18_1, false);
motor RF = motor(PORT6, ratio18_1, false);
motor RB = motor(PORT20, ratio18_1, false);
motor Lift = motor(PORT9, ratio18_1, false);
motor LI = motor(PORT5, ratio18_1, false);
motor RI = motor(PORT2, ratio18_1, false);
motor tilter = motor(PORT16, ratio18_1, false);
pot notweed = pot(Brain.ThreeWirePort.A);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}