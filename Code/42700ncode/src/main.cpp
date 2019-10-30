#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
int thresh = 20;//sets the lowest motor power state for the drive function. This will allow you to tune the curve of the P control for the drive function.

//basic autonomous functions. 
void drive(int lt, int rt, int cd, int ds){//initiates function drive with inputs left ticks, right ticks, and d speed
  //tells each motor to rotate for an amount(Not total.) motorName(distance,rotationUnit,speed,speedunits, blocking param
  //{Blocking param tells the robot to stop reading lines of code till this code is done running. for rotateTo and rotateFor its true by default})
  leftDrive.rotateFor(lt,vex::rotationUnits::deg,ds,vex::velocityUnits::pct,false);
  centerDrive.rotateFor(cd,vex::rotationUnits::deg,ds,vex::velocityUnits::pct,false);
  rightDrive.rotateFor(rt,vex::rotationUnits::deg,ds,vex::velocityUnits::pct);
}

void softMotion(int drivePower,int driveDuration){
  driveMotors.spin(fwd,drivePower,rpm);
  wait(driveDuration,msec);
  driveMotors.stop();
  
}
void lift(int lh){ //initiates lift function with input lift height

  //tells both of the lift motors to rotate to a certain rotation value. Notice that rotateTo is to rotate to say 900deg, rotateFor rotates for 
  //900 deg instead.
  liftLeft.rotateTo(lh,vex::rotationUnits::deg,100,vex::velocityUnits::rpm,false);
  liftRight.rotateTo(lh,vex::rotationUnits::deg,100,vex::velocityUnits::rpm);
} 
/*void drive(int leftTargetDistance, int rightTargetDistance, int driveTopSpeed) { //This is the drive constructor.

  while(leftDrive.rotation(vex::rotationUnits::deg)<leftTargetDistance){//This checks for completion of the drive function.

    int leftCurrentDistance = ( leftDrive.rotation(vex::rotationUnits::deg)  ); //These two lines set up a callback for the drive motor rotation values.
    int rightCurrentDistance = ( rightDrive.rotation(vex::rotationUnits::deg)  );
    int leftSpeed = 100*1-(leftCurrentDistance/ leftTargetDistance); //These two lines set up the P control.
    int rightSpeed = 100*1-(rightCurrentDistance/ rightTargetDistance); //These two lines set up the P control.
    
    leftDrive.startRotateTo(leftTargetDistance,vex::rotationUnits::deg,leftSpeed,vex::velocityUnits::rpm); //These two lines set the motor power for the drive function.
    rightDrive.startRotateTo(rightTargetDistance,vex::rotationUnits::deg,rightSpeed,vex::velocityUnits::rpm);
      }//end of while loop
      leftDrive.resetRotation(); //These two lines reset the motor encoders for maximum accuracy.
      rightDrive.resetRotation();
        }*/


void liftTo(int rotationTarget, int liftTopSpeed, int mode) {//This is the lift target constructor.


 /* while(liftLeft.rotation(vex::rotationUnits::deg)<rotationTarget){
    int liftCurrentDistance = ( liftLeft.rotation(vex::rotationUnits::deg) + liftRight.rotation(vex::rotationUnits::deg) )/2;

    int liftCurrentSpeed = ( (thresh*liftTopSpeed) + ((1-thresh)*liftTopSpeed*(1-(liftCurrentDistance/rotationTarget))  ) );

  if(mode==0){

    liftLeft.rotateTo(rotationTarget,vex::rotationUnits::deg,liftCurrentSpeed,vex::velocityUnits::rpm,false);

    liftRight.rotateTo(rotationTarget,vex::rotationUnits::deg,liftCurrentSpeed,vex::velocityUnits::rpm);
    }else if(mode==1){
      liftLeft.startRotateTo(rotationTarget,vex::rotationUnits::deg,liftCurrentSpeed,vex::velocityUnits::rpm);
      liftRight.startRotateTo(rotationTarget,vex::rotationUnits::deg,liftCurrentSpeed,vex::velocityUnits::rpm);
      
      }
        }*/ 
  
//This is an attempted re-write to allow the program to work in both Tele-OP and autonomous, saving lines of code.
    int liftCurrentDistance = ( liftLeft.rotation(vex::rotationUnits::deg) + liftRight.rotation(vex::rotationUnits::deg) )/2;

    int liftCurrentSpeed = liftTopSpeed;//( (thresh*liftTopSpeed) + ((1-thresh)*liftTopSpeed*(1-(liftCurrentDistance/rotationTarget))  ) );
  if(mode == 0){

    while(liftCurrentDistance<rotationTarget){
      
    int liftCurrentDistance = ( liftLeft.rotation(vex::rotationUnits::deg) + liftRight.rotation(vex::rotationUnits::deg) )/2;

    int liftCurrentSpeed = ( (thresh*liftTopSpeed) + ((1-thresh)*liftTopSpeed*(1-(liftCurrentDistance/rotationTarget))  ) );

    liftLeft.rotateTo(rotationTarget,vex::rotationUnits::deg,liftCurrentSpeed,vex::velocityUnits::rpm,false);

    liftRight.rotateTo(rotationTarget,vex::rotationUnits::deg,liftCurrentSpeed,vex::velocityUnits::rpm);

    }


    } else if(mode == 1){
      if(liftLeft.rotation(vex::rotationUnits::deg) < rotationTarget){
        liftLeft.spin(vex::directionType::rev,liftCurrentSpeed,vex::velocityUnits::rpm);
        liftRight.spin(vex::directionType::rev,liftCurrentSpeed,vex::velocityUnits::rpm);
        }else if(liftLeft.rotation(vex::rotationUnits::deg)>rotationTarget){
        liftLeft.spin(vex::directionType::fwd,liftCurrentSpeed,vex::velocityUnits::rpm);
        liftRight.spin(vex::directionType::fwd,liftCurrentSpeed,vex::velocityUnits::rpm);

        }else{
        liftLeft.stop();
        liftRight.stop();
        }
      }else{
        Controller1.Screen.print("You've set the wrong mode for lift func.");
      }
          }
