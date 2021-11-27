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
int rearliftop =2;
int rearliftlockout =0;
bool intakeop =false; // true is fwd, false is stopped.
bool stingrotop = false; // true is ready to score; false is not
int stinglockout =0;
int intakecountop =0;
int intakelockout =0;

//pneumatic operators

int pneulockouta, pneulockoutb;
bool stingoutlock = false;
bool pneutrackera = true;
bool pneutrackerb = true;

  // User control code here, inside the loop
  while (1) {

  //begin drive controls

    int leftDriveSpeed = ((Controller1.Axis3.value()) - Controller1.Axis1.value());// just some arcade coding. 
    int rightDriveSpeed = (( Controller1.Axis3.value())+Controller1.Axis1.value());

    backLeftDrive.spin(vex::directionType::fwd,leftDriveSpeed,vex::velocityUnits::pct);
    frontLeftDrive.spin(vex::directionType::fwd,leftDriveSpeed,vex::velocityUnits::pct);
    backRightDrive.spin(vex::directionType::fwd,rightDriveSpeed,vex::velocityUnits::pct);
    frontRightDrive.spin(vex::directionType::fwd,rightDriveSpeed,vex::velocityUnits::pct);

  //end drive control

  //begin front (4 bar mogo bridge lift) control here

    if(Controller1.ButtonR1.pressing()==1 && frontLift.rotation(degrees)>800 ){
      motorspeed = (abs(frontLift.rotation(degrees)-800)+20);
      frontLift.spin(fwd,motorspeed,pct);
    }else if(Controller1.ButtonR2.pressing()==1&&frontLift.rotation(deg)>0){
      motorspeed = (((frontLift.rotation(degrees)+450)/4)+40);
      frontLift.spin(reverse,motorspeed,pct);
    }else if(Controller1.ButtonA.pressing()==1){  
      frontLift.rotateTo(0,degrees,100,vex::velocityUnits::pct,false);
    }else{
      frontLift.stop(brake);
    }

  //end front lift control here.

  //begin rear lift control here.

  //operator stuff

    if(Controller1.ButtonL1.pressing()&&rearliftlockout<0&&rearliftop>0){//down
      --rearliftop;
      rearliftlockout=50;
    }
    if(Controller1.ButtonL2.pressing()&&rearliftlockout<0&&rearliftop<2){//up
      ++rearliftop;
      rearliftlockout=50;
    }

  //rear lift movement

    if(rearliftop==1){
      rearLift.startRotateTo(-200,deg,100,rpm);
    }else if(rearliftop==0){
      rearLift.startRotateTo(-450,deg,100,rpm);
    }else if(rearliftop ==2){
      rearLift.startRotateTo(0,deg,100,rpm);
    }else if(!rearLift.isSpinning()){
      rearLift.stop(hold);
    }

  //end rear lift control here

  //begin intake control here

    if(Controller1.ButtonX.pressing()){
      ++intakecountop;
        if(intakecountop>75){
            intakeop = false;
            intake.spin(reverse);
            intakecountop=0;
            intakelockout =100;
        }else if(intakelockout<0){
          intakelockout =100;
          if(intakeop ==false){
            intake.spin(fwd);
            intakeop = !intakeop;
          }else{
            intake.stop(coast);
            intakeop=!intakeop;
          }
        }
    }
    --intakelockout;
  //end intake control here

  //begin sting motor control here

  if(Controller1.ButtonA.pressing()&&stinglockout<0){
    stingrotop = !stingrotop;
    stinglockout = 100;
  }
  if(stingrotop == true){
    stingLift.rotateTo(100,deg,100,rpm);
  }else if(stingrotop==false){
    stingLift.rotateTo(0,deg,100,rpm);
  }else if(!stingLift.isSpinning()){
    stingLift.stop(hold);
  }
  --stinglockout;
  //end sting motor control here

    //begin pneumatic control here

  //begin pneumatic claw control here

  if(Controller1.ButtonRight.pressing()==1){
      pneuB.set(pneutrackerb);
      pneutrackerb = !pneutrackerb;
      pneulockoutb = 100;
    }

  //begin pneumatic sting control here

    if(Controller1.ButtonY.pressing()==1&&stingoutlock == true){
      pneuA.set(pneutrackera);
      pneutrackera = !pneutrackera;
      pneulockouta = 100;
    }

  //end pneumatic control here

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    --pneulockouta;
    --pneulockoutb;

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
