#include "vex.h"
vex::competition Competition;
void move( char directionOfMovement[],int rotationDistance,int pow){
  if(strcmp(directionOfMovement, "axisX")){//side to side
    leftFrontDrive.rotateFor(-rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    rightFrontDrive.rotateFor(-rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    leftBackDrive.rotateFor(rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    rightBackDrive.rotateFor(rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
  }if(strcmp(directionOfMovement, "axisZ")){// forward and back
    leftFrontDrive.rotateFor(rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    rightFrontDrive.rotateFor(-rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    leftBackDrive.rotateFor(rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    rightBackDrive.rotateFor(-rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
  }if(strcmp(directionOfMovement, "axisXZ")){//diagonal movement defaulting left
    rightFrontDrive.rotateFor(-rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    leftBackDrive.rotateFor(rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
  }if(strcmp(directionOfMovement, "axisZX")){//diagonal movement defaulting right
    leftFrontDrive.rotateFor(rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    rightBackDrive.rotateFor(-rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
  }
}
void turn(int turnRotation, int pow){
    leftFrontDrive.rotateFor(-turnRotation,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    rightFrontDrive.rotateFor(-turnRotation,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    leftBackDrive.rotateFor(-turnRotation,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    rightBackDrive.rotateFor(-turnRotation,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
}
void softMove(int movementTime, int pow){
    leftFrontDrive.spin(vex::directionType::fwd,pow,vex::velocityUnits::pct);
    rightFrontDrive.spin(vex::directionType::rev,pow,vex::velocityUnits::pct);
    leftBackDrive.spin(vex::directionType::fwd,pow,vex::velocityUnits::pct);
    rightBackDrive.spin(vex::directionType::rev,pow,vex::velocityUnits::pct);
    vex::task::sleep(movementTime);
}
void pre_auton( void ) {
}
void autonomous( void ) {//move(axis,distance,power.) axisX = side to side, axisZ = fwd and back, axisXZ and axisZX are diagonals. XZ defaults left.
  softMove(2000,-100);
  vex::task::sleep(1000);
  softMove(2000,100);
}

void usercontrol( void ) {
  while (1) {
Controller1.Screen.print(liftLeft.rotation(vex::rotationUnits::deg));
    int leftFrontMotorSpeed = Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value();
    int rightFrontMotorSpeed = Controller1.Axis3.value() - Controller1.Axis4.value() - Controller1.Axis1.value();
    int leftBackMotorSpeed = Controller1.Axis3.value() - Controller1.Axis4.value() + Controller1.Axis1.value();
    int rightBackMotorSpeed = Controller1.Axis3.value() + Controller1.Axis4.value() - Controller1.Axis1.value();  

    leftFrontDrive.spin(vex::directionType::fwd,leftFrontMotorSpeed,vex::velocityUnits::pct);
    rightFrontDrive.spin(vex::directionType::fwd,rightFrontMotorSpeed,vex::velocityUnits::pct);
    leftBackDrive.spin(vex::directionType::fwd,leftBackMotorSpeed,vex::velocityUnits::pct);
    rightBackDrive.spin(vex::directionType::fwd,rightBackMotorSpeed,vex::velocityUnits::pct);  // values based on feedback from the joysticks.
    if(potentiometerControl.value(vex::percentUnits::pct)<50){
      if(Controller1.ButtonL1.pressing()){
        liftLeft.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
        liftRight.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
      }else 
      if(Controller1.ButtonL2.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)>0){
        liftLeft.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
        liftRight.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
      }else{
        liftLeft.stop(vex::brakeType::hold);
        liftRight.stop(vex::brakeType::hold);
      }
      if(Controller1.ButtonR1.pressing()){
        intakeLeft.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
        intakeRight.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
      }else 
      if(Controller1.ButtonR2.pressing()){
        intakeLeft.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
        intakeRight.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
      }else{
        intakeLeft.stop(vex::brakeType::hold);
        intakeRight.stop(vex::brakeType::hold);
      }
      if(Controller1.ButtonLeft.pressing()){
        liftLeft.rotateTo(200,vex::rotationUnits::deg,100,vex::velocityUnits::pct,false);
        liftRight.rotateTo(200,vex::rotationUnits::deg,100,vex::velocityUnits::pct,false);
      }if(Controller1.ButtonUp.pressing()){
        liftLeft.rotateTo(260,vex::rotationUnits::deg,100,vex::velocityUnits::pct,false);
        liftRight.rotateTo(260,vex::rotationUnits::deg,100,vex::velocityUnits::pct,false);
      }if(Controller1.ButtonRight.pressing()){
        liftLeft.rotateTo(500,vex::rotationUnits::deg,100,vex::velocityUnits::pct,false);
        liftRight.rotateTo(500,vex::rotationUnits::deg,100,vex::velocityUnits::pct,false);
      }if(Controller1.ButtonDown.pressing()){
        liftLeft.rotateTo(0,vex::rotationUnits::deg,100,vex::velocityUnits::pct,false);
        liftRight.rotateTo(0,vex::rotationUnits::deg,100,vex::velocityUnits::pct,false);
      }
    }
    
    else{
      if(Controller1.ButtonR1.pressing()){
        liftLeft.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
        liftRight.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
      }else 
      if(Controller1.ButtonR2.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)>0){
        liftLeft.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
        liftRight.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
      }else{
        liftLeft.stop(vex::brakeType::hold);
        liftRight.stop(vex::brakeType::hold);
      }
      if(Controller1.ButtonL2.pressing()){
        intakeLeft.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
        intakeRight.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
      }else 
      if(Controller1.ButtonL1.pressing()){
        intakeLeft.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
        intakeRight.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
      }else{
        intakeLeft.stop(vex::brakeType::hold);
        intakeRight.stop(vex::brakeType::hold);
      }

    }
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}
int main() {
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    pre_auton();
    while(1) {
    vex::task::sleep(100);
    }
  }