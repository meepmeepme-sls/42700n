#include "vex.h"

int thresh = 20;//sets the lowest motor power state for the drive function. This will allow you to tune the curve of the P control for the drive function.

//basic autonomous functions. 
void drive(int lt, int rt, int ds){//initiates function drive with inputs left ticks, right ticks, and d speed
  //tells each motor to rotate for an amount(Not total.) motorName(distance,rotationUnit,speed,speedunits, blocking param
  //{Blocking param tells the robot to stop reading lines of code till this code is done running. for rotateTo and rotateFor its true by default})
  leftDrive.rotateFor(lt,vex::rotationUnits::deg,ds,vex::velocityUnits::rpm,false);
  rightDrive.rotateFor(rt,vex::rotationUnits::deg,ds,vex::velocityUnits::rpm);
}
void lift(int lh){ //initiates lift function with input lift height

  //tells both of the lift motors to rotate to a certain rotation value. Notice that rotateTo is to rotate to say 900deg, rotateFor rotates for 
  //900 deg instead.
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