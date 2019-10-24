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

//This declares the controller as a controller.
vex::controller Controller1;

//this declares the drive motors.
vex::motor leftDrive(vex::PORT1,false);
vex::motor rightDrive(vex::PORT9,true);
vex::motor strafingDrive(vex::PORT5,true);

//This declares the lift motors.
vex::motor liftLeft(vex::PORT11,false);
vex::motor liftRight(vex::PORT20,true);

//This declares the intake motors.
vex::motor intakeLeft(vex::PORT12,false);
vex::motor intakeRight(vex::PORT19,true);

vex::motor Tilter(vex::PORT4,false);