void intake(int intakeMode){//This is the intake constructor.
  if(intakeMode == 0){//This part sets the intake to intake.
    intakeLeft.spin(vex::directionType::fwd,200,vex::velocityUnits::rpm);
    intakeRight.spin(vex::directionType::fwd,200,vex::velocityUnits::rpm);
    }else if(intakeMode == 1){//This part sets the intake to outtake.
    intakeLeft.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);
    intakeRight.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);
      }else{//This part sets the intake to stop running.
      intakeLeft.stop();
      intakeRight.stop();
      }
}

void driveBackAutonomous(){
  
    //sets motor to move in a direction at a set velocity. Doesn't say anything else.
    leftDrive.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
    rightDrive.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
    vex::task::sleep(1000);
    //reverses the spinning after 1 second
    leftDrive.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
    rightDrive.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
    vex::task::sleep(500);
    //stops both motors after 1/2 a second delay of driving fwd.
    leftDrive.stop();
    rightDrive.stop();
    drive(0,300,0,200);
    intakeLeft.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);
    intakeRight.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);
}
void deploy(){
  intakeLeft.spin(reverse,100,percent);
  intakeRight.spin(reverse,100,percent);
  wait(500,msec);
  intakeLeft.stop();
  intakeRight.stop();
}



void redShortAutonomous(){
  Controller1.Screen.print("redShortAutonomous");
  intakeGroup.spin(fwd,200,rpm);
  drive(1300,1300,1300,50);
  drive(-100,-100,-100,200);
  leftDrive.rotateFor(-287,deg,160,rpm);
  drive(-1150,-1150,-1150,70);
  rightDrive.rotateFor(-287,deg,160,rpm);
  drive(1200,1200,1200,47);
  drive(-700,-700,-500,160);
  drive(380,-380,0,160);
  drive(433,433,463,200);
  intakeGroup.spin(reverse,300,rpm);
  wait(200,msec);
  intakeGroup.stop();
  tilterMotor.rotateTo(200,deg,100,rpm);
  intakeGroup.spin(fwd,200,rpm);
  tilterMotor.rotateTo(400,deg,90,rpm);
  tilterMotor.rotateTo(600,deg,60,rpm);
  wait(100,msec);
  intakeGroup.spin(reverse,180,rpm);
  wait(50,msec);
  intakeGroup.spin(reverse,140,rpm);
  driveMotors.spin(reverse,200,rpm);
  wait(500,msec);
  intakeGroup.stop();
  driveMotors.stop();
}
void blueShortAutonomous(){
  Controller1.Screen.print("blueShortAutonomous");
  intakeLeft.spin(fwd,100,pct);
  intakeRight.spin(fwd,100,pct);

}
void redLongAutonomous(){
  Controller1.Screen.print("redLongAutonomous");
  intakeLeft.spin(fwd,100,pct);
  intakeRight.spin(fwd,100,pct);
  
}
void blueLongAutonomous(){
  Controller1.Screen.print("blueLongAutonomous");
  intakeLeft.spin(fwd,100,pct);
  intakeRight.spin(fwd,100,pct);
}


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  leftDrive.resetRotation();
  rightDrive.resetRotation();
  liftLeft.resetRotation();
  liftRight.resetRotation();
  centerDrive.resetRotation();
  intakeLeft.resetRotation();
  intakeRight.resetRotation();
  tilterMotor.resetRotation();
  driveMotors.setTimeout(5,sec);
  liftLeft.setTimeout(2,sec);
  liftRight.setTimeout(2,sec);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  deploy();
  //leftDrive.rotateFor(-2000,degrees,100,vex::velocityUnits::pct);
  redShortAutonomous();
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {//Drive part. Axis1 is the left to right on the left stick. Axis3 is up and down on the left stick. Axis 4 is right and left on the right stick.
    int leftDriveSpeed = ((Controller1.Axis3.value()) + Controller1.Axis1.value());// just some arcade coding. 
    int rightDriveSpeed = (( Controller1.Axis3.value())-Controller1.Axis1.value());
   // int strafingSpeed = ((Controller1.Axis3.value())-Controller1.Axis1.value()+ Controller1.Axis1.value() );
  int strafingSpeed = (leftDriveSpeed / rightDriveSpeed);
  Controller1.Screen.print(autonomousSelector.angle());
//if|then statement you know the drill. This one is checking if ButtonB is being pressed on Controller1.
if(Controller1.ButtonB.pressing()==0){
    leftDrive.spin(vex::directionType::fwd,leftDriveSpeed,vex::velocityUnits::pct);
    rightDrive.spin(vex::directionType::fwd,rightDriveSpeed,vex::velocityUnits::pct);
    centerDrive.spin(vex::directionType::fwd,strafingSpeed,vex::velocityUnits::pct);
   }   //End of drive.
   /* int medliftSpeed = 15+ 100*(1-((liftLeft.rotation(vex::rotationUnits::deg))/320 ));*/
    if(Controller1.ButtonLeft.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)){
      liftLeft.rotateTo(320,degrees,100,rpm,false);
      liftRight.rotateTo(320,degrees,100,rpm);
    }if(Controller1.ButtonUp.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)){
      liftLeft.rotateTo(350,degrees,100,rpm,false);
      liftRight.rotateTo(350,degrees,100,rpm);
    }if(Controller1.ButtonRight.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)){
      liftLeft.rotateTo(600,degrees,100,rpm,false);
      liftRight.rotateTo(600,degrees,100,rpm);
    }if(Controller1.ButtonDown.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)>0){
      liftLeft.rotateTo(0,degrees,100,rpm,false);
      liftRight.rotateTo(0,degrees,100,rpm);
    }

    if(Controller1.ButtonL1.pressing()){
      liftLeft.spin(vex::directionType::fwd,100,vex::velocityUnits::rpm);
      liftRight.spin(vex::directionType::fwd,100,vex::velocityUnits::rpm);
    }else if(Controller1.ButtonL2.pressing()){
      liftLeft.spin(vex::directionType::rev,100,vex::velocityUnits::rpm);
      liftRight.spin(vex::directionType::rev,100,vex::velocityUnits::rpm);
    }else{
      liftLeft.stop(vex::brakeType::hold);
      liftRight.stop(vex::brakeType::hold);
    }
