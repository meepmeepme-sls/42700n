#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"
//
vex::brain Brain;
vex::controller Controller1 = vex::controller();
vex::controller Controller2 = vex::controller();
vex::motor FRdrive = vex::motor(vex::PORT20,vex::gearSetting::ratio18_1,true);
vex::motor BRdrive = vex::motor(vex::PORT10,vex::gearSetting::ratio18_1,true);
vex::motor FLdrive = vex::motor(vex::PORT1,vex::gearSetting::ratio18_1,false);
vex::motor BLdrive = vex::motor(vex::PORT9,vex::gearSetting::ratio18_1,false);
vex::motor LeftIntake = vex::motor(vex::PORT6,vex::gearSetting::ratio18_1,false);
vex::motor RightIntake = vex::motor(vex::PORT7,vex::gearSetting::ratio18_1,true);
vex::motor Lift = vex::motor(vex::PORT8,vex::gearSetting::ratio36_1,true);
vex::motor IntakeAngle = vex::motor(vex::PORT3,vex::gearSetting::ratio36_1,true);
vex::encoder RightEncoder = vex::encoder(Brain.ThreeWirePort.A);
vex::encoder LeftEncoder = vex::encoder(Brain.ThreeWirePort.B);
vex::gyro GyroH = vex::gyro(Brain.ThreeWirePort.E);
vex::pot AutoPot = vex::pot(Brain.ThreeWirePort.D);