#include "vexb.h"

using namespace vex;

// A global instance of competition
competition Competition;

//basic autonomous functions. 



void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {//Drive part. Axis1 is the left to right on the left stick. Axis3 is up and down on the left stick. Axis 4 is right and left on the right stick.
    int leftDriveSpeed = ((Controller1.Axis3.value()) + Controller1.Axis1.value());// just some arcade coding. 
    int rightDriveSpeed = (( Controller1.Axis3.value())-Controller1.Axis1.value());
   // int strafingSpeed = ((Controller1.Axis3.value())-Controller1.Axis1.value()+ Controller1.Axis1.value() );
  int strafingSpeed = (Controller1.Axis3.value());

  int intakeSpeed = 100;
  Controller1.Screen.clearLine();
//Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("%d", autonomousSelector.value(vex::analogUnits::range12bit));

  //if|then statement you know the drill. This one is checking if ButtonB is being pressed on Controller1.
if(Controller1.ButtonB.pressing()==0){
    leftDrive.spin(vex::directionType::fwd,leftDriveSpeed,vex::velocityUnits::pct);
    rightDrive.spin(vex::directionType::fwd,rightDriveSpeed,vex::velocityUnits::pct);
    centerDrive.spin(vex::directionType::fwd,strafingSpeed,vex::velocityUnits::pct);
   }   //End of drive.
   /* int medliftSpeed = 15+ 100*(1-((liftLeft.rotation(vex::rotationUnits::deg))/320 ));*/
    if(Controller1.ButtonLeft.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)){
      liftLeft.rotateTo(320,degrees,100,rpm,false);
      liftRight.rotateTo(320,degrees,100,rpm);
    }if(Controller1.ButtonUp.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)){
      liftLeft.rotateTo(350,degrees,100,rpm,false);
      liftRight.rotateTo(350,degrees,100,rpm);
    }if(Controller1.ButtonRight.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)){
      liftLeft.rotateTo(600,degrees,100,rpm,false);
      liftRight.rotateTo(600,degrees,100,rpm);
    }if(Controller1.ButtonDown.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)>0){
      liftLeft.rotateTo(0,degrees,100,rpm,false);
      liftRight.rotateTo(0,degrees,100,rpm);
    }

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

    //tilt & intake 
    if(liftLeft.rotation(degrees)>200){
      intakeSpeed = 150;
    }else{
      intakeSpeed =200;
    }
int tilterSpeed = 100*(1-(tilterMotor.rotation(vex::rotationUnits::deg)/600));
    if(tilterSpeed<10){
      tilterSpeed=10;
    }
    if(Controller1.ButtonX.pressing()&&(tilterMotor.rotation(vex::rotationUnits::deg)<600)){
      tilterMotor.spin(vex::directionType::fwd,tilterSpeed,vex::velocityUnits::rpm);
      if(tilterMotor.rotation(vex::rotationUnits::deg)>700){
        intakeLeft.spin(vex::directionType::rev,15,vex::velocityUnits::rpm);
        intakeRight.spin(vex::directionType::rev,15,vex::velocityUnits::rpm);
      }
    }else
    if(Controller1.ButtonY.pressing()&&tilterMotor.rotation(vex::rotationUnits::deg)>0){
      tilterMotor.spin(vex::directionType::rev,100,vex::velocityUnits::rpm);
    }else{
      tilterMotor.stop(vex::brakeType::brake);
    }
    if(Controller1.ButtonR2.pressing()){
      intakeLeft.spin(vex::directionType::rev,intakeSpeed,vex::velocityUnits::rpm);
      intakeRight.spin(vex::directionType::rev,intakeSpeed,vex::velocityUnits::rpm);

    }else 
    if(Controller1.ButtonR1.pressing()){
      intakeLeft.spin(vex::directionType::fwd,200,vex::velocityUnits::rpm);
      intakeRight.spin(vex::directionType::fwd,200,vex::velocityUnits::rpm);
    }else{
      intakeLeft.stop(vex::brakeType::hold);
      intakeRight.stop(vex::brakeType::hold);
    }

    //stack outtake 
    if(Controller1.ButtonB.pressing()){
      intakeLeft.spin(vex::directionType::rev,140,vex::velocityUnits::rpm);
      intakeRight.spin(vex::directionType::rev,140,vex::velocityUnits::rpm);
    leftDrive.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
    rightDrive.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
    centerDrive.spin(reverse,200,rpm);
      
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
  if(tilterMotor.rotation(degrees)<30&&Controller1.ButtonL1.pressing()){
    tilterMotor.spin(fwd,100,rpm);
  }
}
}
//
// Main will set up the competition functions and callbacks.
//
int main() {
  while(Competition.isEnabled()==false){
    Controller1.Screen.clearLine();
    Controller1.Screen.print("%d", autonomousSelector.value(vex::analogUnits::range12bit));
  }
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
