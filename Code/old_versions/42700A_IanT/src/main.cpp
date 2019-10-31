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
    rightFrontDrive.spin(vex::directionType::fwd,pow,vex::velocityUnits::pct);
    leftBackDrive.spin(vex::directionType::fwd,pow,vex::velocityUnits::pct);
    rightBackDrive.spin(vex::directionType::fwd,pow,vex::velocityUnits::pct);
    leftFrontDrive.stop();
    rightFrontDrive.stop();
    leftBackDrive.stop();
    rightBackDrive.stop();
    vex::task::sleep(movementTime);
}
void pre_auton( void ) {
}
void autonomous( void ) {//move(axis,distance,power.) axisX = side to side, axisZ = fwd and back, axisXZ and axisZX are diagonals. XZ defaults left.
  softMove(1000,-100);
  vex::task::sleep(1000);
  softMove(1000,100);
  intakeLeft.spin(reverse,100,rpm);
  intakeRight.spin(reverse,100,rpm);
}

void usercontrol( void ) {
  while (1) {
    int leftFrontMotorSpeed = Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value();
    int rightFrontMotorSpeed = Controller1.Axis3.value() - Controller1.Axis4.value() - Controller1.Axis1.value();
    int leftBackMotorSpeed = Controller1.Axis3.value() - Controller1.Axis4.value() + Controller1.Axis1.value();
    int rightBackMotorSpeed = Controller1.Axis3.value() + Controller1.Axis4.value() - Controller1.Axis1.value();  

    leftFrontDrive.spin(vex::directionType::fwd,leftFrontMotorSpeed,vex::velocityUnits::pct);
    rightFrontDrive.spin(vex::directionType::fwd,rightFrontMotorSpeed,vex::velocityUnits::pct);
    leftBackDrive.spin(vex::directionType::fwd,leftBackMotorSpeed,vex::velocityUnits::pct);
    rightBackDrive.spin(vex::directionType::fwd,rightBackMotorSpeed,vex::velocityUnits::pct);  // values based on feedback from the joysticks.
     
int tilterSpeed = (100*(1-(tilterMotor.rotation(vex::rotationUnits::deg)/800)))-10;
//Controller1.Screen.print("%.2f", tilterSpeed);
  //  Controller1.Screen.setCursor(1, 1);
      if(Controller1.ButtonX.pressing()&&tilterMotor.rotation(degrees)<800){
        tilterMotor.spin(fwd,tilterSpeed,rpm);
      }else if(Controller1.ButtonY.pressing()&&tilterMotor.rotation(vex::rotationUnits::deg)>0){
        tilterMotor.spin(reverse,100,rpm);
      }else{
        tilterMotor.stop(hold);
      }
      
    if(potentiometerControl.value(vex::percentUnits::pct)<50){
      if(Controller1.ButtonL1.pressing()&&liftMotor.rotation(degrees)<800){
        liftMotor.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
      }else 
      if(Controller1.ButtonL2.pressing()/*&&liftMotor.rotation(vex::rotationUnits::deg)>0*/){
        liftMotor.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
      }else{
        liftMotor.stop(vex::brakeType::hold);
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
        liftMotor.rotateTo(200,vex::rotationUnits::deg,100,vex::velocityUnits::pct,false);
      }if(Controller1.ButtonUp.pressing()){
        liftMotor.rotateTo(260,vex::rotationUnits::deg,100,vex::velocityUnits::pct,false);
      }if(Controller1.ButtonRight.pressing()){
        liftMotor.rotateTo(500,vex::rotationUnits::deg,100,vex::velocityUnits::pct,false);
      }if(Controller1.ButtonDown.pressing()){
        liftMotor.rotateTo(0,vex::rotationUnits::deg,100,vex::velocityUnits::pct,false);
      }if(Controller1.ButtonB.pressing()){
 leftFrontDrive.spin(reverse,200,rpm);
 rightFrontDrive.spin(reverse,200,rpm);
 leftBackDrive.spin(reverse,200,rpm);
 rightBackDrive.spin(reverse,200,rpm);
 intakeLeft.spin(reverse,200,rpm);
 intakeRight.spin(reverse,200,rpm);
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