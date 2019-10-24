#include "robot-config.h"
//funtiond and varible setup for auto and dirver controle (primalrly auto tho)
//varibles (auto) | corrisopnds with thair respetible loops
int loop;
//other varibles
int CLpos;
int cl;
int udistance;
int ds;
int l1;
int t1;
int v1;
int currds;
int Speed;
int MaxSpeed;
int debug;
int temp;
//move forwd with ultrasonic
  void uf(int upower){
    LF.rotateFor(udistance, vex::rotationUnits::deg,upower, vex::velocityUnits::pct,false);
    LB.rotateFor(udistance, vex::rotationUnits::deg,upower, vex::velocityUnits::pct,false);
    RF.rotateFor(-udistance, vex::rotationUnits::deg,upower, vex::velocityUnits::pct,false);
    RB.rotateFor(-udistance, vex::rotationUnits::deg,upower, vex::velocityUnits::pct);
  }
//sleep (shortened version of vex::task::sleep(x);) | napt = nap time LOL
  void sleep(int napt){
    vex::task::sleep(napt);
  }
//x axis movement Forward|Backward
  void dx(int xpower, int xdistance){
    LF.rotateFor(xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct,false);
    LB.rotateFor(xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct,false);
    RF.rotateFor(-xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct,false);
    RB.rotateFor(-xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct);
  }
//pid x axis movment
  void pdx(int Top_speed, int xdistance){
    //put pid code here
  }
//z axis movement Left|Right
  void dz(int zpower, int zdistance){
      LF.rotateFor(-zdistance, vex::rotationUnits::deg,zpower, vex::velocityUnits::pct,false);
      LB.rotateFor(zdistance, vex::rotationUnits::deg,zpower, vex::velocityUnits::pct,false);
      RF.rotateFor(-zdistance, vex::rotationUnits::deg,zpower, vex::velocityUnits::pct,false);
      RB.rotateFor(zdistance, vex::rotationUnits::deg,zpower, vex::velocityUnits::pct);
  }
//rotate on y axis movement RotateLeft|RotateRight | use gyro for rotate
  void dy(int ypower, int ydistance){
    LF.rotateFor(ydistance, vex::rotationUnits::deg,ypower, vex::velocityUnits::pct,false);
    LB.rotateFor(ydistance, vex::rotationUnits::deg,ypower, vex::velocityUnits::pct,false);
    RF.rotateFor(ydistance, vex::rotationUnits::deg,ypower, vex::velocityUnits::pct,false);
    RB.rotateFor(ydistance, vex::rotationUnits::deg,ypower, vex::velocityUnits::pct);
  }
//arm movement
  void arm(int apower, int adistance){
    AR.rotateTo(adistance, vex::rotationUnits::deg, apower, vex::velocityUnits::pct,false);
    AL.rotateTo(adistance, vex::rotationUnits::deg, apower, vex::velocityUnits::pct,false);
  }
//intake
  void intake(int inpower){
    CL.spin(vex::directionType::rev, inpower, vex::velocityUnits::pct);
    CR.spin(vex::directionType::fwd, inpower, vex::velocityUnits::pct);
  }
//vision auto aliment
  void autoc( int dts, int aspeed){
	//sets speed
    LF.setVelocity(aspeed,vex::velocityUnits::pct);
    RF.setVelocity(aspeed,vex::velocityUnits::pct);
    LB.setVelocity(aspeed,vex::velocityUnits::pct);
    RB.setVelocity(aspeed,vex::velocityUnits::pct);	
	//sees if thair is a maching colloed object infront of the bot
    //left check
    if(Vision.largestObject.centerX < 105  && Sonar.distance(vex::distanceUnits::cm)>dts) {
    //strafe left
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
      Brain.Screen.setCursor(2,1);
      Brain.Screen.print("Left                       .");
      LB.spin(vex::directionType::rev);
      LF.spin(vex::directionType::fwd);
      RB.spin(vex::directionType::rev);
      RF.spin(vex::directionType::fwd);
      sleep(40);
    }
    else if (Vision.largestObject.centerX > 210 && Sonar.distance(vex::distanceUnits::cm)>dts) {
      //for debuging
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
      Brain.Screen.setCursor(2,1);
      Brain.Screen.print("right                       .");
      //strafe right
      LB.spin(vex::directionType::fwd);
      LF.spin(vex::directionType::rev);
      RB.spin(vex::directionType::fwd);
      RF.spin(vex::directionType::rev);
      sleep(40);
    }
    else if (Vision.largestObject.centerX < 210 && Vision.largestObject.centerX > 105 && Sonar.distance(vex::distanceUnits::cm)>dts) {
      //for debuging
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
      Brain.Screen.setCursor(2,1);
      Brain.Screen.print("forwd                       .");
      //go forwd
      LB.spin(vex::directionType::fwd);
      LF.spin(vex::directionType::fwd);
      RB.spin(vex::directionType::rev);
      RF.spin(vex::directionType::rev);
      sleep(40);
    }
    else if(Vision.objectCount == 1 && Sonar.distance(vex::distanceUnits::cm)<dts){
      LF.stop();
      RF.stop();
      LB.stop();
      RB.stop();
      loop = 0;
      Brain.Screen.setCursor(2,1);
    Controller1.Screen.print ("aliment compleated");
    }
  }
void Move_Fwd(int pwr){
  LF.setVelocity(pwr,vex::velocityUnits::pct);
  RF.setVelocity(-1*pwr,vex::velocityUnits::pct);
  LB.setVelocity(pwr,vex::velocityUnits::pct);
  RB.setVelocity(-1*pwr,vex::velocityUnits::pct);
}
void Move_Right(int pwr){
  LF.setVelocity(pwr,vex::velocityUnits::pct);
  RF.setVelocity(pwr,vex::velocityUnits::pct);
  LB.setVelocity(-1*pwr,vex::velocityUnits::pct);
  RB.setVelocity(-1*pwr,vex::velocityUnits::pct);
}
void Move_Left(int pwr){
  LF.setVelocity(-1*pwr,vex::velocityUnits::pct);
  RF.setVelocity(-1*pwr,vex::velocityUnits::pct);
  LB.setVelocity(pwr,vex::velocityUnits::pct);
  RB.setVelocity(pwr,vex::velocityUnits::pct);
}
void Drive_stop( void ) {
  LF.stop();
  RF.stop();
  LB.stop();
  RB.stop();
}