#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"
#include "vision.h"

using namespace vex;
vex::brain Brain;
vex::motor LF (vex::PORT1, vex::gearSetting::ratio18_1,false);
vex::motor LB (vex::PORT2, vex::gearSetting::ratio18_1,false);
vex::motor RF (vex::PORT3, vex::gearSetting::ratio18_1,false);
vex::motor RB (vex::PORT4, vex::gearSetting::ratio18_1,false);
vex::motor AL (vex::PORT5, vex::gearSetting::ratio18_1,false);
vex::motor AR (vex::PORT6, vex::gearSetting::ratio18_1,false);
vex::motor CL (vex::PORT7, vex::gearSetting::ratio18_1,false);
vex::motor CR (vex::PORT8, vex::gearSetting::ratio18_1,false);
vex::sonar Sonar( Brain.ThreeWirePort.G);
vex::line line1( Brain.ThreeWirePort.F );
vex::pot pot1(Brain.ThreeWirePort.A);
vex::controller Controller1;