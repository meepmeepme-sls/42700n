#include "robot-config.h"
# define M_PIl          3.141592653589793238462643383279502884L /* pi */
int WheelDiameter;
int xdistance;
int zdistance;
//pie * wheel size in mm = x | (sonar in cm-DistanceToObject) / x *360 = degrese to move to stopping from specified value in cm form object| x = 25.93384735538374 |
//x axis movement Forward|Backward
void dx(int xpower, int xdistanceInCM){
  xdistance = xdistanceInCM/(WheelDiameter*M_PIl)*360;
	LF.rotateFor(xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct,false);
	LB.rotateFor(xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct,false);
	RF.rotateFor(-xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct,false);
	RB.rotateFor(-xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct);
}
//z axis movement Left|Right
void dz(int zpower, int zdistanceInCM){
  zdistance = zdistanceInCM/(WheelDiameter*M_PIl)*360;
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
//autoselect
void autoselectdisplay(){
  if (notweed.value(pct) <= 16 && notweed.value(pct) >= 0) {
    Brain.Screen.print("Auto: Red 1 ");
    Controller1.Screen.print("Auto: Red 1                           .");
  }
  else if (notweed.value(pct) >= 17 && notweed.value(pct) <= 33) {
    Brain.Screen.print("Auto: Red 2 ");
    Controller1.Screen.print("Auto: Red 2                           .");
  }
  else if (notweed.value(pct) >= 34 && notweed.value(pct) <= 50) {
    Brain.Screen.print("Auto: Red 3 ");
    Controller1.Screen.print("Auto: Red 3                           .");
  }
  else if (notweed.value(pct) >= 51 && notweed.value(pct) <= 67) {
    Brain.Screen.print("Auto: Blue 1");
    Controller1.Screen.print("Auto: Blue 1                           .");
  }
  else if (notweed.value(pct) >= 68 && notweed.value(pct) <= 84) {
    Brain.Screen.print("Auto: Blue 2");
    Controller1.Screen.print("Auto: Blue 2                           .");
  }
  else if (notweed.value(pct) >= 85 && notweed.value(pct) <= 100) {
    // Brain.Screen.print("Blue3");
    Brain.Screen.print("Auto: Blue 3");
    Controller1.Screen.print("Auto: Blue 3                           .");
  }

}


/*void inout(int inoutpower, int inoutdri){
  LI.spin(inoutdri, -inoutpower, pct);
  RI.spin(inoutdri, inoutpower, pct);
}*/

/*
//x axis movement Forward|Backward
void dx(int xpower, int xdistance){
	LF.rotateFor(xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct,false);
	LB.rotateFor(xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct,false);
	RF.rotateFor(-xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct,false);
	RB.rotateFor(-xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct);
}
*/