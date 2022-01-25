#include "vex.h"

/*
This section includes variables for use in autonomous, driver control
*/


/*
This section includes functions for use in autonomous, driver control
*/
bool driveHoldOp = false;

void driveHold(){
  driveHoldOp =!driveHoldOp;
}


bool liftManualTracker = false; //default false = manual control.

int liftpotoffset = 15;

void ftoggle(){
frontClaw.set(!frontClaw.value());
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

void gyroTurn(int gturntarget, double mult){
  imu.setHeading(180, deg);
  int gturnoptarget = gturntarget-imu.heading(deg);
  while(imu.heading()!=gturntarget){
    leftDrive.spin(fwd,1.2*mult*(gturntarget-imu.heading(deg)),volt);
    rightDrive.spin(fwd,-1.2*mult*(gturntarget-imu.heading(deg)),volt);
    Controller.Screen.newLine();
    Controller.Screen.print(imu.heading(deg));
  }
  leftDrive.stop(hold);
  rightDrive.stop(hold);
}

void senseGo(int distimeout, int speed){
  rearClaw.set(false);
  int i=0;
  while(rearLimit.value()&&-leftDrive.rotation(deg)<distimeout){
    leftDrive.spin(reverse,speed,pct);
    rightDrive.spin(reverse,speed,pct);
  }
  rearClaw.set(true);
  wait(5,msec);
}

void biasdrive(int lrot,int rrot, int lpow, int rpow){// true = wait to complete for left, 
leftDrive.rotateFor(lrot,deg,lpow,velocityUnits::pct,false);
rightDrive.rotateFor(rrot,deg,rpow,velocityUnits::pct,false);
while(leftDrive.isSpinning()||rightDrive.isSpinning()){
  wait(1,msec);
}


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
  gyroTurn(90, .1);
  simpleDrive(100, 100, 30);
  gyroTurn(90, .1);
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

void leftsideSHAcounter(){//grab middle neutral then continue into high middle goal to disrupt autonomous.
  senseGo(5000,100);
  biasdrive(-100,20,-5000,100);
  simpleDrive(-1000,-1000,100);
  simpleDrive(2000,2000,100);
  simpleDrive(0,1000,100);
  ftoggle();
  
}

void rush(){
  senseGo(5000,100);
  simpleDrive(-leftDrive.rotation(deg),-rightDrive.rotation(deg),100);
  leftDrive.stop(hold);
  rightDrive.stop(hold);

}