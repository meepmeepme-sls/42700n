
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

vex::motor leftDrive(vex::PORT1,vex::gearSetting::ratio18_1,false);
vex::motor rightDrive(vex::PORT5,vex::gearSetting::ratio18_1,false);
vex::motor liftLeft(vex::PORT11,vex::gearSetting::ratio36_1,true);
vex::motor liftRight(vex::PORT20,vex::gearSetting::ratio36_1,false);
vex::motor intakeLeft(vex::PORT12,vex::gearSetting::ratio18_1,false);
vex::motor intakeRight(vex::PORT19,vex::gearSetting::ratio18_1,true);
vex::motor strafingDrive(vex::PORT2,vex::gearSetting::ratio18_1,false);
vex::motor tilterMotor(vex::PORT13,vex::gearSetting::ratio36_1,false);