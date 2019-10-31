#include "vexa.h"

void pre_auton( void ) {
}
void autonomous( void ) {//move(axis,distance,power.) axisX = side to side, axisZ = fwd and back, axisXZ and axisZX are diagonals. XZ defaults left.
  softMove(1000,-100);
  vex::task::sleep(1000);
  softMove(1000,100);
  intakeLeft.spin(reverse,100,rpm);
  intakeRight.spin(reverse,100,rpm);
}