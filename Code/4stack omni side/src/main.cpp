#include "vex.h"
using namespace vex;
vex::brain       Brain;
vex::competition Competition;
//start of user generated code.
int thresh = 20;//sets the lowest motor power state for the drive function. This will allow you to tune the curve of the P control for the drive function.

void drive(int lt, int rt, int ds){
  leftDrive.rotateFor(lt,vex::rotationUnits::deg,ds,vex::velocityUnits::rpm,false);
  rightDrive.rotateFor(rt,vex::rotationUnits::deg,ds,vex::velocityUnits::rpm);
}
void lift(int lh){
  liftLeft.rotateTo(lh,vex::rotationUnits::deg,100,vex::velocityUnits::rpm,false);
  liftRight.rotateTo(lh,vex::rotationUnits::deg,100,vex::velocityUnits::rpm);
} 
/*void drive(int leftTargetDistance, int rightTargetDistance, int driveTopSpeed) { //This is the drive constructor.

  while(leftDrive.rotation(vex::rotationUnits::deg)<leftTargetDistance){//This checks for completion of the drive function.

    int leftCurrentDistance = ( leftDrive.rotation(vex::rotationUnits::deg)  ); //These two lines set up a callback for the drive motor rotation values.
    int rightCurrentDistance = ( rightDrive.rotation(vex::rotationUnits::deg)  );
    int leftSpeed = 100*1-(leftCurrentDistance/ leftTargetDistance); //These two lines set up the P control.
    int rightSpeed = 100*1-(rightCurrentDistance/ rightTargetDistance); //These two lines set up the P control.
    
    leftDrive.startRotateTo(leftTargetDistance,vex::rotationUnits::deg,leftSpeed,vex::velocityUnits::rpm); //These two lines set the motor power for the drive function.
    rightDrive.startRotateTo(rightTargetDistance,vex::rotationUnits::deg,rightSpeed,vex::velocityUnits::rpm);
      }//end of while loop
      leftDrive.resetRotation(); //These two lines reset the motor encoders for maximum accuracy.
      rightDrive.resetRotation();
        }*/

void strafe(int strafingTargetDistance, int strafingTopSpeed){ //This is the strafing constructor.

  while(strafingDrive.rotation(vex::rotationUnits::deg)<strafingTargetDistance){//This checks for completion of the strafe function.

    int strafingCurrentSpeed = ( (thresh*strafingTopSpeed) + ((1-thresh)*strafingTopSpeed*(1-(strafingDrive.rotation(vex::rotationUnits::deg)/strafingTargetDistance) )  ) );
    strafingDrive.startRotateTo(strafingTargetDistance,vex::rotationUnits::deg,strafingCurrentSpeed,vex::velocityUnits::rpm);//This sets the motor power for the strafing motor.

    }

      }

void liftTo(int rotationTarget, int liftTopSpeed, int mode) {//This is the lift target constructor.


 /* while(liftLeft.rotation(vex::rotationUnits::deg)<rotationTarget){
    int liftCurrentDistance = ( liftLeft.rotation(vex::rotationUnits::deg) + liftRight.rotation(vex::rotationUnits::deg) )/2;

    int liftCurrentSpeed = ( (thresh*liftTopSpeed) + ((1-thresh)*liftTopSpeed*(1-(liftCurrentDistance/rotationTarget))  ) );

  if(mode==0){

    liftLeft.rotateTo(rotationTarget,vex::rotationUnits::deg,liftCurrentSpeed,vex::velocityUnits::rpm,false);

    liftRight.rotateTo(rotationTarget,vex::rotationUnits::deg,liftCurrentSpeed,vex::velocityUnits::rpm);
    }else if(mode==1){
      liftLeft.startRotateTo(rotationTarget,vex::rotationUnits::deg,liftCurrentSpeed,vex::velocityUnits::rpm);
      liftRight.startRotateTo(rotationTarget,vex::rotationUnits::deg,liftCurrentSpeed,vex::velocityUnits::rpm);
      
      }
        }*/ 
  
//This is an attempted re-write to allow the program to work in both Tele-OP and autonomous, saving lines of code.
    int liftCurrentDistance = ( liftLeft.rotation(vex::rotationUnits::deg) + liftRight.rotation(vex::rotationUnits::deg) )/2;

    int liftCurrentSpeed = liftTopSpeed;//( (thresh*liftTopSpeed) + ((1-thresh)*liftTopSpeed*(1-(liftCurrentDistance/rotationTarget))  ) );
  if(mode == 0){

    while(liftCurrentDistance<rotationTarget){
      
    int liftCurrentDistance = ( liftLeft.rotation(vex::rotationUnits::deg) + liftRight.rotation(vex::rotationUnits::deg) )/2;

    int liftCurrentSpeed = ( (thresh*liftTopSpeed) + ((1-thresh)*liftTopSpeed*(1-(liftCurrentDistance/rotationTarget))  ) );

    liftLeft.rotateTo(rotationTarget,vex::rotationUnits::deg,liftCurrentSpeed,vex::velocityUnits::rpm,false);

    liftRight.rotateTo(rotationTarget,vex::rotationUnits::deg,liftCurrentSpeed,vex::velocityUnits::rpm);

    }


    } else if(mode == 1){
      if(liftLeft.rotation(vex::rotationUnits::deg) < rotationTarget){
        liftLeft.spin(vex::directionType::rev,liftCurrentSpeed,vex::velocityUnits::rpm);
        liftRight.spin(vex::directionType::rev,liftCurrentSpeed,vex::velocityUnits::rpm);
        }else if(liftLeft.rotation(vex::rotationUnits::deg)>rotationTarget){
        liftLeft.spin(vex::directionType::fwd,liftCurrentSpeed,vex::velocityUnits::rpm);
        liftRight.spin(vex::directionType::fwd,liftCurrentSpeed,vex::velocityUnits::rpm);

        }else{
        liftLeft.stop();
        liftRight.stop();
        }
      }else{
        Controller1.Screen.print("You've set the wrong mode for lift func.");
      }
          }
