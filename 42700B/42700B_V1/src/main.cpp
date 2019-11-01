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

#include "vex.h"
#include "funtions.h"
using namespace vex;

// A global instance of competition
competition Competition;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("42700B_V1");
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("Config Claw port7");
  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print("       FL port1 |BL port2 |FR port3");
  Brain.Screen.setCursor(4, 1);
  Brain.Screen.print("       BR port4 |AR port5 |AL port6");
}

/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */

void usercontrol(void) {
  // User control code here, inside the loop
  printf("%f battery", Brain.Battery.capacity());
  while (1) {
    //drive (tank)
    FL.spin(vex::directionType::fwd, Controller.Axis2.value(), vex::velocityUnits::pct);
    BL.spin(vex::directionType::fwd, Controller.Axis2.value(), vex::velocityUnits::pct);
    FR.spin(vex::directionType::fwd, Controller.Axis3.value(), vex::velocityUnits::pct);
    BR.spin(vex::directionType::fwd, Controller.Axis3.value(), vex::velocityUnits::pct);
    //arm
    //up
    if (Controller.ButtonL1.pressing()) {
      AL.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      AR.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    //down
    else if (Controller.ButtonL2.pressing()) {
      AL.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      AR.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    //stop
    else {
      AL.stop(vex::brakeType::brake);
      AR.stop(vex::brakeType::brake);
    }
    //claw
    //open
    if (Controller.ButtonR1.pressing()) {
      Claw.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    //down
    else if (Controller.ButtonR2.pressing()) {
      Claw.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    //stop
    else {
      Claw.stop(vex::brakeType::brake);
    }
    wait(20, msec); // Sleep the task for a short amount of time to prevent wasted resources.
  }
}
//dont worry about below__________________________________________________________________________
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