int tilterSpeed = 20+100*(1-(tilterMotor.rotation(vex::rotationUnits::deg)/600));
    if(Controller1.ButtonX.pressing()&&(tilterMotor.rotation(vex::rotationUnits::deg)<600)){
      tilterMotor.spin(vex::directionType::fwd,tilterSpeed,vex::velocityUnits::rpm);
      if(tilterMotor.rotation(vex::rotationUnits::deg)>700){
        intakeLeft.spin(vex::directionType::rev,15,vex::velocityUnits::rpm);
        intakeRight.spin(vex::directionType::rev,15,vex::velocityUnits::rpm);
      }
    }else
    if(Controller1.ButtonY.pressing()&&tilterMotor.rotation(vex::rotationUnits::deg)>0){
      tilterMotor.spin(vex::directionType::rev,100,vex::velocityUnits::rpm);
    }else{
      tilterMotor.stop(vex::brakeType::brake);
    }
    if(Controller1.ButtonR2.pressing()){
      intakeLeft.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);
      intakeRight.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);

    }else 
    if(Controller1.ButtonR1.pressing()){
      intakeLeft.spin(vex::directionType::fwd,200,vex::velocityUnits::rpm);
      intakeRight.spin(vex::directionType::fwd,200,vex::velocityUnits::rpm);
    }else{
      intakeLeft.stop(vex::brakeType::hold);
      intakeRight.stop(vex::brakeType::hold);
    }
    if(Controller1.ButtonB.pressing()){
      intakeLeft.spin(vex::directionType::rev,140,vex::velocityUnits::rpm);
      intakeRight.spin(vex::directionType::rev,140,vex::velocityUnits::rpm);
    leftDrive.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
    rightDrive.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
    centerDrive.spin(reverse,200,rpm);
      
    }else if(Controller1.ButtonA.pressing()){
      intakeGroup.spin(reverse,60,rpm);
      driveMotors.spin(reverse,60,rpm);
    }
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
