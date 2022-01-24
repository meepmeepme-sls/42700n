#include "vex.h"

/*
This section includes variables for use in autonomous, driver control
*/


/*
This section includes functions for use in autonomous, driver control
*/
bool liftManualTracker = false; //default false = manual control.

bool clawTracker = false;

int liftpotoffset = 15;

bool clawop = false;

void cloggle(){
  clawop = !clawop;
  clawTracker=false;
}

void ftoggle(){
sauron.set(!sauron.value());
}
void rtoggle(){
rearClaw.set(!rearClaw.value());
}
/*
void simpleDrive(int leftdistance, int rightdistance, int speed){
  while(leftDrive.rotation(deg)!=leftdistance && rightDrive.rotation(deg)!=rightdistance){
  leftDrive.rotateTo(leftdistance,deg,speed,velocityUnits::pct,false);
  rightDrive.rotateTo(rightdistance,deg,speed,velocityUnits::pct,false);
    wait(20,msec);
  }
  
}*/

void pDrive(int ld, int rd, int pow){
  leftDrive.resetRotation();
  rightDrive.resetRotation();
  double lerror = ld-leftDrive.rotation(deg);
  double rerror = rd-rightDrive.rotation(deg);
  while(!(fabs(lerror)<=0)&&!(fabs(rerror)<=0)){
    leftDrive.spin(fwd,(lerror*pow)+10,pct);
    rightDrive.spin(fwd,(rerror*pow)+10,pct);\
    wait(10,msec);
  }
}

void simpleDrive(int ld, int rd, int pow){
  leftDrive.rotateFor(ld, deg, pow,velocityUnits::pct,false);
  rightDrive.rotateFor(rd, deg, pow,velocityUnits::pct,true);
}

void gyroTurn(int gturntarget){
  gturntarget = gturntarget/2;
    imu.resetHeading();
    imu.resetRotation();
    Controller.Screen.newLine();
    Controller.Screen.print(gturntarget);
  while(gturntarget-imu.rotation()>=0){
    leftDrive.spin(fwd,(gturntarget-imu.rotation(deg))*10,pct);
    rightDrive.spin(reverse,(gturntarget-imu.rotation(deg))*10,pct);
    wait(20,msec);
    Controller.Screen.newLine();
    Controller.Screen.print(gturntarget-imu.rotation(deg));
  }
}

void senseGo(int timeout, int speed){
  rearClaw.set(false);
  int i=0;
  while(rearLimit.value()&&leftDrive.rotation(deg)>-(timeout)){
    leftDrive.spin(reverse,speed,pct);
    rightDrive.spin(reverse,speed,pct);
    wait(1,msec);
    i++;
  }
  rearClaw.set(true);
  leftDrive.spin(reverse,100,pct);
  rightDrive.spin(reverse,100,pct);
  wait(40,msec);
}

void liftTo(int lrotation){
  /*int lspeed;
  while(liftLevel.value(deg)-liftpotoffset!=lrotation){
    lspeed = 1.1*((lrotation)-(liftLevel.value(deg)-liftpotoffset));
    lift.spin(fwd,lspeed,pct);
  }*/
  lift.rotateTo(lrotation,deg,100,rpm);
}

void soloawp(){
  rtoggle();
  //liftTo(200);
  simpleDrive(400,400,70);
  simpleDrive(800,-800,50);
  simpleDrive(1400,1400,70);
  simpleDrive(750,-750,50);
  simpleDrive(4000,4000,70);
  liftTo(90);
  simpleDrive(2000,2000,70);
  ftoggle();
  wait(1,sec);
  liftTo(100);
  simpleDrive(-1000,-1000,50);
  liftTo(-1);
  simpleDrive(1200,1200,50);
  ftoggle();
  simpleDrive(-1000,-1000,70);
  /*
  liftTo(90);
  ftoggle();
  simpleDrive(-300,-300,70);
  gyroTurn(-90);
  simpleDrive(500, 500, 70);
  gyroTurn(90);
  simpleDrive(2000,2000,100);
  gyroTurn(180);
  simpleDrive(-200,-200,50);
  rtoggle();
  simpleDrive(500,500,100);*/
}

void lawp(){
  rtoggle();
  simpleDrive(400,400,50);
  simpleDrive(-750,750,50);
  senseGo(150,100);
}

void rawp(){
  simpleDrive(200,200,70);
  liftTo(90);
  ftoggle();
  wait(1,sec);
  liftTo(100);
  simpleDrive(-200, -200, 50);
  liftTo(0);
  simpleDrive(300, 300, 50);
  ftoggle();
  simpleDrive(-500,-500,70);
}

void rrush(){
  senseGo(200,100);
  simpleDrive(1600,1600,100);
  simpleDrive(1000,-1000,100);
  //simpleDrive(400,-400,100);
  rtoggle();
  simpleDrive(1000,1000,60);
  simpleDrive(4000,-4000,100);
  senseGo(200,100);
  simpleDrive(2000,2000,100);
  
  
}
void rush(){
  senseGo(8000,100);
  //simpleDrive(3500,5000,100);
  simpleDrive(-(leftDrive.rotation(deg)),-(rightDrive.rotation(deg)),100);
  leftDrive.stop(hold);
  rightDrive.stop(hold);
  lift.rotateTo(-490,deg,100,rpm);
}