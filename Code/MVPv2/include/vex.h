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
vex::controller Controller1 = vex::controller();

//this declares the drive motors.
vex::motor leftFrontDrive(vex::PORT1,false);
vex::motor leftBackDrive(vex::PORT2,false);
vex::motor rightFrontDrive(vex::PORT9,true);
vex::motor rightBackDrive(vex::PORT10,true);

//This declares the lift motors.
vex::motor liftLeft(vex::PORT11,false);
vex::motor liftRight(vex::PORT20);



/*
//il,ir intake left / intake right


vex::motor il(vex::PORT6,false);
vex::motor ir(vex::PORT7,true);
//mi = main intake reverse as neccesary
vex::motor mi(vex::PORT8,true);

*/