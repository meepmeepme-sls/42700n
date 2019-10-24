#include "functions.h"

void driveBackAutonomous(){
  
    //sets motor to move in a direction at a set velocity. Doesn't say anything else.
    leftDrive.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
    rightDrive.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
    vex::task::sleep(1000);
    //reverses the spinning after 1 second
    leftDrive.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
    rightDrive.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
    vex::task::sleep(500);
    //stops both motors after 1/2 a second delay of driving fwd.
    leftDrive.stop();
    rightDrive.stop();
    drive(0,300,200);
    intakeLeft.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);
    intakeRight.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);
}