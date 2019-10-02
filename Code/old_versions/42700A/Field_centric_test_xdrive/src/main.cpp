#include "vex.h"
#include "math.h"
using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
vex::motor LF (vex::PORT1, vex::gearSetting::ratio18_1,false);
vex::motor LB (vex::PORT2, vex::gearSetting::ratio18_1,false);
vex::motor RF (vex::PORT3, vex::gearSetting::ratio18_1,false);
vex::motor RB (vex::PORT4, vex::gearSetting::ratio18_1,false);
vex::gyro gyro1(Brain.ThreeWirePort.D);
vex::controller Controller1;

// define your global instances of motors and other devices here
int pi;
int NewNorth;
int x_joy;
int y_joy;
int rotatey_joy;;
int rotatex_joy;
int rotation;
int log_drive(int joy_val)
{
	int new_val = 0;
	if ( joy_val < 0)
	{
		new_val = -1 * joy_val * joy_val / 127;
	}
	else
	{
		new_val = joy_val * joy_val / 127;
	}
	return new_val;
}
int direction_vector;
int direction_angle;
int cosX;
int sinY;
//int cosDegrees;
//int sinDegrees;
int drive_drift;
//int radiansToDegrees;
int driveX;
int driveY;
int motorReq;
int East_drive;
int West_drive;
int North_drive;
int South_drive;
int limitMotor;
int ca1;
int ca3;
int ca4;
int x;
int a;
int math1;
int math2;
int math3;
int math4;
int sinDegrees(int sind){
  math3=sin(sind*pi/180);
  return math3;
}
int cosDegrees(int cosd){
  math2=((pi*cosd)/180);
  return math2;
}
int radiansToDegrees(int radiae){
  math1=pi/180*radiae;
  return math1;
}


int main() {
  while(true){
  /*
    //Holonomic_X_drive driver controle
    gyro1.angle();

    ca4 = (Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value());
    
    x = ca4;

    LF.spin(vex::directionType::fwd, Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
    RF.spin(vex::directionType::fwd, -Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
    RB.spin(vex::directionType::fwd, -Controller1.Axis3.value() - Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
    LB.spin(vex::directionType::fwd, Controller1.Axis3.value() - Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
    gyro1.value(analogUnits::pct);

    LF.spin(vex::directionType::fwd, x, vex::velocityUnits::pct);
  */
    pi=22/7;
    NewNorth = (gyro1.value(analogUnits::pct));
		// New North is where the robot belives north is.

		// use the log drive to ease the driving but still keep the 127 max
		x_joy= log_drive(Controller1.Axis4.value());
		y_joy= log_drive(Controller1.Axis3.value());
		rotatey_joy= log_drive(Controller1.Axis2.value());
		rotatex_joy= log_drive(Controller1.Axis1.value());

		//The 8UP button resets the gyro so the
		//current heading is considered forward.
		//This is helpful because we can reset North if we change our position.
		if (Controller1.ButtonA.pressing() == 1) {
			gyro1.startCalibration();
			NewNorth = 0;
		}

		direction_vector= sqrt((x_joy*x_joy)+(y_joy*y_joy));
	  if(y_joy!=0 && y_joy>0){
      direction_angle = radiansToDegrees(atan((float)x_joy/(float)y_joy))*10;
	  }
		else if(y_joy !=0 && y_joy< 0){
			direction_angle = (10*radiansToDegrees(atan((float)(x_joy*-1)/(float)(y_joy*-1))+1800));
			//writeDebugStreamLine("special x_joy: %d y_joy %d  dir ang %f", x_joy, y_joy, direction_angle);
		}
		else{
			if(x_joy==0)direction_angle = 0;
			if(x_joy<0)direction_angle = 1800;
		}
		//writeDebugStreamLine("x_joy: %d y_joy %d ", x_joy, y_joy);
		//writeDebugStreamLine("direction_angle: %f ", direction_angle);
		//writeDebugStreamLine("direction_vector: %d ", direction_vector);
    a=NewNorth/10;
		cosX = cosDegrees(a);
		sinY = sinDegrees(a);
		//writeDebugStreamLine("gyro: %f ", NewNorth/10);
		//writeDebugStreamLine("cos gyro: %f \n", cosX);
		//writeDebugStreamLine("sin gyro: %f \n", sinY);


		drive_drift = (direction_angle - NewNorth)/10;  // divie by 10 since the angles are in gyro *10 range

		cosX = cosDegrees(drive_drift);
		sinY = sinDegrees(drive_drift);
		driveX = direction_vector * cosX;
		driveY = direction_vector * sinY;

		rotation = rotatex_joy;

    //set speed
		LF.spin(fwd, driveX + rotation, pct);
    RF.spin(fwd, driveX*-1 + rotation, pct);
    LB.spin(fwd, driveY*-1 + rotation, pct);
    RB.spin(fwd, driveY + rotation, pct);
		//motorReq[East_drive] = limitMotor((driveX) + rotation);
    //motorReq[West_drive] = limitMotor((driveX*-1) + rotation);
		//motorReq[North_drive] = limitMotor((driveY*-1) + rotation);
		//motorReq[South_drive] = limitMotor((driveY) + rotation);
    
    }
  }