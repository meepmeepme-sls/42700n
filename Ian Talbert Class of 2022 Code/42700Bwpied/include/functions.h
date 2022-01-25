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

void idletowards(vex::directionType movement){
    leftDriveMotorGroup.spin(movement,25,pct);
    rightDriveMotorGroup.spin(movement,25,pct);
}

void drivestop(){
    leftDriveMotorGroup.stop(hold);
    rightDriveMotorGroup.stop(hold);
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
void intakeSpin(vex::directionType ir, int intspinspeed = 200){// isr = intake spin rotation (RPM)
  intake.spin(ir,intspinspeed,rpm);
}
// intakeStop stops the intake rotation.
void intakeStop(){// no integers, just a shortcut.
  intake.stop();
}

bool clawsigner =true;
bool stingsigner =true;

void stingtoggle(){
      pneuA.set(stingsigner);
      stingsigner = !stingsigner;
}
void clawtoggle(){
      pneuB.set(clawsigner);
      clawsigner = !clawsigner;
}

void pdrive(int ldist, int rdist, int pscale){//ldist and rdist are the drive side distances, pscale scales back the speed at the end of the drive motion. For example, if the target is 500deg and the drive is at 400deg with a pscale of 100 the drive would be set to 100%. With a pscale of 70, the drive would be set to 70%. This allows me to adjust the decelleration proportion.
  int timeout = ((abs(ldist)+abs(rdist))/(100/pscale))/5;
  int ldrivespeed = abs(ldist)-leftDriveMotorGroup.rotation(deg);
  int rdrivespeed = abs(rdist)-rightDriveMotorGroup.rotation(deg);
  while(abs(leftDriveMotorGroup.rotation(deg))<abs(ldist)&&abs(rightDriveMotorGroup.rotation(deg))<abs(rdist)&&timeout>0){
  ldrivespeed = abs(ldist)-leftDriveMotorGroup.rotation(deg)*pscale;
  rdrivespeed = abs(rdist)-rightDriveMotorGroup.rotation(deg)*pscale;
    leftDriveMotorGroup.spin(fwd,ldrivespeed,pct);
    rightDriveMotorGroup.spin(fwd,rdrivespeed,pct);
    --timeout;
    wait(10,msec);
  }
}

void drivePD(double leftFinalValue,double rightFinalValue){
  //drive PD tuning values
  double drivekP=0.38;
  double drivekD=.03;
  double drivekI=0.05;
  //resets motor positions
  leftDriveMotorGroup.resetRotation();
  rightDriveMotorGroup.resetRotation();

  //sets up the while loop condition 
  double leftError=leftFinalValue;
  double rightError=rightFinalValue;
  double leftPreviousError=0;
  double rightPreviousError=0;
  double leftIntegral=0;
  double rightIntegral=0;

  while (fabs(leftError)>=10&&fabs(rightError)>=10){
    //Get drivetrain motor positions
    double backLeftPosition = backLeftDrive.rotation(degrees);
    double backRightPosition = backRightDrive.rotation(degrees);
    double frontLeftPosition = frontLeftDrive.rotation(degrees);
    double frontRightPosition = frontRightDrive.rotation(degrees);

    //Get average motor positions
    double leftSidePosition=(backLeftPosition+frontLeftPosition)/2;
    double rightSidePosition=(backRightPosition+frontRightPosition)/2;

    //proportional
    rightError=rightFinalValue-rightSidePosition;
    leftError=leftFinalValue-leftSidePosition; 

    //derivative
    double leftDerivative=leftError-leftPreviousError;
    double rightDerivative=rightError-rightPreviousError;

    //integral
    if(fabs(leftError)<200){
      leftIntegral+=leftError;
    }
    else{
      leftIntegral=0;
    }

    if(fabs(rightError)<200){
      rightIntegral+=rightError;
    }
    else{
      rightIntegral=0;
    }

    //sets up the motor power for each side
    double leftMotorPower=leftError*drivekP+leftDerivative*drivekD+leftIntegral*drivekI;
    double rightMotorPower=rightError*drivekP+rightDerivative*drivekD+rightIntegral*drivekI;

    rightDriveMotorGroup.spin(fwd,rightMotorPower,rpm);
    leftDriveMotorGroup.spin(fwd,leftMotorPower,rpm);

    leftPreviousError=leftError;
    rightPreviousError=rightError;

    //Sleep the PID for a short amount of time to prevent wasted resources.
    wait(20,msec);
  }
  leftDriveMotorGroup.stop();
  rightDriveMotorGroup.stop();
}

void lhd(){
  frontLift.spin(fwd,60,rpm);
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  leftDriveMotorGroup.resetRotation();
  rightDriveMotorGroup.resetRotation();
  frontLift.resetRotation();
  rearLift.resetRotation();
  stingLift.resetRotation();
  intake.resetRotation();

  Controller1.Screen.print(potGauto.value(deg));

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void stingLiftTo (int rot){
  stingLift.rotateTo(rot, deg,100,rpm,true);
}

/*
autonomous functions are below
*/


// crlob = center rush left of bridge. crlob rushes to secure the centermost mogo, then the short mogo.
/*void crlob(){
  simpleDrive(800,800,200);
  simpleDrive(100,0,200);
  simpleDrive(100,100,200);
  idletowards(fwd);
  wait(40,msec);
  clawtoggle();
  simpleDrive(-100,-100,200);
  rearLiftTo(-490,true);
  stingLiftTo(650);
  
}*/


//lcrmaprob = left center rush mogo, autonomous point. crmap rushes to secure the left centermost mogo, then secure the left alliance mogo and score in it.(right of bridge)**PRIORITIZE**
void rcrmap(){
  lhd();
  simpleDrive(1100, 1100, 200);
  frontLift.stop(brake);
  idletowards(fwd);
  wait(650,msec);
  clawtoggle();
  wait(170,msec);
  drivestop();
  frontLiftTo(-100, false);
  simpleDrive(-800,-800,200);
  frontLiftTo(20,true);
  stingLiftTo(300);
  frontLiftTo(-100,false);
  simpleDrive(-175,175,150);
  rearLiftTo(-480, true);
  simpleDrive(-550, -550, 200);
  rearLiftTo(-225,true);
  intakeSpin(fwd,200);

  //below is ring intake function. Consider removing. 
  simpleDrive(20,20,200);
  //simpleDrive(230, -230, 200);
  frontLiftTo(-100, false);
  /*
  simpleDrive(800,800,100);
  wait(100,msec);
  simpleDrive(-1100,-1100,200);
*/
}

void lcrmap(){
  frontLiftTo(-100,false);
  stingtoggle();
  intakeSpin(fwd, 100);
  simpleDrive(1200,1200, 200);
  intakeStop();
  frontLiftTo(0,true);
  lhd();
  idletowards(fwd);
  wait(300,msec);
  clawtoggle();
  //goes towards center neutral goal while intaking rings onto stinger. 

  wait(100,msec);
  frontLiftTo(-50,false);
  simpleDrive(-1000,-1000,200);
  stingtoggle();
  stingLiftTo(300);
  //drives back across line, closes stinger and lifts to a height out of the way

  simpleDrive(-200,200,150);
  rearLiftTo(-480,true);
  simpleDrive(-400,-400,200);
  rearLiftTo(-230,false);
  //grabs the ramp alliance mogo

  frontLiftTo(-100,false);
  intakeSpin(fwd);
  simpleDrive(400, 400, 150);
  simpleDrive(230,-230,150);
  simpleDrive(400,400,100);
  //feeds the cross shapes of rings into the alliance mogo; end of function
  
}

void lrsn(){//left, rush short neutral mogo
  lhd();
  simpleDrive(1100,1100,200);
  idletowards(fwd);
  wait(250,msec);
  clawtoggle();
  wait(170,msec);
  simpleDrive(-1200,-1200,200);
  simpleDrive(-100,100,150);
  stingLiftTo(300);
  rearLiftTo(-480, true);
  simpleDrive(-400, -400, 200);
  rearLiftTo(-230, true);
  intakeSpin(fwd);
}

void lrsnars(){//left, rush short neutral mogo, alliance rings scored (base off of lrsn)
  lhd();
  simpleDrive(1100,1100,200);
  idletowards(fwd);
  wait(250,msec);
  clawtoggle();
  wait(170,msec);
  simpleDrive(-1200,-1200,200);
  simpleDrive(-100,100,150);
  stingLiftTo(300);
  rearLiftTo(-480, true);
  simpleDrive(-400, -400, 200);
  rearLiftTo(-230, true);
  intakeSpin(fwd);
}
void rwap(){
  stingLiftTo(300);
  rearLiftTo(-480,true);
  simpleDrive(-400,-400,150);
  idletowards(reverse);
  wait(200,msec);
  rearLiftTo(-330,true);
  intakeSpin(fwd,150);
  drivestop();
}


void autonomous(void) {
  if(potGauto.value(deg)<25){
    lcrmap();
  }else if(potGauto.value(pct)<50){

  }else if(potGauto.value(pct)<75){
    rwap();
  }else if(potGauto.value(pct)<100){
    rcrmap();
  }
}
