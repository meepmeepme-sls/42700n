#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller Controller;
motor FL = motor(PORT1);
motor BL = motor(PORT2);
motor FR = motor(PORT3);
motor BR = motor(PORT4);
motor AL = motor(PORT5);
motor AR = motor(PORT6);
motor Claw = motor(PORT7);
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}