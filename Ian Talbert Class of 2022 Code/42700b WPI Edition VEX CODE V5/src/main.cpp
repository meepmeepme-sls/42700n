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

int frontliftop =0;
int frontliftlockout =0;
int rearliftop =3;

if(rearLift.rotation(deg)<-300){
  rearliftop =2;
}

int rearliftlockout =0;
bool intakeop =false; // true is fwd, false is stopped.
bool stingrotop = false; // true is ready to score; false is not
if(stingLift.rotation(deg)>600){
  stingrotop=true;
}
int stinglockout =0;
int intakecountop =0;
int intakelockout =0;

//pneumatic operators

int pneulockouta =-1;
int pneulockoutb =-1;
bool stingoutlock = true;
bool pneutrackera = true;
bool pneutrackerb = true;
pneuA.set(false);
pneuB.set(false);

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
    frontLift.spin(reverse,(frontLift.rotation(deg)+810),pct);
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

    if(Controller1.ButtonL2.pressing()&&rearliftlockout<0&&rearliftop>0){//down
      --rearliftop;
      rearliftlockout=5;
    }
    if(Controller1.ButtonL1.pressing()&&rearliftlockout<0&&rearliftop<3){//up
      ++rearliftop;
      rearliftlockout=5;
    }

  //rear lift movement

    if(rearliftop==2){
      rearLift.startRotateTo(-230,deg,100,rpm);
    }else if(rearliftop==1){
      rearLift.startRotateTo(-360,deg,100,rpm);
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

  //end rear lift control here

  //begin intake control here

    if(Controller1.ButtonX.pressing()){
      ++intakecountop;
        if(intakecountop>3){
            intakeop = false;
            intake.spin(reverse,100,pct);
            intakecountop=0;
            intakelockout =5;
        }else if(intakelockout<0){
          intakelockout =5;
          intakecountop =0;
          if(intakeop ==false){
            intake.spin(fwd,100,pct);
            intakeop = !intakeop;
            intakecountop =0;
          }else{
            intake.stop(coast);
            intakeop=!intakeop;
            intakecountop =0;
          }
        }
    }
    Controller1.Screen.newLine();
    Controller1.Screen.print(frontliftlockout);
    --intakelockout;
  //end intake control here

  //begin sting motor control here

  if(Controller1.ButtonA.pressing()&&stinglockout<0){
    stingrotop = !stingrotop;
    stinglockout = 5;
  }
  if(stingrotop == true&&stingLift.rotation(deg)<650){
   // stingLift.rotateTo(650,deg,100,rpm,false);
    stingLift.spin(fwd,100,pct);
  }else if(stingrotop==false&&stingLift.rotation(deg)>0){
   // stingLift.rotateTo(0,deg,100,rpm,false);
    stingLift.spin(reverse,100,pct);
  }else if(!stingLift.isSpinning()){
    stingLift.stop(hold);
  }

  if(Controller1.ButtonDown.pressing()){//allows resetting encoder position if desynced
    stingLift.spin(reverse,30,pct);
    stingLift.resetRotation();
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
      pneulockoutb = 5;
    }
  
    if(pneulockoutb>-1){
    --pneulockoutb;
  }
  //begin pneumatic sting control here
    if(Controller1.ButtonB.pressing()&&stingoutlock == true &&pneulockouta<0){
      pneuA.set(pneutrackera);
      pneutrackera = !pneutrackera;
      pneulockouta = 5;
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
    wait(100, msec);
  }
}
