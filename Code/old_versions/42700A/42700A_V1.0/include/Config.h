#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"
#include "Vision.h"
//dead brain ports | 1; 7; 12; 13;
using namespace vex;
vex::brain Brain;
vex::motor LF (vex::PORT11, vex::gearSetting::ratio18_1,false);
vex::motor LB (vex::PORT14, vex::gearSetting::ratio18_1,false);
vex::motor RF (vex::PORT17, vex::gearSetting::ratio18_1,false);
vex::motor RB (vex::PORT20, vex::gearSetting::ratio18_1,false);
vex::motor AL (vex::PORT3, vex::gearSetting::ratio18_1,false);
vex::motor AR (vex::PORT4, vex::gearSetting::ratio18_1,false);
vex::motor CL (vex::PORT5, vex::gearSetting::ratio18_1,false);
vex::motor CR (vex::PORT2, vex::gearSetting::ratio18_1,false);
vex::sonar Sonar(Brain.ThreeWirePort.E);
vex::pot pot1(Brain.ThreeWirePort.H);
vex::pot pot2(Brain.ThreeWirePort.B);
vex::controller Controller1;