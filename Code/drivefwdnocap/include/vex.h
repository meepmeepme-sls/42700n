
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
vex::controller Controller1;

vex::motor leftDrive(vex::PORT15,vex::gearSetting::ratio18_1,true);
vex::motor rightDrive(vex::PORT11,vex::gearSetting::ratio18_1,false);
vex::motor liftLeft(vex::PORT3,vex::gearSetting::ratio36_1,true);
vex::motor liftRight(vex::PORT8,vex::gearSetting::ratio36_1,false);
vex::motor intakeLeft(vex::PORT9,vex::gearSetting::ratio18_1,true);
vex::motor intakeRight(vex::PORT1,vex::gearSetting::ratio18_1,false);
vex::motor strafingDrive(vex::PORT13,vex::gearSetting::ratio18_1,false);
vex::motor tilterMotor(vex::PORT10,vex::gearSetting::ratio36_1,false);