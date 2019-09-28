/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "v5.h"
#include "v5_vcs.h"

//defines a controller named "Controller1"
using namespace vex;
vex::brain Brain; 

vex::controller Controller1;

//defines the motor name(port#,gear ratio, reversed setting);
vex::motor leftFrontDrive(vex::PORT1,vex::gearSetting::ratio18_1,false);
vex::motor rightFrontDrive(vex::PORT3,vex::gearSetting::ratio18_1,true);
vex::motor leftBackDrive(vex::PORT2,vex::gearSetting::ratio18_1,false);
vex::motor rightBackDrive(vex::PORT4,vex::gearSetting::ratio18_1,true);
vex::motor liftLeft(vex::PORT5,vex::gearSetting::ratio36_1,true);
vex::motor liftRight(vex::PORT6,vex::gearSetting::ratio36_1,false);
vex::motor intakeLeft(vex::PORT13,vex::gearSetting::ratio18_1,false);
vex::motor intakeRight(vex::PORT11,vex::gearSetting::ratio18_1,true);

vex::pot potentiometerControl(Brain.ThreeWirePort.E);
vex::pot liftPotentiometer(Brain.ThreeWirePort.B);