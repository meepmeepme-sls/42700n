#include "vex.h"
void move( char directionOfMovement[],int rotationDistance,int pow){
  if(strcmp(directionOfMovement, "axisX")){//side to side
    leftFrontDrive.rotateFor(-rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    rightFrontDrive.rotateFor(-rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    leftBackDrive.rotateFor(rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    rightBackDrive.rotateFor(rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
  }if(strcmp(directionOfMovement, "axisZ")){// forward and back
    leftFrontDrive.rotateFor(rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    rightFrontDrive.rotateFor(-rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    leftBackDrive.rotateFor(rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    rightBackDrive.rotateFor(-rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
  }if(strcmp(directionOfMovement, "axisXZ")){//diagonal movement defaulting left
    rightFrontDrive.rotateFor(-rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    leftBackDrive.rotateFor(rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
  }if(strcmp(directionOfMovement, "axisZX")){//diagonal movement defaulting right
    leftFrontDrive.rotateFor(rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    rightBackDrive.rotateFor(-rotationDistance,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
  }
}
void turn(int turnRotation, int pow){
    leftFrontDrive.rotateFor(-turnRotation,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    rightFrontDrive.rotateFor(-turnRotation,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    leftBackDrive.rotateFor(-turnRotation,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    rightBackDrive.rotateFor(-turnRotation,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
}
void softMove(int movementTime, int pow){
    leftFrontDrive.spin(vex::directionType::fwd,pow,vex::velocityUnits::pct);
    rightFrontDrive.spin(vex::directionType::fwd,pow,vex::velocityUnits::pct);
    leftBackDrive.spin(vex::directionType::fwd,pow,vex::velocityUnits::pct);
    rightBackDrive.spin(vex::directionType::fwd,pow,vex::velocityUnits::pct);
    leftFrontDrive.stop();
    rightFrontDrive.stop();
    leftBackDrive.stop();
    rightBackDrive.stop();
    vex::task::sleep(movementTime);
}
