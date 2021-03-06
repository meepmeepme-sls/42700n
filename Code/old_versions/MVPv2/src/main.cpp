//This begins VEX Competition Template constructors.
#include "vex.h"
using namespace vex;
vex::brain       Brain;
vex::competition Competition;
  //This is the end of VEX Competition Template Constructors.

//This is the beginning of autonomous function calleftBackDriveack constructors.

//this function is for going straight

    int thresh = 20;
void drive(int dist,int fast) {

  while(leftFrontDrive.rotation(vex::rotationUnits::deg)<dist){

    int currentdist = ( leftFrontDrive.rotation(vex::rotationUnits::deg) + leftBackDrive.rotation(vex::rotationUnits::deg) + rightFrontDrive.rotation(vex::rotationUnits::deg) + rightBackDrive.rotation(vex::rotationUnits::deg)  )/4;
    int topspeed = ( (thresh*fast) + ((1-thresh)*fast*(1-(currentdist/dist))  ) );

    leftFrontDrive.startRotateTo(dist,vex::rotationUnits::deg,topspeed,vex::velocityUnits::rpm);
    leftBackDrive.startRotateTo(dist,vex::rotationUnits::deg,topspeed,vex::velocityUnits::rpm);
    rightFrontDrive.startRotateTo(dist,vex::rotationUnits::deg,topspeed,vex::velocityUnits::rpm);
    rightBackDrive.startRotateTo(dist,vex::rotationUnits::deg,topspeed,vex::velocityUnits::rpm);
      }//end of while loop
      leftFrontDrive.resetRotation();
      leftBackDrive.resetRotation();
      rightFrontDrive.resetRotation();
      rightBackDrive.resetRotation();
        }

void turn(int ldist, int rdist, int tspeed){
  int lrot = (leftFrontDrive.rotation(vex::rotationUnits::deg)+leftBackDrive.rotation(vex::rotationUnits::deg)/2);
  int rrot = (rightFrontDrive.rotation(vex::rotationUnits::deg)+rightBackDrive.rotation(vex::rotationUnits::deg)/2);


  int lspeed = (tspeed * (1- (lrot) / (ldist-thresh) ) );
  int rspeed = (tspeed * (1- (rrot) / (ldist-thresh) ) );
  
  while(ldist<leftFrontDrive.rotation(vex::rotationUnits::deg)&&rdist<rightFrontDrive.rotation(vex::rotationUnits::deg)){
    leftFrontDrive.startRotateTo(ldist,vex::rotationUnits::deg,lspeed,vex::velocityUnits::rpm);
    leftBackDrive.startRotateTo(ldist,vex::rotationUnits::deg,lspeed,vex::velocityUnits::rpm);
    rightFrontDrive.startRotateTo(rdist,vex::rotationUnits::deg,rspeed,vex::velocityUnits::rpm);
    rightBackDrive.startRotateTo(rdist,vex::rotationUnits::deg,rspeed,vex::velocityUnits::rpm);

    }//end of while loop
      leftFrontDrive.resetRotation();
      leftBackDrive.resetRotation();
      rightFrontDrive.resetRotation();
      rightBackDrive.resetRotation();
      }

void liftTo(int rot, int pow, int f) {
  if(f==0){
    liftLeft.rotateTo(rot,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    liftRight.rotateTo(rot,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    }else if(f==1){
      liftLeft.rotateTo(rot,vex::rotationUnits::deg,pow,vex::velocityUnits::pct,false);
      liftRight.rotateTo(rot,vex::rotationUnits::deg,pow,vex::velocityUnits::pct,false);

      }
}

void intake(){
  intakeLeft.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
  intakeRight.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
}

/*
void intakeout(){
  mi.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
}
void intakein(){
  mi.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
}
void gin(){
    ir.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
    il.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
}
void gout(){
    ir.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
    il.spin(vex::directionType::rev,100,vex::velocityUnits::pct);

}
*/

  //This is the end of autonomous function calleftBackDriveack constructors.

void pre_auton( void ) {
  
}

void autonomous( void ) {
  liftTo(900,100,0);
  drive(900,200);
}

//This is the beginning of the teleop part of the code. It's broken into three parts: Drive, Lift, and Intakes.

void usercontrol( void ) {
  while (1) {
  
  //This is the beginning of the drive constructor.
  int dz = 15;
  
  //These are ternary operators. I'm using them so that the controller is less sensitive. If the value of the joystick does not exceed a certain value it will set the value to zero.
  int joyStickAxis3 = Controller1.Axis3.value();
  joyStickAxis3 = abs(joyStickAxis3) > dz ? joyStickAxis3 : 0;
  int joyStickAxis2 = Controller1.Axis2.value();
  joyStickAxis2 = abs(joyStickAxis2) > dz ? joyStickAxis2 : 0;

      //connects the joysticks with the drive
      leftFrontDrive.spin(vex::directionType::fwd, joyStickAxis3, vex::velocityUnits::pct);
      rightFrontDrive.spin(vex::directionType::fwd, joyStickAxis2, vex::velocityUnits::pct);
      leftBackDrive.spin(vex::directionType::fwd, joyStickAxis3, vex::velocityUnits::pct);
      rightBackDrive.spin(vex::directionType::fwd, joyStickAxis2, vex::velocityUnits::pct);

  //This is the end of the drive constructor.

  //This is the beginning of the lift constructor.

  //connects the lift to the shoulder buttons.
  int stopCheck = (liftLeft.velocity(vex::velocityUnits::rpm) + liftRight.velocity(vex::velocityUnits::rpm) )/2;

  if(Controller1.ButtonL1.pressing()){
    liftLeft.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
    liftRight.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
      //this check stops the lift from stalling out on top, and lets me know when it is.
      if(stopCheck<20){
        liftLeft.stop(vex::brakeType::coast);
        liftRight.stop(vex::brakeType::coast);
        Controller1.rumble(".....");
      }
        } else if(Controller1.ButtonL2.pressing()){
        liftLeft.startRotateTo(0,vex::rotationUnits::deg,100,vex::velocityUnits::pct);  
        liftRight.startRotateTo(0,vex::rotationUnits::deg,100,vex::velocityUnits::pct);  
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