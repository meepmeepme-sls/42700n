#include "vex.h"

    void usercontrol( void ) {
      while(1){
        FrRight.spin(vex::directionType::fwd, Controller1.Axis3.value()-Controller1.Axis4.value()+Controller1.Axis2.value()+Controller2.Axis3.value()-Controller2.Axis4.value()+Controller2.Axis2.value(), vex::velocityUnits::pct);
        BcRight.spin(vex::directionType::fwd, Controller1.Axis3.value()+Controller1.Axis4.value()+Controller1.Axis2.value()+Controller2.Axis3.value()+Controller2.Axis4.value()+Controller2.Axis2.value(), vex::velocityUnits::pct);
        FrLeft.spin(vex::directionType::fwd, Controller1.Axis3.value()+Controller1.Axis4.value()-Controller1.Axis2.value()+Controller2.Axis3.value()+Controller2.Axis4.value()-Controller2.Axis2.value(), vex::velocityUnits::pct);
        BcLeft.spin(vex::directionType::fwd, Controller1.Axis3.value()-Controller1.Axis4.value()-Controller1.Axis2.value()+Controller2.Axis3.value()-Controller2.Axis4.value()-Controller2.Axis2.value(), vex::velocityUnits::pct);   

        vex::task::sleep(20); 
        Controller1.Screen.print("you KAN do it!!");
        Controller2.Screen.print("%f",RoLift.rotation(rotationUnits::deg));
        
       //roller lift
int rampSpeed = 20+100*(1-(RoLift.rotation(vex::rotationUnits::deg)/820));
        if(Controller1.ButtonA.pressing()) {
            RoLift.spin(vex::directionType::rev, rampSpeed, vex::velocityUnits::rpm);
        }
        else if(Controller1.ButtonB.pressing()) { 
            RoLift.spin(vex::directionType::fwd, 100, vex::velocityUnits::rpm);
        }
        else if(Controller2.ButtonA.pressing()) {
            RoLift.spin(vex::directionType::rev, rampSpeed, vex::velocityUnits::rpm);
        }
        else if(Controller2.ButtonB.pressing()) { 
            RoLift.spin(vex::directionType::fwd, 100, vex::velocityUnits::rpm);
        }
        else { 
            RoLift.stop(vex::brakeType::brake);
        }
                                   
        //rollers
        if(Controller1.ButtonR1.pressing()) {
            RoLeft.spin(vex::directionType::fwd, 90, vex::velocityUnits::pct);
            RoRight.spin(vex::directionType::fwd, 90, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonR2.pressing()) { 
            RoLeft.spin(vex::directionType::rev, 90, vex::velocityUnits::pct);
            RoRight.spin(vex::directionType::rev, 90, vex::velocityUnits::pct);
        }
        else if(Controller2.ButtonR1.pressing()) {
            RoLeft.spin(vex::directionType::fwd, 90, vex::velocityUnits::pct);
            RoRight.spin(vex::directionType::fwd, 90, vex::velocityUnits::pct);
        }
        else if(Controller2.ButtonR2.pressing()) { 
            RoLeft.spin(vex::directionType::rev, 90, vex::velocityUnits::pct);
            RoRight.spin(vex::directionType::rev, 90, vex::velocityUnits::pct);
        }
        else { 
            RoLeft.stop(vex::brakeType::brake);
            RoRight.stop(vex::brakeType::brake);
        }
        
        //ramp lift
        if(Controller1.ButtonL1.pressing()) {
            RaLift.spin(vex::directionType::fwd, 40, vex::velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing()) { 
            RaLift.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
        }
        else if(Controller2.ButtonL1.pressing()) {
            RaLift.spin(vex::directionType::fwd, 40, vex::velocityUnits::pct);
        }
        else if(Controller2.ButtonL2.pressing()) { 
            RaLift.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
        }
        else { 
            RaLift.stop(vex::brakeType::brake);
        }
          

        vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
}
}
