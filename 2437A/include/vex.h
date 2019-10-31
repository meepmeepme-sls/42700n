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

using namespace vex;
vex::brain Brain;
vex::motor BcRight (vex::PORT1, vex::gearSetting::ratio18_1,true);
vex::motor RoLift (vex::PORT2, vex::gearSetting::ratio36_1,true);
vex::motor RaLift (vex::PORT6, vex::gearSetting::ratio36_1,false);
vex::motor BcLeft (vex::PORT10, vex::gearSetting::ratio18_1,false);
vex::motor FrRight (vex::PORT11, vex::gearSetting::ratio18_1,true);
vex::motor RoRight (vex::PORT16, vex::gearSetting::ratio18_1,true);
vex::motor RoLeft (vex::PORT17, vex::gearSetting::ratio18_1,false);
vex::motor FrLeft (vex::PORT20, vex::gearSetting::ratio18_1,false);
vex::controller Controller1;
vex::controller Controller2( vex::controllerType::partner );
