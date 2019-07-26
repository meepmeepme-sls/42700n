//This begins VEX Competition Template constructors.
#include "vex.h"
using namespace vex;
vex::brain       Brain;
vex::competition Competition;
  //This is the end of VEX Competition Template Constructors.

//This is the beginning of autonomous function callback constructors.

//this function is for going straight

    int thresh = 20;
void drive(int dist,int fast) {

  while(lf.rotation(vex::rotationUnits::deg)<dist){

    int currentdist = ( lf.rotation(vex::rotationUnits::deg) + lb.rotation(vex::rotationUnits::deg) + rf.rotation(vex::rotationUnits::deg) + rb.rotation(vex::rotationUnits::deg)  )/4;
    int topspeed = (fast * ( 1- ( currentdist / (dist -thresh) ) ) );

    lf.startRotateTo(dist,vex::rotationUnits::deg,topspeed,vex::velocityUnits::rpm);
    lb.startRotateTo(dist,vex::rotationUnits::deg,topspeed,vex::velocityUnits::rpm);
    rf.startRotateTo(dist,vex::rotationUnits::deg,topspeed,vex::velocityUnits::rpm);
    rb.startRotateTo(dist,vex::rotationUnits::deg,topspeed,vex::velocityUnits::rpm);
      }//end of while loop
      lf.resetRotation();
      lb.resetRotation();
      rf.resetRotation();
      rb.resetRotation();
        }

void turn(int ldist, int rdist, int tspeed){
  int lrot = (lf.rotation(vex::rotationUnits::deg)+lb.rotation(vex::rotationUnits::deg)/2);
  int rrot = (rf.rotation(vex::rotationUnits::deg)+rb.rotation(vex::rotationUnits::deg)/2);


  int lspeed = (tspeed * (1- (rrot) / (ldist-thresh) ) );
  int rspeed = (tspeed * (1- (rrot) / (ldist-thresh) ) );
  
  while(ldist<lf.rotation(vex::rotationUnits::deg)&&rdist<rf.rotation(vex::rotationUnits::deg)){
    lf.startRotateTo(ldist,vex::rotationUnits::deg,lspeed,vex::velocityUnits::rpm);
    lb.startRotateTo(ldist,vex::rotationUnits::deg,lspeed,vex::velocityUnits::rpm);
    rf.startRotateTo(rdist,vex::rotationUnits::deg,rspeed,vex::velocityUnits::rpm);
    rb.startRotateTo(rdist,vex::rotationUnits::deg,rspeed,vex::velocityUnits::rpm);

    }//end of while loop
      lf.resetRotation();
      lb.resetRotation();
      rf.resetRotation();
      rb.resetRotation();
      }

void lto(int rot, int pow, int f) {
  if(f==0){
    liftLeft.rotateTo(rot,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    liftRight.rotateTo(rot,vex::rotationUnits::deg,pow,vex::velocityUnits::pct);
    }else if(f==1){
      liftLeft.rotateTo(rot,vex::rotationUnits::deg,pow,vex::velocityUnits::pct,false);
      liftRight.rotateTo(rot,vex::rotationUnits::deg,pow,vex::velocityUnits::pct,false);

      }
}
void intakeout(){
  mi.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
}
void intakein(){
  mi.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
}
void gin(){
    ir.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
    il.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
}
void gout(){
    ir.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
    il.spin(vex::directionType::rev,100,vex::velocityUnits::pct);

}

  //This is the end of autonomous function callback constructors.

void pre_auton( void ) {
  
}

void autonomous( void ) {
  lto(900,100,0);
  drive(900,200);
}

//This is the beginning of the teleop part of the code. It's broken into three parts: Drive, Lift, and Intakes (ground and main).

void usercontrol( void ) {
  while (1) {
  
  //This is the beginning of the drive constructor.
  int dz = 15;
  
  //These are ternary operators. I'm using them so that the controller is less sensitive. If the value of the joystick does not exceed a certain value it will set the value to zero.
  int JSA3 = Controller1.Axis3.value();
  JSA3 = abs(JSA3) > dz ? JSA3 : 0;
  int JSA2 = Controller1.Axis2.value();
  JSA2 = abs(JSA2) > dz ? JSA2 : 0;

      //connects the joysticks with the drive
      lf.spin(vex::directionType::fwd, JSA3, vex::velocityUnits::pct);
      rf.spin(vex::directionType::fwd, JSA2, vex::velocityUnits::pct);
      lb.spin(vex::directionType::fwd, JSA3, vex::velocityUnits::pct);
      rb.spin(vex::directionType::fwd, JSA2, vex::velocityUnits::pct);

  //This is the end of the drive constructor.

  //This is the beginning of the lift constructor.

  //connects the lift to the shoulder buttons.
  if(Controller1.ButtonL1.pressing()){
    liftLeft.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
    liftRight.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
    } else if(Controller1.ButtonL2.pressing()){
    liftLeft.startRotateTo(0,vex::rotationUnits::deg,100,vex::velocityUnits::pct);  
    liftRight.startRotateTo(0,vex::rotationUnits::deg,100,vex::velocityUnits::pct);  
      } else if((liftLeft.rotation(vex::rotationUnits::deg)<5)&&(liftRight.rotation(vex::rotationUnits::deg)<5)){
        liftLeft.stop(vex::brakeType::coast);
        liftLeft.stop(vex::brakeType::coast);
          }else{
          liftLeft.stop(vex::brakeType::hold);
          liftRight.stop(vex::brakeType::hold);
            }

  //This is the end of the lift constructor.

  //This is the beginning of the ground intake constructor.

  //connects the ground intake to the top right shoulder button and the letter buttons.
  if(Controller1.ButtonR1.pressing()){
    gin();
    }else if(Controller1.ButtonB.pressing()){
      gout();
      }else{
        ir.stop();
        il.stop();
        }
        
  //This is the end of the ground intake constructor.
 
  //This is the start of the main intake constructor.

/*
  if(Controller1.ButtonR2.pressing()){
    intakein();
    l.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
    }else if(Controller1.ButtonA.pressing()){
      intakeout();
      }
*/

  //This is the beginning of targeted button presets. Feel free to set these aside to focus on the MVP
  //line sensor to line up cube with tower intake. 

  if(Controller1.ButtonUp.pressing()){
    lto(400,100,1);
    }else if(Controller1.ButtonDown.pressing()){

    }

  /*


  */

    vex::task::sleep(20);
  }
}

//This is the end of the teleop part of the code.

//This is the beginning of the main constructor for the VEX Competition Template.
int main() {
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    pre_auton();                        
    while(1) {
    }    
}

//This is the end of the main constructor for the VEX Competition Template.