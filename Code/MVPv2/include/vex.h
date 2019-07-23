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
vex::controller Controller1 = vex::controller();
vex::motor lf(vex::PORT1,false);
vex::motor lb(vex::PORT2,false);
vex::motor rf(vex::PORT3,true);
vex::motor rb(vex::PORT4,true);
//motor groups. 
//l = lift
vex::motor l(vex::PORT5,false);
//il,ir intake left / intake right
vex::motor il(vex::PORT6,false);
vex::motor ir(vex::PORT7,true);
//mi = main intake reverse as neccesary
vex::motor mi(vex::PORT8,true);

