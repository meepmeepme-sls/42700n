/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "functions.h"

using namespace vex;

// A global instance of competition
competition Competition;



// define your global instances of motors and other devices here
int motorspeed;
int rearmotorspeed;

void usercontrol(void) {

//motor operators
int rearliftop =3;

if(rearLift.rotation(deg)<-10){
  rearliftop =0;
}

int rearliftlockout =0;
bool intakeop =false; // true is fwd, false is stopped.
int stingrotop = 0; //0 is down position, 1 is driving position, 2 is scoring position
if(stingLift.rotation(deg)>290){
  stingrotop=1;
}else{
  stingrotop=0;
}
int stingcountop =0;
int stinglockout =0;
int intakecountop =0;
int intakelockout =0;

//pneumatic operators

int pneulockouta =-1;
int pneulockoutb =-1;
bool stingoutlock = true;
bool pneutrackera = true;
bool pneutrackerb = !pneuB.value();
pneuA.set(false);

  // User control code here, inside the loop
  while (1) {

  //begin drive controls

    int leftDriveSpeed = ((Controller1.Axis3.value()) + Controller1.Axis1.value());// just some arcade coding. 
    int rightDriveSpeed = (( Controller1.Axis3.value())-Controller1.Axis1.value());

    backLeftDrive.spin(vex::directionType::fwd,leftDriveSpeed,vex::velocityUnits::pct);
    frontLeftDrive.spin(vex::directionType::fwd,leftDriveSpeed,vex::velocityUnits::pct);
    backRightDrive.spin(vex::directionType::fwd,rightDriveSpeed,vex::velocityUnits::pct);
    frontRightDrive.spin(vex::directionType::fwd,rightDriveSpeed,vex::velocityUnits::pct);

  //end drive control.

  //begin front (4 bar mogo bridge lift) control here.
/*
    //operator stuff.

    if(Controller1.ButtonR2.pressing()&&frontliftlockout<0&&frontliftop>1){//down
      --frontliftop;
      frontliftlockout=3;
    }
    if(Controller1.ButtonR1.pressing()&&frontliftlockout<0&&frontliftop<3){//up
      ++frontliftop;
      frontliftlockout=3;
    }

  //front lift movement.

    if(frontliftop==1){
      frontLift.startRotateTo(100,deg,100,rpm);
    }else if(frontliftop==0){
      frontLift.startRotateTo(0,deg,100,rpm);
    }else if(frontliftop ==2){
      if(frontLift.rotation(deg)<400){
        stingrotop = true;
      }
      frontLift.startRotateTo(400,deg,100,rpm);
    }else if(frontliftop ==3){
      frontLift.startRotateTo(800,deg,100,rpm);
    }else if(!frontLift.isSpinning()){
      frontLift.stop(hold);
    }
  if(frontliftlockout>-1){
    --frontliftlockout;
  }

  */

  if(Controller1.ButtonR1.pressing()&&frontLift.rotation(deg)>-810){//up
    frontLift.spin(reverse,(frontLift.rotation(deg)+830),pct);
  }else if(Controller1.ButtonR2.pressing()&&frontLift.rotation(deg)<20){//down
    frontLift.spin(fwd,abs(frontLift.rotation(deg)-20),pct);    
  }else{
    frontLift.stop(hold);
  }

  if(Controller1.ButtonLeft.pressing()){//allows resetting encoder position if desynced
    frontLift.spin(fwd,30,pct);
    frontLift.resetRotation();
  }

  //end front lift control here.

  //begin rear lift control here.

  //operator stuff

    if(Controller1.ButtonL2.pressing()&&rearliftlockout<0&&rearliftop>-1){//down
      --rearliftop;
      rearliftlockout=15;
    }
    if(Controller1.ButtonL1.pressing()&&rearliftlockout<0&&rearliftop<3){//up
      ++rearliftop;
      rearliftlockout=15;
    }

  //rear lift movement

    if(rearliftop==2){
      rearLift.startRotateTo(-225,deg,100,rpm);
    }else if(rearliftop==-1){
      rearLift.startRotateTo(-570,deg,100,rpm);
    }else   if(rearliftop==1){
      rearLift.startRotateTo(-330,deg,100,rpm);
    }else if(rearliftop==0){
      rearLift.startRotateTo(-480,deg,100,rpm);
    }else if(rearliftop ==3){
      rearLift.startRotateTo(0,deg,100,rpm);
    }else if(!rearLift.isSpinning()){
      rearLift.stop(hold);
    }

    if(rearliftlockout>-1){
      --rearliftlockout;
    }
    if(Controller1.ButtonUp.pressing()){
      rearLift.spin(fwd,100,rpm);
      rearLift.resetRotation();
    }

  //end rear lift control here

  //begin intake control here

    if(Controller1.ButtonX.pressing()){
      ++intakecountop;
        if(intakecountop>20){
            intakeop = false;
            intake.spin(reverse,100,pct);
            intakecountop=0;
            intakelockout =25;
        }else if(intakelockout<0){
          intakelockout =25;
          intakecountop =0;
          if(intakeop ==false){
            intake.spin(fwd,90,pct);
            if(stingrotop==0){
              intake.spin(fwd,75,pct);
            }
            intakeop = !intakeop;
            intakecountop =0;
          }else{
            intake.stop(coast);
            intakeop=!intakeop;
            intakecountop =0;
          }
        }
    }
    --intakelockout;
  //end intake control here

  //begin sting motor control here

  if(Controller1.ButtonA.pressing()){
      ++stingcountop;
        if(stingcountop>20){
            stingrotop =2;
            stingcountop=0;
            stinglockout =25;
        }else if(stinglockout<0){
          stinglockout =25;
          stingcountop =0;
          if(stingrotop ==0){
            stingrotop=1;
          }else{
            stingrotop=0;
          }
        }
    }
  if(Controller1.ButtonRight.pressing()){
    stingrotop = 3;
  }

  if(stingrotop == 3){
    stingLift.startRotateTo(900,deg,100,rpm);
  }else
  if(stingrotop == 2){
   // stingLift.rotateTo(650,deg,100,rpm,false);
    //stingLift.spin(fwd,100,pct);
    stingLift.startRotateTo(630,deg,100,rpm);
  }else if(stingrotop == 1){
   // stingLift.rotateTo(650,deg,100,rpm,false);
    stingLift.startRotateTo(330,deg,100,rpm);
  }else if(stingrotop==0){
   // stingLift.rotateTo(0,deg,100,rpm,false);
    //stingLift.spin(reverse,100,pct);
    stingLift.startRotateTo(0,deg,100,rpm);
  }else if(!stingLift.isSpinning()){
    //stingLift.stop(hold);
    //if(Controller1.ButtonUp.pressing()){
      //stingLift.resetRotation();
    //}
  }

  if(Controller1.ButtonDown.pressing()){//allows resetting encoder position if desynced
    stingLift.spin(reverse,30,pct);
    stingrotop=4;
    stingLift.resetRotation();
  }else if(!stingLift.isSpinning()){
    stingLift.stop(hold);
  }

  if(stinglockout>-1){
    --stinglockout;
  }

  //end sting motor control here

    //begin pneumatic control here

  //begin pneumatic claw control here

  if(Controller1.ButtonY.pressing()&&pneulockoutb<0){
      pneuB.set(pneutrackerb);
      pneutrackerb = !pneutrackerb;
      pneulockoutb = 25;
    }
  
    if(pneulockoutb>-1){
    --pneulockoutb;
  }
  //begin pneumatic sting control here
    if(Controller1.ButtonB.pressing()&&stingoutlock == true &&pneulockouta<0){
      pneuA.set(pneutrackera);
      pneutrackera = !pneutrackera;
      pneulockouta = 25;
    }
    if(pneulockouta>-1){
    --pneulockouta;
  }

  //end pneumatic control here

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

  //int cleanup

  

    wait(10, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }//end of while loop
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    Controller1.Screen.print(potGauto.value(pct));
    Controller1.Screen.newLine();
    wait(100, msec);
  }
}