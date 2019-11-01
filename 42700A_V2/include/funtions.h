#include "robot-config.h"
//x axis movement Forward|Backward
void dx(int xpower, int xdistance){
	LF.rotateFor(xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct,false);
	LB.rotateFor(xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct,false);
	RF.rotateFor(-xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct,false);
	RB.rotateFor(-xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct);
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
/*void inout(int inoutpower, int inoutdri){
  LI.spin(inoutdri, -inoutpower, pct);
  RI.spin(inoutdri, inoutpower, pct);
}*/

