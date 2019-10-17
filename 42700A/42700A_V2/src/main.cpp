#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

int ToggleState;

void ToggleButton(){
  while(true){
    vex::this_thread::sleep_for(10);
    //tank drive
    if(Controller1.ButtonY.pressing()==true&&ToggleState == false){
      Controller1.Screen.print ("Warning                           .");
      ToggleState = true;
      vex::this_thread::sleep_for(100);
    }
    //arcade drive
    else if(Controller1.ButtonY.pressing()==true&&ToggleState == true) {
      Controller1.Screen.print ("Warning                           .");
      vex::this_thread::sleep_for(100);
      ToggleState=false;
    }
  }
}

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    
    //drive
    if (ToggleState == true) {
        Controller1.Screen.print("Tank Drive                           .");
      Brain.Screen.setCursor(2, 0);
      Brain.Screen.print("Tank Drive ");
      LF.spin(vex::directionType::fwd,Controller1.Axis3.value() + Controller1.Axis4.value(),vex::velocityUnits::pct);
      LB.spin(vex::directionType::fwd,Controller1.Axis3.value() - Controller1.Axis4.value(),vex::velocityUnits::pct);
      RF.spin(vex::directionType::fwd,-Controller1.Axis2.value() + Controller1.Axis1.value(), vex::velocityUnits::pct);
      RB.spin(vex::directionType::fwd,-Controller1.Axis2.value() - Controller1.Axis1.value(),vex::velocityUnits::pct);
    }
    // arcade drive mode|Y button is the toggle
    else if (ToggleState == false) {
        Controller1.Screen.print("Arcade Drive  ");
      Brain.Screen.setCursor(2, 0);
      Brain.Screen.print("Arcade Drive  ");
      LF.spin(vex::directionType::fwd,Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value(), vex::velocityUnits::pct);
      RF.spin(vex::directionType::fwd,-Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
      RB.spin(vex::directionType::fwd,-Controller1.Axis3.value() - Controller1.Axis4.value() +Controller1.Axis1.value(),vex::velocityUnits::pct);
      LB.spin(vex::directionType::fwd,Controller1.Axis3.value() - Controller1.Axis4.value() +Controller1.Axis1.value(),vex::velocityUnits::pct);
    }
    //lift
    if(Controller1.ButtonL1.pressing()) {
      Lift.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonL2.pressing()) {
      Lift.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    else{
      Lift.setBrake(brake);
    }
    //intake
    if(Controller1.ButtonR2.pressing()) {
      LI.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      RI.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonR1.pressing()) {
      LI.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      RI.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    else{
      LI.setBrake(brake);
      RI.setBrake(brake);
    }
    //tilter
    if(Controller1.ButtonX.pressing()) {
      tilter.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonA.pressing()) {
      tilter.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    else{
      tilter.setBrake(brake);
    }
    
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
