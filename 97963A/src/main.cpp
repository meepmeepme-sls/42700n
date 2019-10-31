/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Sarah Xiang                                      */
/*    Created:      Wed Sep 04 2019                                           */
/*    Description:  V5 project                                                */
/*    WELCOME TO MY TRASH CODE!                                               */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
vex::motor Motor1 = vex::motor(vex::PORT1);
vex::motor Motor2 = vex::motor(vex::PORT8);
vex::motor intake1 = vex::motor(vex::PORT3);
vex::motor intake2 = vex::motor(vex::PORT4);
vex::controller controller1 = vex::controllerType::primary;
vex::controller controller2 = vex::controllerType::partner;
vex::motor driveLeft = vex::motor(vex::PORT6);
vex::motor driveRight = vex::motor(vex::PORT7);
vex::motor driveMid = vex::motor(vex::PORT5);
vex::motor tilter = vex::motor(vex::PORT9);
vex::line Line = vex::line(Brain.ThreeWirePort.G);
vex::bumper Bumper = vex::bumper(Brain.ThreeWirePort.E);

// define your global instances of motors and other devices here
float motorLeft = Motor1.rotation(rotationUnits::deg);
float motorRight = - Motor2.rotation(rotationUnits::deg);

float leftWheel = driveLeft.rotation(rotationUnits::deg); //needs modification
float rightWheel = driveRight.rotation(rotationUnits::deg); //needs modification
float leftWheel_last = leftWheel;
float rightWheel_last = rightWheel;
float deltaLeftWheel = leftWheel - leftWheel_last;
float deltaRightWheel = rightWheel - rightWheel_last;
float midWheelPower = (deltaLeftWheel - deltaRightWheel)*controller2.Axis2.value() / (2*deltaRightWheel);

//below are pid terms for the lift
float midPoint = ( motorLeft + motorRight )/2;
float setPoint = motorLeft - midPoint;
float derivative, totalError, P, I, D, liftCorrectionPower, leftPower, rightPower;
float lastError = setPoint;
float error = setPoint;
float Kp = 1.1;
float Ki = 0;
float Kd = 0.3;

//below are pid terms for the tilter
float derivative_t, P_t, D_t;
float setPoint_t;
float error_t = setPoint_t;
float Kp_t = 0.09;
float Kd_t = 0.2;
float power_t = P_t + D_t;
float lastError_t = error_t;

float liftHighPos = 700;
float lift_sixCubes_pos = 1250;
float lift_sevenCubes_pos = 1500;

float derivative_l, P_l, D_l;
float setPoint_l;
float error_l = setPoint_l;
float Kp_l = 0.12;
float Kd_l = 0.08;
float power_l = P_l + D_l;
float lastError_l = error_l;

float tilterPos_high = 730;
float tilterPos_low = 940;
float tilterPos = - tilter.rotation(rotationUnits::deg);
float tilterPos_release_preparation_low = 740;
float tilterPos_release_preparation_high = 650;

float bumper_pressing = 0;  //I do not know how to print a boolean

//macro booleans
bool liftToPosition_sixCubes = false;
bool release_sixCubes = false;
bool liftToPosition_ground = false;
bool release_ground = false;
bool Bumper_ = false;
bool readyToRelease_sixCubes = false;
bool lift_coast = false;

void liftToPosition_sixCubes_setTrue ( void ) {
  liftToPosition_sixCubes = true;
}

void liftToPosition_sixCubes_setFalse ( void ) {
  liftToPosition_sixCubes = false;
}

void release_sixCubes_setTrue ( void ){
  release_sixCubes = true;
}

void release_sixCubes_setFalse ( void ){
  release_sixCubes = false;
  readyToRelease_sixCubes = false;
}

void liftToPosition_ground_setTrue ( void ){
  liftToPosition_ground = true;
}

void liftToPosition_ground_setFalse ( void ){
  liftToPosition_ground = false;
}

void release_ground_setTrue ( void ){
  release_ground = true;
}

void release_ground_setFalse ( void ){
  release_ground = false;
}

int macro_task() {
  while(1) {
    //macro for dr4b raising _ high pos
    controller1.ButtonL1.pressed(liftToPosition_sixCubes_setTrue);
    controller1.ButtonL1.released(liftToPosition_sixCubes_setFalse);
    
    //macro for cube release _ high pos
    controller1.ButtonL2.pressed(release_sixCubes_setTrue);
    controller1.ButtonL2.released(release_sixCubes_setFalse);

    //macro for dr4b raising _ ground
    controller1.ButtonR1.pressed(liftToPosition_ground_setTrue);
    controller1.ButtonR1.released(liftToPosition_ground_setFalse);

    //macro for cube release _ ground
    controller1.ButtonR2.pressed(release_ground_setTrue);
    controller1.ButtonR2.released(release_ground_setFalse);
  }
}



