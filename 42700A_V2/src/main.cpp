#include "vex.h"
#include "funtions.h"
#include "visionModuel.h"
using namespace vex;

// A global instance of competition
competition Competition;
/*
int ToggleState;

void ToggleButton(){
  while(1){
    //vex::this_thread::sleep_for(10);
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
*/
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
  autoselectdisplay();
  
  
  /*some config stuff
  Omni 2.75" = 69.85mm | Standerd 2.75" = 69.85mm | Traction 3.25" = 82.55mm
  Omni 3.25" = 82.55mm | Standerd 4"    = 101.6mm | Traction 4"    = 101.6mm
  Omni 4"    = 101.6mm | Standerd 5"    = 127mm   | Mecanum 4"     = 101.6mm
  in mm for move foward*/
  WheelDiameter = 8255/100;  //is 82.55mm but c++ dosent like decimals in numbers
  
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
  static bool Red;
  //deploy intake and tray
  Lift.rotateFor(fwd, 500, deg);
  //wait(100);
  Lift.rotateFor(fwd, 500, deg, false);
  
  //auto select
  //1
  if (notweed.value(pct) <= 16 && notweed.value(pct) >= 0){
  dz(100, -375);
  dz(100, 100);  
  }
  //2
  else if (notweed.value(pct) >= 17 && notweed.value(pct) <= 33){
  dx(200, 500);
  wait(1, sec);
  LI.spin(fwd);
  RI.spin(reverse);
  dx(100, 450);
  dy(100, 45);
  dx(100, 450);
  Lift.spinFor(fwd, 90, deg);
  LI.spin(reverse);
  RI.spin(fwd);
  dx(100, -150);
  }
  //3
  else if (notweed.value(pct) >= 34 && notweed.value(pct) <= 50) {
    visionAuto(Red, 10, 150, 105, 210);
  }
  //4
  else if (notweed.value(pct) >= 51 && notweed.value(pct) <= 67) {
  dz(100, 375);
  dz(100, -100);
  } 
  //5
  else if (notweed.value(pct) >= 68 && notweed.value(pct) <= 84) {

  } 
  //6
  else if (notweed.value(pct) >= 85 && notweed.value(pct) <= 100) {

  }
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
  //Vision signiture varibles
  static bool Red;

  //ToggleState=false;
  // User control code here, inside the loop
  while (1) {
    //drive
    LF.spin(vex::directionType::fwd,Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value(), vex::velocityUnits::pct);
    RF.spin(vex::directionType::fwd,-Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
    RB.spin(vex::directionType::fwd,-Controller1.Axis3.value() - Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
    LB.spin(vex::directionType::fwd,Controller1.Axis3.value() - Controller1.Axis4.value() + Controller1.Axis1.value(), vex::velocityUnits::pct);
    
    //lift
    if(Controller1.ButtonL1.pressing()) {
      Lift.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonL2.pressing()) {
      Lift.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    else{
      Lift.stop(brake);
    }
    
    //intake
    if(Controller1.ButtonR2.pressing()) {
      LI.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      RI.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonR1.pressing()) {
      LI.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      RI.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    else{
      LI.stop(brake);
      RI.stop(brake);
    }

    //tilter
    if(Controller1.ButtonX.pressing()) {
      tilter.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonA.pressing()) {
      tilter.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    else{
      tilter.stop(brake);
    }
    
    //vision test
    if(Controller1.ButtonLeft.pressing()){
      visionDriver(Red, 10, 50, 105, 210);
    }
    else if(Controller1.ButtonRight.pressing()){
      visionDriver(Red, 10, 50, 105, 210);
    }
    else if (Controller1.ButtonUp.pressing()){
      visionDriver(Red, 10, 50, 105, 210);
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
