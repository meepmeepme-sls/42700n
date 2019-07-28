//This begins VEX Competition Template constructors.
#include "vex.h"
using namespace vex;
vex::brain       Brain;
vex::competition Competition;
  //This is the end of VEX Competition Template Constructors.

//This is the beginning of autonomous function calleftDriveack constructors.

//this function is for going straight

    int thresh = 20;
void drive(int leftTargetDistance, int rightTargetDistance, int driveTopSpeed) {

  while(leftDrive.rotation(vex::rotationUnits::deg)<leftTargetDistance){

    int leftCurrentDistance = ( leftDrive.rotation(vex::rotationUnits::deg)  );
    int rightCurrentDistance = ( rightDrive.rotation(vex::rotationUnits::deg)  );
    int leftSpeed = ( (thresh*driveTopSpeed) + ((1-thresh)*driveTopSpeed*(1-(leftCurrentDistance/leftTargetDistance))  ) );
    int rightSpeed = ( (thresh*driveTopSpeed) + ((1-thresh)*driveTopSpeed*(1-(rightCurrentDistance/rightTargetDistance))  ) );

    leftDrive.startRotateTo(leftTargetDistance,vex::rotationUnits::deg,leftSpeed,vex::velocityUnits::rpm);
    rightDrive.startRotateTo(rightTargetDistance,vex::rotationUnits::deg,rightSpeed,vex::velocityUnits::rpm);
      }//end of while loop
      leftDrive.resetRotation();
      rightDrive.resetRotation();
        }

void strafe(int strafingTargetDistance, int strafingTopSpeed){

  while(strafingDrive.rotation(vex::rotationUnits::deg)<strafingTargetDistance){

    int strafingCurrentSpeed = ( (thresh*strafingTopSpeed) + ((1-thresh)*strafingTopSpeed*(1-(strafingDrive.rotation(vex::rotationUnits::deg)/strafingTargetDistance) )  ) );
    strafingDrive.startRotateTo(strafingTargetDistance,vex::rotationUnits::deg,strafingCurrentSpeed,vex::velocityUnits::rpm);

    }

      }

void liftTo(int rotationTarget, int liftTopSpeed, int mode) {


  while(liftLeft.rotation(vex::rotationUnits::deg)<rotationTarget){
    int liftCurrentDistance = ( liftLeft.rotation(vex::rotationUnits::deg) + liftRight.rotation(vex::rotationUnits::deg) )/2;

    int liftCurrentSpeed = ( (thresh*liftTopSpeed) + ((1-thresh)*liftTopSpeed*(1-(liftCurrentDistance/rotationTarget))  ) );

  if(mode==0){

    liftLeft.rotateTo(rotationTarget,vex::rotationUnits::deg,liftCurrentSpeed,vex::velocityUnits::rpm,false);

    liftRight.rotateTo(rotationTarget,vex::rotationUnits::deg,liftCurrentSpeed,vex::velocityUnits::rpm);
    }else if(mode==1){
      liftLeft.startRotateTo(rotationTarget,vex::rotationUnits::deg,liftCurrentSpeed,vex::velocityUnits::rpm);
      liftRight.startRotateTo(rotationTarget,vex::rotationUnits::deg,liftCurrentSpeed,vex::velocityUnits::rpm);
      
      }
        }
          }
void intake(){
  intakeLeft.spin(vex::directionType::fwd,100,vex::velocityUnits::rpm);
  intakeRight.spin(vex::directionType::fwd,100,vex::velocityUnits::rpm);
}

/*
void intakeout(){
  mi.spin(vex::directionType::rev,100,vex::velocityUnits::rpm);
}
void intakein(){
  mi.spin(vex::directionType::fwd,100,vex::velocityUnits::rpm);
}
void gin(){
    ir.spin(vex::directionType::fwd,100,vex::velocityUnits::rpm);
    il.spin(vex::directionType::fwd,100,vex::velocityUnits::rpm);
}
void gout(){
    ir.spin(vex::directionType::rev,100,vex::velocityUnits::rpm);
    il.spin(vex::directionType::rev,100,vex::velocityUnits::rpm);

}
*/

  //This is the end of autonomous function calleftDrive constructors.

