/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFI700GURED DEVICES ----

#include "functions.h"

using namespace vex;

// A global instance of competition
competition Competition;



// define your global instances of motors and other devices here
int motorspeed;
int rearmotorspeed;

void usercontrol(void) {
bool pneutrackera = true;
  // User control code here, inside the loop
  while (1) {

    int leftDriveSpeed = ((Controller1.Axis3.value()) - Controller1.Axis1.value());// just some arcade coding. 
    int rightDriveSpeed = (( Controller1.Axis3.value())+Controller1.Axis1.value());

    backLeftDrive.spin(vex::directionType::fwd,leftDriveSpeed,vex::velocityUnits::pct);
    frontLeftDrive.spin(vex::directionType::fwd,leftDriveSpeed,vex::velocityUnits::pct);
    backRightDrive.spin(vex::directionType::fwd,rightDriveSpeed,vex::velocityUnits::pct);
    frontRightDrive.spin(vex::directionType::fwd,rightDriveSpeed,vex::velocityUnits::pct);

    if(Controller1.ButtonR1.pressing()==1 && frontLift.rotation(degrees)<800 ){
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

    

    if(Controller1.ButtonL1.pressing()==1 && rearLift.rotation(degrees)<0 ){
      rearmotorspeed = ((abs(frontLift.rotation(degrees)-700)/4)+20);
      rearLift.spin(fwd,rearmotorspeed,pct);
    }else if(Controller1.ButtonL2.pressing()==1&&rearLift.rotation(deg)>-450){
      rearmotorspeed = (abs(700-frontLift.rotation(degrees)/4)+20);
      rearLift.spin(reverse,rearmotorspeed,pct);
    }else

    if(Controller1.ButtonLeft.pressing()==1){
      rearLift.rotateTo(300,degrees,200,rpm);
    }else{
      rearLift.stop(hold);
    }

    if(Controller1.ButtonX.pressing()==1){
      intake.spin(fwd,100,pct);
    }else if(Controller1.ButtonB.pressing()==1){
      intake.spin(reverse,100,pct);
    }else if(Controller1.ButtonY.pressing()==1){
      intake.stop(coast);
    }

    if(Controller1.ButtonDown.pressing()==1){
      pneuA.set(pneutrackera);
      pneutrackera = !pneutrackera;
    }

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
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
