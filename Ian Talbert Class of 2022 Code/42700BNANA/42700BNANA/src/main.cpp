#include "functionsandvariables.h"
using namespace vex;
competition Competition;
void pre_auton(void) {
  leftDrive.resetRotation();
  rightDrive.resetRotation();
    Controller.Screen.newLine();
    Controller.Screen.print(potGAuto.value(pct));
  Brain.Screen.clearScreen();
    Brain.Screen.setFillColor(autoncolor);
  if(potGAuto.value(pct)<25){
    Brain.Screen.drawRectangle(10,10,30,60);
  }else if(potGAuto.value(pct)<50){
    Brain.Screen.drawRectangle(10,10,60,30);
  }else if(potGAuto.value(pct)<75){
    Brain.Screen.drawRectangle(0,272,480,272);
  }else if(potGAuto.value(pct)<100){
    Brain.Screen.drawRectangle(0,272,480,272);
  }
  vexcodeInit();
  frontClaw.set(true);
  imu.calibrate();
  while(imu.isCalibrating()){
    wait(100,msec);
  }
}
void autonomous(void) {
    Controller.Screen.newLine();
    Controller.Screen.print(potGAuto.value(pct));
  if(potGAuto.value(pct)<25){
    //soloawp();
    rush();
    Brain.Screen.setFillColor(color::green);
  }else if(potGAuto.value(pct)<50){
    lawp();
    Brain.Screen.setFillColor(color::red);
  }else if(potGAuto.value(pct)<75){
    rawp();
    Brain.Screen.setFillColor(color::blue);
  }else if(potGAuto.value(pct)<100){
    rrush();
    Brain.Screen.setFillColor(color::yellow);
  }
}

void usercontrol(void) {
  while (1) {
    Controller.Screen.newLine();
    Controller.Screen.print(rightDrive.rotation(deg));
    Controller.ButtonY.pressed(ftoggle);
    Controller.ButtonB.pressed(rtoggle);
    leftDrive.spin(fwd,Controller.Axis3.value()+Controller.Axis1.value(),pct);
    rightDrive.spin(fwd,Controller.Axis3.value()-Controller.Axis1.value(),pct);

    if(Controller.ButtonR1.pressing()&&liftLevel.value(deg)<120){
      liftManualTracker = false;
      lift.spin(fwd,100/*120-liftLevel.value(deg)*/,pct);
    }else if(Controller.ButtonR2.pressing()&&liftLevel.value(deg)>liftpotoffset){
      liftManualTracker = false;
      lift.spin(reverse,liftLevel.value(deg)-liftpotoffset+10,pct);
    }else if(liftManualTracker == false){
      lift.stop(brake);
    }

    if(Controller.ButtonUp.pressing()){// lifts the lift to a preset height for platform scoring.
      liftManualTracker = true;
      
    }
    if(liftLevel.value(deg)<70&&liftManualTracker == true){
        lift.spin(fwd,110-liftLevel.value(deg)+10,pct);
      }else if(liftManualTracker == true&&liftLevel.value(deg)>70){
      lift.stop(hold);
    }


    wait(20, msec);
  }
}
int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}