int main() {

  driveMid.setReversed(true);
  driveRight.setReversed(true);
  Motor1.setReversed(true);
  Motor2.setReversed(true);
  tilter.setReversed(true);
    
  Motor1.setMaxTorque(100, percentUnits::pct);
  Motor1.setMaxTorque(100, percentUnits::pct);
  intake1.setMaxTorque(100, percentUnits::pct);
  intake2.setMaxTorque(100, percentUnits::pct);
  driveLeft.setMaxTorque(100, percentUnits::pct);
  driveRight.setMaxTorque(100, percentUnits::pct);
  driveMid.setMaxTorque(100, percentUnits::pct);
  tilter.setMaxTorque(100, percentUnits::pct);
  //run the macro task
  vex::task t(macro_task);
   
  while(1) {
    

    //lift pid calculatoins, for correction
    motorLeft = Motor1.rotation(rotationUnits::deg);
    motorRight = - Motor2.rotation(rotationUnits::deg);
    midPoint = ( motorLeft + motorRight ) / 2;
    error = motorLeft - midPoint;
    derivative = error - lastError;
    totalError = totalError + error;
    P = error * Kp;
    //I = totalError*Ki;
    D = derivative * Kd;
    liftCorrectionPower = P + I + D;





    //first macro, lift raise to high pos and titer rotate to prepare for release

    if(liftToPosition_sixCubes == true){

      //lift pid, for go to set point, currently not needed
      
      /*setPoint_l = lift_sixCubes_pos;
      error_l = setPoint_l - midPoint;
      derivative_l = error_l - lastError_l;
      P_l = error_l * Kp_l;
      D_l = derivative_l * Kd_l;
      power_l = P_l + D_l;
      lastError_l = error_l;
      leftPower = power_l - liftCorrectionPower;
      rightPower = power_l + liftCorrectionPower;*/
      //step 1: lift go to set point, height of 6 cubes

      Motor1.rotateTo(1200, rotationUnits::deg, 90, velocityUnits::pct, false);
      Motor2.rotateTo(-1200, rotationUnits::deg, 90, velocityUnits::pct, false);
      
      //tilter pid, doesn't work
      tilterPos = - tilter.rotation(rotationUnits::deg);
      /*setPoint_t = tilterPos_release_preparation;
      error_t = setPoint_t - tilterPos;
      derivative_t = error_t - lastError_t;
      P_t = error_t * Kp_t;
      D_t = derivative_t * Kd_t;
      power_t = P_t + D_t;
      lastError_t = error_t;*/

      //step 2: tilter go to set point
      tilter.rotateTo(tilterPos_release_preparation_high, rotationUnits::deg, 0.11 * (tilterPos_release_preparation_high - tilterPos), velocityUnits::pct, false);

      //all the previous code are non blocking, the code below enable the driver still has control over the robot while this macro is running
      //DRIVETRAIN CONTROL
        if((controller2.Axis3.value() != 0)||(controller2.Axis1.value() != 0)){
          leftWheel = driveLeft.rotation(rotationUnits::deg); 
          rightWheel = - driveRight.rotation(rotationUnits::deg); 
        
          deltaLeftWheel = leftWheel - leftWheel_last;
          deltaRightWheel = rightWheel - rightWheel_last;

          midWheelPower = (deltaLeftWheel - deltaRightWheel)*(controller2.Axis3.value() + controller2.Axis1.value() * controller2.Axis1.value() * controller2.Axis1.value() / 10000) / (2*deltaLeftWheel);
          
          driveLeft.spin(directionType::fwd, controller2.Axis3.value() + controller2.Axis1.value() * controller2.Axis1.value() * controller2.Axis1.value() / 10000, velocityUnits::pct);
          driveRight.spin(directionType::fwd, controller2.Axis3.value() - controller2.Axis1.value() * controller2.Axis1.value() * controller2.Axis1.value() / 10000, velocityUnits::pct);
          driveMid.spin(directionType::fwd, midWheelPower, velocityUnits::pct);

          leftWheel_last = leftWheel;
          rightWheel_last = rightWheel;
        }
        else{
          if((motorLeft + motorRight)/2 > liftHighPos){
            //when the lift position is high, set the motors to coast to prevent tipping
            driveLeft.stop(brakeType::coast);
            driveRight.stop(brakeType::coast);
            driveMid.stop(brakeType::coast);
          }
          else{
            //when the lift position is low, set the motors to hold to minimize the effect of inertia
            driveLeft.stop(brakeType::brake);
            driveRight.stop(brakeType::brake);
            driveMid.stop(brakeType::brake);
          }
        }
        //DRIVETRAIN CONTROL ENDS
    }




    //macro 2, release cubes (high stack)

    else if(release_sixCubes == true){
      if(Line.value(percentUnits::pct) < 50){
        readyToRelease_sixCubes = true;
      }
      if(readyToRelease_sixCubes == false){
        tilter.rotateTo(tilterPos_high, rotationUnits::deg, 80, velocityUnits::pct);
        Motor1.spin(directionType::rev, 20 + liftCorrectionPower, velocityUnits::pct);
        Motor2.spin(directionType::fwd, 20 - liftCorrectionPower, velocityUnits::pct);
      }
      else{
        Motor1.stop(brakeType::hold);
        Motor2.stop(brakeType::hold);
        vex::task::sleep(300);

        //back up
        
        controller2.rumble("-");
        driveLeft.rotateFor(-500, rotationUnits::deg, 45, velocityUnits::pct, false);
        driveMid.rotateFor(-500, rotationUnits::deg, 45, velocityUnits::pct, false);
        driveRight.rotateFor(-500, rotationUnits::deg, 45, velocityUnits::pct);
        driveLeft.stop(brakeType::coast);
        driveRight.stop(brakeType::coast);
        driveMid.stop(brakeType::coast);

        release_sixCubes = false;
      }
    }




    //macro 3, preparation for ground stack release

    else if(liftToPosition_ground == true){
      //step1: lift raise up a little bit
      Motor1.rotateTo(200, rotationUnits::deg, 60, velocityUnits::pct, false);
      Motor2.rotateTo(-200, rotationUnits::deg, -60, velocityUnits::pct, false);

      //step2: tilter rotate to position
      tilterPos = - tilter.rotation(rotationUnits::deg);
      tilter.rotateTo(740, rotationUnits::deg, 0.1 * (tilterPos_low - tilterPos), velocityUnits::pct, false);

      //DRIVETRAIN CONTROL
        if((controller2.Axis3.value() != 0)||(controller2.Axis1.value() != 0)){
          leftWheel = driveLeft.rotation(rotationUnits::deg); 
          rightWheel = - driveRight.rotation(rotationUnits::deg); 
        
          deltaLeftWheel = leftWheel - leftWheel_last;
          deltaRightWheel = rightWheel - rightWheel_last;

          midWheelPower = (deltaLeftWheel - deltaRightWheel)*(controller2.Axis3.value() + controller2.Axis1.value() * controller2.Axis1.value() * controller2.Axis1.value() / 10000) / (2*deltaLeftWheel);
          
          driveLeft.spin(directionType::fwd, controller2.Axis3.value() + controller2.Axis1.value() * controller2.Axis1.value() * controller2.Axis1.value() / 10000, velocityUnits::pct);
          driveRight.spin(directionType::fwd, controller2.Axis3.value() - controller2.Axis1.value() * controller2.Axis1.value() * controller2.Axis1.value() / 10000, velocityUnits::pct);
          driveMid.spin(directionType::fwd, midWheelPower, velocityUnits::pct);

          leftWheel_last = leftWheel;
          rightWheel_last = rightWheel;
        }
        else{
          if((motorLeft + motorRight)/2 > liftHighPos){
            //when the lift position is high, set the motors to coast to prevent tipping
            driveLeft.stop(brakeType::coast);
            driveRight.stop(brakeType::coast);
            driveMid.stop(brakeType::coast);
          }
          else{
            //when the lift position is low, set the motors to hold to minimize the effect of inertia
            driveLeft.stop(brakeType::brake);
            driveRight.stop(brakeType::brake);
            driveMid.stop(brakeType::brake);
          }
        }
        //DRIVETRAIN CONTROL ENDS
    }





    // macro 4, gorund stack release

    else if(release_ground == true){
      //check bumper
      if(Bumper.pressing()){
        Bumper_ = true;
      }
      else{
        Bumper_ = false;
      }
      
      //lift to lowest position
      if(Bumper_ == false){
        tilter.rotateTo(tilterPos_low, rotationUnits::deg, 80, velocityUnits::pct);
        Motor1.spin(directionType::rev, 45 + liftCorrectionPower, velocityUnits::pct);
        Motor2.spin(directionType::fwd, 45 - liftCorrectionPower, velocityUnits::pct);
        vex::task::sleep(200);
      }
      else{
        
        Motor1.stop(brakeType::hold);
        Motor2.stop(brakeType::hold);
        vex::task::sleep(100);
        //back up

        controller2.rumble("-");
        driveLeft.rotateFor(-500, rotationUnits::deg, 45, velocityUnits::pct, false);
        driveMid.rotateFor(-500, rotationUnits::deg, 45, velocityUnits::pct, false);
        driveRight.rotateFor(-500, rotationUnits::deg, 45, velocityUnits::pct);
        driveLeft.stop(brakeType::coast);
        driveRight.stop(brakeType::coast);
        driveMid.stop(brakeType::coast);

        release_ground = false;
      }
    }





    //normal control code

    else{
        //LIFT CONTROL (CONTROLLER 1&2)
        leftPower = controller1.Axis3.value() - liftCorrectionPower;
        rightPower = controller1.Axis3.value() + liftCorrectionPower;
        
        if( (leftPower > 100) || (rightPower > 100) ){
          if(leftPower > rightPower){
            rightPower = rightPower - (leftPower - 100);
          }
          if(leftPower < rightPower){
            leftPower = leftPower - (rightPower - 100);
          }
        }
        if( (leftPower < -100) || (rightPower < -100) ){
          if(leftPower < rightPower){
            //left needs to catch up with right
            rightPower = rightPower - (leftPower + 100);
          }
          if(leftPower > rightPower){
            //right needs to catch up with left
            leftPower = leftPower - (rightPower + 100);
          }
        }
        
        if(Bumper.pressing()){
          //stop the motors when bumper pressed, prevent axle twisting
          Motor1.stop(brakeType::coast);
          Motor2.stop(brakeType::coast);

          Motor1.resetRotation();
          Motor2.resetRotation();

          bumper_pressing = 1;

          //lift_coast = true;
        }
        else{
          bumper_pressing = 0;
          
          if(controller1.Axis3.value() != 0){
            //lift_coast = false;
            Motor1.spin(directionType::fwd, leftPower, velocityUnits::pct);
            Motor2.spin(directionType::rev, rightPower, velocityUnits::pct);
          }
          /*else if(controller2.ButtonL1.pressing()){
            //lift_coast = false;
            Motor1.spin(directionType::fwd, 90 - liftCorrectionPower, velocityUnits::pct);
            Motor2.spin(directionType::rev, 90 + liftCorrectionPower, velocityUnits::pct);
          }
          else if(controller2.ButtonL2.pressing()){
            //lift_coast = false;
            Motor1.spin(directionType::rev, 90 + liftCorrectionPower, velocityUnits::pct);
            Motor2.spin(directionType::fwd, 90 - liftCorrectionPower, velocityUnits::pct);
          }*/
          else{
            if( fabs(motorLeft - motorRight) > 3){
              Motor1.spin( directionType::fwd, -liftCorrectionPower, velocityUnits::pct );
              Motor2.spin( directionType::rev, liftCorrectionPower, velocityUnits::pct );
            }
            else {
              if(lift_coast == false){
                Motor1.stop(brakeType::hold);
                Motor2.stop(brakeType::hold);
              }
              else{
                Motor1.stop(brakeType::coast);
                Motor2.stop(brakeType::coast);
              }
            }
          }
        }
        lastError = error;
        //LIFT CONTROL ENDS (CONTROLLER 1&2)



        //INTAKE CONTROL
        //R1 and R2 are for normal intake
        if( controller2.ButtonR1.pressing() ){
          intake1.spin(directionType::fwd, 100, velocityUnits::pct);
          intake2.spin(directionType::rev, 100, velocityUnits::pct);
        }
        else if ( controller2.ButtonR2.pressing() ) {
          intake1.spin(directionType::rev, 100, velocityUnits::pct);
          intake2.spin(directionType::fwd, 100, velocityUnits::pct);
        }
        //L1 and L2 are for tower intake
        if( controller2.ButtonL1.pressing() ){
          intake1.spin(directionType::fwd, 30, velocityUnits::pct);
          intake2.spin(directionType::rev, 30, velocityUnits::pct);
        }
        else if ( controller2.ButtonL2.pressing() ) {
          intake1.spin(directionType::rev, 30, velocityUnits::pct);
          intake2.spin(directionType::fwd, 30, velocityUnits::pct);
        }
        else{
          intake1.stop(brakeType::coast);
          intake2.stop(brakeType::coast);
        }
        //INTAKE CONTROL ENDS



        //DRIVETRAIN CONTROL
        if((controller2.Axis3.value() != 0)||(controller2.Axis1.value() != 0)){
          leftWheel = driveLeft.rotation(rotationUnits::deg); 
          rightWheel = - driveRight.rotation(rotationUnits::deg); 
        
          deltaLeftWheel = leftWheel - leftWheel_last;
          deltaRightWheel = rightWheel - rightWheel_last;

          midWheelPower = (deltaLeftWheel - deltaRightWheel)*(controller2.Axis3.value() + controller2.Axis1.value() * controller2.Axis1.value() * controller2.Axis1.value() / 10000) / (2*deltaLeftWheel);
          
          driveLeft.spin(directionType::fwd, controller2.Axis3.value() + controller2.Axis1.value() * controller2.Axis1.value() * controller2.Axis1.value() / 10000, velocityUnits::pct);
          driveRight.spin(directionType::fwd, controller2.Axis3.value() - controller2.Axis1.value() * controller2.Axis1.value() * controller2.Axis1.value() / 10000, velocityUnits::pct);
          driveMid.spin(directionType::fwd, midWheelPower, velocityUnits::pct);

          leftWheel_last = leftWheel;
          rightWheel_last = rightWheel;
        }
        else{
          if((motorLeft + motorRight)/2 > liftHighPos){
            //when the lift position is high, set the motors to coast to prevent tipping
            driveLeft.stop(brakeType::coast);
            driveRight.stop(brakeType::coast);
            driveMid.stop(brakeType::coast);
          }
          else{
            //when the lift position is low, set the motors to hold to minimize the effect of inertia
            driveLeft.stop(brakeType::brake);
            driveRight.stop(brakeType::brake);
            driveMid.stop(brakeType::brake);
          }
        }
        //DRIVETRAIN CONTROL ENDS



        //TILTER CONTROL (CONTROLLER 1)
        tilterPos = -tilter.rotation(rotationUnits::deg);
        if(controller1.Axis2.value() != 0){
          tilter.spin(directionType::fwd, controller1.Axis2.value(), velocityUnits::pct);
        }
        else if(controller1.ButtonX.pressing()){
          tilter.rotateTo(tilterPos_high, rotationUnits::deg, 0.13 * (tilterPos_high - tilterPos), velocityUnits::pct, false);
        }
        else if(controller1.ButtonA.pressing()){
          //low stack, pid needed (or it might not)
          /*setPoint_t = tilterPos_low;
          error_t = setPoint_t - tilterPos;
          derivative_t = error_t - lastError_t;
          P_t = error_t * Kp_t;
          D_t = derivative_t * Kd_t;
          power_t = P_t + D_t;
          lastError_t = error_t;*/

          tilter.rotateTo(tilterPos_low, rotationUnits::deg, 0.13 * (tilterPos_low - tilterPos), velocityUnits::pct, false);
        }
        else if(controller1.ButtonB.pressing()){
          tilter.rotateTo(0, rotationUnits::deg, 100,velocityUnits::pct);
        }
        else if((Line.value(percentUnits::pct) < 60) && controller2.ButtonR1.pressing()){
          tilter.rotateTo(350, rotationUnits::deg, 70, velocityUnits::pct, false);
        }
        else{
          tilter.stop(brakeType::hold);
        }
        //TILTER CONTROL ENDS (CONTOLLER1)
    }



        //SCREEN PRINT INFO
        Brain.Screen.printAt(10,20,"1 position = %1.2f", Motor1.rotation(rotationUnits::deg));
        Brain.Screen.printAt(10,40,"2 position = %1.2f", -Motor2.rotation(rotationUnits::deg));
        Brain.Screen.printAt(10,80,"tilter position = %1.2f", tilter.rotation(rotationUnits::deg));
        Brain.Screen.printAt(10,100,"error = %1.2f", error);
        Brain.Screen.printAt(10, 140, "bumper pressing = %1.2f", bumper_pressing);
        Brain.Screen.printAt(10, 160, "line = %1.2d", Line.value(percentUnits::pct));
        task::sleep(10);   
  }
}