void pre_auton( void ) {
  
}

void autonomous( void ) {
  liftTo(900,100,0);
  drive(900,900,200);
}

//This is the beginning of the teleop part of the code. It's broken into three parts: Drive, Lift, and Intakes.

void usercontrol( void ) {
  while (1) {
  
  //This is the beginning of the drive constructor.
  int dz = 15;
  
  //These are ternary operators. I'm using them so that the controller is less sensitive. If the value of the joystick does not exceed a certain value it will set the value to zero.
  int leftDriveTeleOp = Controller1.Axis3.value()-Controller1.Axis1.value();
  leftDriveTeleOp = abs(leftDriveTeleOp) > dz ? leftDriveTeleOp : 0;
  int RightDriveTeleOp = Controller1.Axis3.value()+Controller1.Axis1.value();
  RightDriveTeleOp = abs(RightDriveTeleOp) > dz ? RightDriveTeleOp : 0;
  int strafeDriveTeleOp = Controller1.Axis4.value();
  strafeDriveTeleOp = abs(strafeDriveTeleOp) > dz ? strafeDriveTeleOp : 0;
      //connects the joysticks with the drive
      leftDrive.spin(vex::directionType::fwd, leftDriveTeleOp, vex::velocityUnits::rpm);
      rightDrive.spin(vex::directionType::fwd, RightDriveTeleOp, vex::velocityUnits::rpm);
      strafingDrive.spin(vex::directionType::fwd,strafeDriveTeleOp,vex::velocityUnits::rpm);

  //This is the end of the drive constructor.

  //This is the beginning of the lift constructor.

  //connects the lift to the shoulder buttons.
  int stopCheck = (liftLeft.velocity(vex::velocityUnits::rpm) + liftRight.velocity(vex::velocityUnits::rpm) )/2;

  if(Controller1.ButtonL1.pressing()){
    liftLeft.spin(vex::directionType::fwd,100,vex::velocityUnits::rpm);
    liftRight.spin(vex::directionType::fwd,100,vex::velocityUnits::rpm);
      //this check stops the lift from stalling out on top, and lets me know when it is.
      if(stopCheck<20){
        liftLeft.stop(vex::brakeType::coast);
        liftRight.stop(vex::brakeType::coast);
        Controller1.rumble(".....");
      }
        } else if(Controller1.ButtonL2.pressing()){
        liftLeft.startRotateTo(0,vex::rotationUnits::deg,100,vex::velocityUnits::rpm);  
        liftRight.startRotateTo(0,vex::rotationUnits::deg,100,vex::velocityUnits::rpm);  
          } else if((liftLeft.rotation(vex::rotationUnits::deg)<5)&&(liftRight.rotation(vex::rotationUnits::deg)<5)){
            liftLeft.stop(vex::brakeType::coast);
            liftLeft.stop(vex::brakeType::coast);
              }else{
              liftLeft.stop(vex::brakeType::hold);
              liftRight.stop(vex::brakeType::hold);
                }

  //This is the end of the lift constructor.
 
  //This is the start of the main intake constructor.


  //this segment attatches the right shoulder button to the intake and checks if the intake is slipping.
  if(Controller1.ButtonR2.pressing()){
    intake();
    }else if(intakeRight.isSpinning()||intakeLeft.isSpinning()){
      intakeLeft.stop(vex::brakeType::hold);
      intakeRight.stop(vex::brakeType::hold);
      }else{
        intakeLeft.stop(vex::brakeType::coast);
        intakeRight.stop(vex::brakeType::coast);
      }

  //This is the beginning of targeted button presets. Feel free to set these aside to focus on the MVP
  //line sensor to line up cube with tower intake. 

  if(Controller1.ButtonUp.pressing()){
    liftTo(400,100,1);
    }else if(Controller1.ButtonDown.pressing()){

    }

  /*


  */

    vex::task::sleep(20);
  }
}

//This is the end of the teleop part of the code.

//This is the beginning of the main constructor for the VEX Competition Template.
int main() {
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    pre_auton();                        
    while(1) {
    }    
}

//This is the end of the main constructor for the VEX Competition Template.