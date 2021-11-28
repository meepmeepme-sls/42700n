#include "vex.h"

/*
functions.h houses all functions including pre auton and auton.
*/


// simpleDrive moves the left and right drive in unison at a certain speed.
void simpleDrive(int ld, int rd,int rs) { // ld = left displacement (deg), rd = right
                           // displacement (deg), rs = rotation speed (RPM)
  leftDriveMotorGroup.rotateFor(ld, deg, rs, rpm, false);
  rightDriveMotorGroup.rotateFor(rd, deg, rs, rpm, true);
  leftDriveMotorGroup.stop(hold);
  rightDriveMotorGroup.stop(hold);
}

void idletowards(bool dir){
  if(dir==true){
    leftDriveMotorGroup.spin(fwd,20,pct);
    rightDriveMotorGroup.spin(fwd,20,pct);
  }else{
    leftDriveMotorGroup.spin(reverse,20,pct);
    rightDriveMotorGroup.spin(reverse,20,pct);
  }
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
void intakeSpin(int isr){// isr = intake spin rotation (RPM)
  intake.spin(fwd,isr,rpm);
}
// intakeStop stops the intake rotation.
void intakeStop(){// no integers, just a shortcut.
  intake.stop();
}

bool clawsigner =true;

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

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void stingLiftTo (int rot){
  stingLift.rotateTo(rot, deg,100,rpm,true);
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

// crlob = center rush left of bridge. crlob rushes to secure the centermost mogo, then the short mogo.
void crlob(){
  simpleDrive(800,800,200);
  simpleDrive(100,0,200);
  simpleDrive(100,100,200);
  idletowards(true);
  wait(40,msec);
  clawtoggle();
  simpleDrive(-100,-100,200);
  rearLiftTo(-490,true);
  stingLiftTo(650);
  
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
  if(potGauto.value(deg)<60){
    crlob();
  }else if(potGauto.value(deg)<120){

  }else if(potGauto.value(deg)<180){

  }else if(potGauto.value(deg)<240){

  }else if(potGauto.value(deg)<300){

  }else{
    
  }
}
