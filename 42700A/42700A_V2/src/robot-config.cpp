#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller Controller1;
motor LF = motor(PORT2, ratio18_1, false);
motor LB = motor(PORT3, ratio18_1, false);
motor RF = motor(PORT4, ratio18_1, false);
motor RB = motor(PORT5, ratio18_1, false);
motor Lift = motor(PORT8, ratio18_1, false);
motor LI = motor(PORT9, ratio18_1, false);
motor RI = motor(PORT10, ratio18_1, false);
motor tilter = motor(PORT11, ratio18_1, false);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}