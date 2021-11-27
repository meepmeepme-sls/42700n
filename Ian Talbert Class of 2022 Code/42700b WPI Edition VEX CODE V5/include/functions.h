#include "vex.h"

/*
functions.h houses all functions including pre auton and auton.
*/


// simpleDrive moves the left and right drive in unison at a certain speed.
void simpleDrive(int ld, int rd,int rs) { // ld = left displacement (deg), rd = right
                           // displacement (deg), rs = rotation speed (RPM)
  leftDriveMotorGroup.rotateFor(ld, deg, rs, rpm, false);
  rightDriveMotorGroup.rotateFor(rd, deg, rs, rpm, true);
}

// turn aims to turn the robot around center to a certain degree at a certain velocity
void simpleTurn(int trt, int ts) { // trt = turn rotation target (deg), ts = turn speed (RPM)
int multiplier = 100;
  leftDriveMotorGroup.rotateTo(trt*multiplier,deg,ts,rpm);
  rightDriveMotorGroup.rotateTo(-trt*multiplier,deg,ts,rpm);
}

// frontLiftTo moves the front (4 bar) intake to a certain location. Added blocking bool to save time.
void frontLiftTo(int fltr, bool block){ // fltr = front lift to rotation (deg), block = blockng other functions?
  frontLift.rotateTo(fltr,deg,200,rpm,block);
}
// rearLiftTo moves the rear dance, the 2 bar lift, to a certain location. Added blocking bool to save time.
void rearLiftTo(int rltr, bool block){ // rltr = rear lift to rotation (deg), block = blocking other functions?
  rearLift.rotateTo(rltr,deg,200,rpm,block);
}
//  intakeSpin is a shortcut to rotation.
void intakeSpin(int isr){// isr = intake spin rotation (RPM)
  intake.spin(fwd,isr,rpm);
}
// intakeStop stops the intake rotation.
void intakeStop(){// no integers, just a shortcut.
  intake.stop();
}


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*
autonomous functions are below
*/

// liftoff lifts a nearby rear mogo up.
void liftoff(){
rearLiftTo(200,false);
simpleDrive(-300,-300,150);
wait(500,msec);
rearLiftTo(670,true);
}

// crlob = center rush left of bridge. crlob rushes to secure the short neutral mogo, then the centermost mogo.
void crlob(){

}

// ccrlob = center, center rush left of bridge. ccrlob rushes to secure the centermost mogo, then the left side neutral mogo.
void ccrlob(){

}

//lcrmap = left center rush mogo, autonomous point. crmap rushes to secure the left centermost mogo, then secure the left alliance mogo and score in it.**PRIORITIZE**
void lcrmap(){

}

//rcrmap = right center rush mogo, autonomous point. crmap rushes to secure the right centermost mogo, then secure the right alliance mogo and score in it.**PRIORITIZE**
void rcrmap(){

}
void uniauto(){
  simpleDrive(-800, -800, 170);
  simpleDrive(-250, -250, 100);
  rearLiftTo(400,true);
  simpleDrive(900,900,200);
  frontLiftTo(-490,true);
  simpleDrive(-200,200,200);//200 is about 80 degrees
}

void autonomous(void) {
  uniauto();
}
