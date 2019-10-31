#include "vexa.h"
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  leftDrive.resetRotation();
  rightDrive.resetRotation();
  liftLeft.resetRotation();
  liftRight.resetRotation();
  centerDrive.resetRotation();
  intakeLeft.resetRotation();
  intakeRight.resetRotation();
  tilterMotor.resetRotation();
  driveMotors.setTimeout(3,sec);
  liftLeft.setTimeout(2,sec);
  liftRight.setTimeout(2,sec);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void driveBackAutonomous(){
  
    //sets motor to move in a direction at a set velocity. Doesn't say anything else.
    leftDrive.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
    rightDrive.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
    vex::task::sleep(1000);
    //reverses the spinning after 1 second
    leftDrive.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
    rightDrive.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
    vex::task::sleep(500);
    //stops both motors after 1/2 a second delay of driving fwd.
    leftDrive.stop();
    rightDrive.stop();
    drive(0,300,0,200);
    intakeLeft.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);
    intakeRight.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);
}
void deploy(){
  intakeLeft.spin(reverse,100,percent);
  intakeRight.spin(reverse,100,percent);
  wait(500,msec);
  intakeLeft.stop();
  intakeRight.stop();
}



void redShortAutonomous(){
  Controller1.Screen.print("redShortAutonomous");
  intakeGroup.spin(fwd,200,rpm);
  drive(1300,1300,1300,50);
  drive(-100,-100,-100,200);
  leftDrive.rotateFor(-287,deg,160,rpm);
  drive(-1150,-1150,-1150,70);
  rightDrive.rotateFor(-287,deg,160,rpm);
  drive(1200,1200,1200,47);
  drive(-700,-700,-500,160);
  drive(380,-380,0,160);
  softMotion(120,300);
  intakeGroup.spin(reverse,300,rpm);
  wait(200,msec);
  intakeGroup.stop();
  tilterMotor.rotateTo(200,deg,100,rpm);
  intakeGroup.spin(fwd,200,rpm);
  tilterMotor.rotateTo(400,deg,90,rpm);
  tilterMotor.rotateTo(600,deg,60,rpm);
  wait(100,msec);
  intakeGroup.spin(reverse,180,rpm);
  wait(50,msec);
  intakeGroup.spin(reverse,140,rpm);
  driveMotors.spin(reverse,200,rpm);
  wait(500,msec);
  intakeGroup.stop();
  driveMotors.stop();
}
void blueShortAutonomous(){
  
  intakeGroup.spin(fwd,200,rpm);
  drive(1300,1300,1300,50);
  drive(-100,-100,-100,200);
  rightDrive.rotateFor(-270,deg,160,rpm);
  drive(-1200,-1200,-1200,70);
  leftDrive.rotateFor(-275,deg,160,rpm);
  drive(1200,1200,1200,50);
  drive(-700,-700,-500,160);
  drive(-365,365,0,160);
  drive(433,433,463,200);
  intakeGroup.spin(reverse,300,rpm);
  wait(200,msec);
  intakeGroup.stop();
  tilterMotor.rotateTo(300,deg,100,rpm);
  intakeGroup.spin(fwd,200,rpm);
  tilterMotor.rotateTo(400,deg,60,rpm);
  tilterMotor.rotateTo(600,deg,35,rpm);
  wait(100,msec);
  intakeGroup.spin(reverse,180,rpm);
  wait(50,msec);
  intakeGroup.spin(reverse,140,rpm);
  driveMotors.spin(reverse,200,rpm);
  wait(500,msec);
  intakeGroup.stop();
  driveMotors.stop();

}
void redLongAutonomous(){
  Controller1.Screen.print("redLongAutonomous");
  intakeLeft.spin(fwd,100,pct);
  intakeRight.spin(fwd,100,pct);
  
}
void blueLongAutonomous(){
  Controller1.Screen.print("blueLongAutonomous");
  intakeLeft.spin(fwd,100,pct);
  intakeRight.spin(fwd,100,pct);
}
void skills(){

}
void autonomous(void) {
  deploy();
  if(autonomousSelector.value(range12bit)<1150){  Controller1.Screen.clearLine();

    Controller1.Screen.print("1");
    redShortAutonomous();
  }else if(autonomousSelector.value(range12bit)<1300){  Controller1.Screen.clearLine();

    Controller1.Screen.print("2");
    driveBackAutonomous();
  }else if(autonomousSelector.value(range12bit)<2000){  Controller1.Screen.clearLine();

    Controller1.Screen.print("3");
    blueShortAutonomous();
  }else if(autonomousSelector.value(range12bit)<3000){  Controller1.Screen.clearLine();

    Controller1.Screen.print("4");
    redLongAutonomous();
  }else if(autonomousSelector.value(range12bit)<4000){   Controller1.Screen.clearLine();

    Controller1.Screen.print("5");  
    blueLongAutonomous();
  }else{  Controller1.Screen.clearLine();

    Controller1.Screen.print("6");
    skills();
  }
}