void intake(int intakeMode){//This is the intake constructor.
  if(intakeMode == 0){//This part sets the intake to intake.
    intakeLeft.spin(vex::directionType::fwd,200,vex::velocityUnits::rpm);
    intakeRight.spin(vex::directionType::fwd,200,vex::velocityUnits::rpm);
    }else if(intakeMode == 1){//This part sets the intake to outtake.
    intakeLeft.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);
    intakeRight.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);
      }else{//This part sets the intake to stop running.
      intakeLeft.stop();
      intakeRight.stop();
      }
}
void pre_auton( void ) {//Clears all motor encoders upon start of user program.
  leftDrive.resetRotation();
  rightDrive.resetRotation();
  liftLeft.resetRotation();
  liftRight.resetRotation();
  strafingDrive.resetRotation();
  intakeLeft.resetRotation();
  intakeRight.resetRotation();
  tilterMotor.resetRotation();
}
void autonomous( void ) {
  intake(1);
  vex::task::sleep(3000);
  intake(0);
  vex::task::sleep(500);
  lift(100);
  lift(0);
  drive(700,700,100);
  drive(-300,-300,200);
}

void usercontrol( void ) {
  while (1) {
    //Drive part.
    int leftDriveSpeed = ((Controller1.Axis3.value()) + -1*Controller1.Axis1.value());
    int rightDriveSpeed = (( Controller1.Axis3.value() )+Controller1.Axis1.value());
    int strafingSpeed = (1*Controller1.Axis4.value());

    leftDrive.spin(vex::directionType::fwd,leftDriveSpeed,vex::velocityUnits::pct);
    rightDrive.spin(vex::directionType::fwd,rightDriveSpeed,vex::velocityUnits::pct);
    strafingDrive.spin(vex::directionType::fwd,strafingSpeed,vex::velocityUnits::pct);
    //End of drive.
    int medliftSpeed = 15+ 100*(1-((liftLeft.rotation(vex::rotationUnits::deg))/320 ));
    int highliftSpeed = 15+ 100*(1-((liftLeft.rotation(vex::rotationUnits::deg))/350 ));
    int topliftSpeed = 15+ 100*(1-((liftLeft.rotation(vex::rotationUnits::deg))/660 ));
    int downliftSpeed = 15+ 100*(((liftLeft.rotation(vex::rotationUnits::deg))/2 ));

    if(Controller1.ButtonLeft.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)<320){
      liftLeft.spin(vex::directionType::fwd,medliftSpeed,vex::velocityUnits::rpm);
      liftRight.spin(vex::directionType::fwd,medliftSpeed,vex::velocityUnits::rpm);
    }if(Controller1.ButtonUp.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)<350){
      liftLeft.spin(vex::directionType::fwd,highliftSpeed,vex::velocityUnits::rpm);
      liftRight.spin(vex::directionType::fwd,highliftSpeed,vex::velocityUnits::rpm);
    }if(Controller1.ButtonRight.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)<660){
      liftLeft.spin(vex::directionType::fwd,topliftSpeed,vex::velocityUnits::rpm);
      liftRight.spin(vex::directionType::fwd,topliftSpeed,vex::velocityUnits::rpm);
    }if(Controller1.ButtonDown.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)>0){
      liftLeft.spin(vex::directionType::rev,downliftSpeed,vex::velocityUnits::rpm);
      liftRight.spin(vex::directionType::rev,downliftSpeed,vex::velocityUnits::rpm);
    }
    Controller1.Screen.print (medliftSpeed);

    if(Controller1.ButtonL1.pressing()){
      liftLeft.spin(vex::directionType::fwd,100,vex::velocityUnits::rpm);
      liftRight.spin(vex::directionType::fwd,100,vex::velocityUnits::rpm);
    }else if(Controller1.ButtonL2.pressing()){
      liftLeft.spin(vex::directionType::rev,100,vex::velocityUnits::rpm);
      liftRight.spin(vex::directionType::rev,100,vex::velocityUnits::rpm);
    }else{
      liftLeft.stop(vex::brakeType::hold);
      liftRight.stop(vex::brakeType::hold);
    }
int tilterSpeed = 20+100*(1-(tilterMotor.rotation(vex::rotationUnits::deg)/820));
    if(Controller1.ButtonX.pressing()){
      tilterMotor.spin(vex::directionType::fwd,tilterSpeed,vex::velocityUnits::rpm);
    }else
    if(Controller1.ButtonY.pressing()){
      tilterMotor.spin(vex::directionType::rev,60,vex::velocityUnits::rpm);
    }else{
      tilterMotor.stop(vex::brakeType::brake);
    }
    if(Controller1.ButtonR1.pressing()){
      intakeLeft.spin(vex::directionType::fwd,200,vex::velocityUnits::rpm);
      intakeRight.spin(vex::directionType::fwd,200,vex::velocityUnits::rpm);
    }else if(Controller1.ButtonR2.pressing()){
      intakeLeft.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);
      intakeRight.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);

    }else{
      intakeLeft.stop(vex::brakeType::brake);
      intakeRight.stop(vex::brakeType::brake);
    }
    if(Controller1.ButtonB.pressing()){
      tilterMotor.rotateTo(0,vex::rotationUnits::deg,100,vex::velocityUnits::rpm);
    }
  }
}int main() {
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    pre_auton();
    while(1) {
      vex::task::sleep(100);
    }    
       
}