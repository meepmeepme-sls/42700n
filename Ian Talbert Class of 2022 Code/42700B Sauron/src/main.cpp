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
  sauron.set(false);
  rearClaw.set(false);
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
    Controller.ButtonX.pressed(ftoggle);
    Controller.ButtonB.pressed(rtoggle);

    Controller.ButtonY.pressed(cloggle);
    leftDrive.spin(fwd,Controller.Axis3.value()+.7*Controller.Axis1.value(),pct);
    rightDrive.spin(fwd,Controller.Axis3.value()-.7*Controller.Axis1.value(),pct);

    if(Controller.ButtonR1.pressing()&&liftLevel.value(range12bit)>1900){
      liftManualTracker = false;
      lift.spin(fwd,100*liftLevel.value(range12bit)-2000,pct);
    }else if(Controller.ButtonR2.pressing()&&liftLevel.value(range12bit)<2950){
      liftManualTracker = false;
      lift.spin(reverse,(100*(3000-liftLevel.value(range12bit))),pct);
    }else if(liftManualTracker == false){
      lift.stop(hold);
    } if(liftManualTracker == true){
      lift.spin(fwd,100*(liftLevel.value(range12bit)-2600),rpm);
      if(liftLevel.value(range12bit)<2600&&liftLevel.value(range12bit)>2500){
        liftManualTracker = false;
      }
    }

    if(Controller.ButtonUp.pressing()){// lifts the lift to a preset height for platform scoring.
      liftManualTracker = true;
    }
/*
    if(clawop&&clawLevel.value(range12bit)>1000&&clawTracker==false){
      if(clawLevel.value(range12bit)<1000){
        claw.stop();
        clawTracker=true;
      }
      claw.spin(fwd,100,pct);
    }else if(!clawop&&clawLevel.value(range12bit)<3300&&clawTracker==false){
      if(clawLevel.value(range12bit)>3300){
        claw.stop();
        clawTracker=true;
      }
      claw.spin(reverse,100,pct);
    }else if(clawTracker==true){
      claw.stop();
    }else{
      claw.stop(coast);
    }*/

    if(!clawop&&clawTracker==false){
      claw.startRotateTo(0,deg,100,rpm);
      clawTracker=true;
    }else if(clawop&&clawTracker==false){
      claw.startRotateTo(210,deg,100,rpm);
      clawTracker=true;

    }else if(!claw.isSpinning()){
claw.stop(brake);
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
