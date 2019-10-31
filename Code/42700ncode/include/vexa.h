#include "vex.h"

//this is a custom function header file.

void drive(int lt, int rt, int cd, int ds){//initiates function drive with inputs left ticks, right ticks, and d speed
  //tells each motor to rotate for an amount(Not total.) motorName(distance,rotationUnit,speed,speedunits, blocking param
  leftDrive.startRotateFor(lt,vex::rotationUnits::deg,ds,vex::velocityUnits::pct);
  centerDrive.startRotateFor(cd,vex::rotationUnits::deg,ds,vex::velocityUnits::pct);
  rightDrive.startRotateFor(rt,vex::rotationUnits::deg,ds,vex::velocityUnits::pct);  
  
  Brain.resetTimer();//resets brain timer
  int timeout = 2000;//sets timeout time to 2 seconds. Create formula, largest rotation number / rpm + base?
  while((leftDrive.isSpinning()||rightDrive.isSpinning()||centerDrive.isSpinning() ) && Brain.timer(msec)<timeout){

  }//does not let program exit out of program until all drive motors have ceased spinning.
}
void pidDrive(int leftDriveDistanceTarget, int rightDriveDistanceTarget, int centerDriveDistanceTarget, int driveSpeedCap){
  leftDrive.resetRotation();
    centerDrive.resetRotation();

  rightDrive.resetRotation();
  Brain.resetTimer();
  int timeOutPeriod =  2000;//arbitrary timeout period 2 seconds.
  while((leftDrive.rotation(degrees)!=leftDriveDistanceTarget||centerDrive.rotation(degrees)!=centerDriveDistanceTarget||centerDrive.rotation(degrees)!=centerDriveDistanceTarget)&&timeOutPeriod){
    int leftDriveSpeed = 0;
    centerDrive.spin(fwd,leftDriveSpeed,pct);
    int rightDriveSpeed = 0;
    centerDrive.spin(fwd,leftDriveSpeed,pct);
    int centerDriveSpeed = 0;
    centerDrive.spin(fwd,leftDriveSpeed,pct);
  } 

}

void softMotion(int drivePower,int driveDuration){
  driveMotors.spin(fwd,drivePower,rpm);//tells motors to spin.
  wait(driveDuration,msec);//tells program to wait a bit before stopping.
  driveMotors.stop();//tells drive to stop.
  
}
void lift(int lh){ //initiates lift function with input lift height

  
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


/*void liftTo(int rotationTarget, int liftTopSpeed, int mode) {//This is the lift target constructor.


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
          */
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

