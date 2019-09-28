#include "functions.h "
using namespace vex;
vex::competition Competition;
//start of user generated code.

void pre_auton( void ) {//Clears all motor encoders upon start of user program.
  leftDrive.resetRotation();
  rightDrive.resetRotation();
  liftLeft.resetRotation();
  liftRight.resetRotation();
  strafingDrive.resetRotation();
  intakeLeft.resetRotation();
  intakeRight.resetRotation();
  tilterMotor.resetRotation();
}
//this stuff runs in the first 15 seconds of the competition. 
void autonomous( void ) {
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
    drive(0,300,200);
    intakeLeft.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);
    intakeRight.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);
}
//this runs for the rest of the match (1:45)
void usercontrol( void ) {
  
    int shifter = 0;
  while (1) {
    //Drive part. Axis1 is the left to right on the left stick. Axis3 is up and down on the left stick. Axis 4 is right and left on the right stick.
    int leftDriveSpeed = ((Controller1.Axis3.value()) + -1*Controller1.Axis1.value());// just some arcade coding. 
    int rightDriveSpeed = (( Controller1.Axis3.value() )+Controller1.Axis1.value());
    int strafingSpeed = (1*Controller1.Axis4.value());

//if|then statement you know the drill. This one is checking if ButtonB is being pressed on Controller1.
if(Controller1.ButtonB.pressing()==0){
    leftDrive.spin(vex::directionType::fwd,leftDriveSpeed,vex::velocityUnits::pct);
    rightDrive.spin(vex::directionType::fwd,rightDriveSpeed,vex::velocityUnits::pct);
    strafingDrive.spin(vex::directionType::fwd,strafingSpeed,vex::velocityUnits::pct);
   }   //End of drive.
    int medliftSpeed = 15+ 100*(1-((liftLeft.rotation(vex::rotationUnits::deg))/320 ));
    int highliftSpeed = 15+ 100*(1-((liftLeft.rotation(vex::rotationUnits::deg))/350 ));
    int topliftSpeed = 15+ 100*(1-((liftLeft.rotation(vex::rotationUnits::deg))/660 ));
    int downliftSpeed = 15+ 100*(((liftLeft.rotation(vex::rotationUnits::deg))/2 ));

    if(Controller1.ButtonLeft.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)<320){
      liftLeft.spin(vex::directionType::fwd,medliftSpeed,vex::velocityUnits::rpm);
      liftRight.spin(vex::directionType::fwd,medliftSpeed,vex::velocityUnits::rpm);
    }if(Controller1.ButtonUp.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)<350){
      liftLeft.spin(vex::directionType::fwd,highliftSpeed,vex::velocityUnits::rpm);
      liftRight.spin(vex::directionType::fwd,highliftSpeed,vex::velocityUnits::rpm);
    }if(Controller1.ButtonRight.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)<660){
      liftLeft.spin(vex::directionType::fwd,topliftSpeed,vex::velocityUnits::rpm);
      liftRight.spin(vex::directionType::fwd,topliftSpeed,vex::velocityUnits::rpm);
    }if(Controller1.ButtonDown.pressing()&&liftLeft.rotation(vex::rotationUnits::deg)>0){
      liftLeft.spin(vex::directionType::rev,downliftSpeed,vex::velocityUnits::rpm);
      liftRight.spin(vex::directionType::rev,downliftSpeed,vex::velocityUnits::rpm);
    }
    int autoval = autonomousSelector.value(vex::percentUnits::pct);
    Controller1.Screen.print(autoval);

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
int tilterSpeed = 20+100*(1-(tilterMotor.rotation(vex::rotationUnits::deg)/720));
    if(Controller1.ButtonX.pressing()){
      tilterMotor.spin(vex::directionType::fwd,tilterSpeed,vex::velocityUnits::rpm);
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
    if(Controller1.ButtonB.pressing()&&tilterMotor.rotation(vex::rotationUnits::deg)<400){
      intakeLeft.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);
      intakeRight.spin(vex::directionType::rev,200,vex::velocityUnits::rpm);
    leftDrive.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
    rightDrive.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
      
    }
    if(Controller1.ButtonA.pressing()){
      shifter = 1;
    }else{
      shifter = 0;
    }
  }
}int main() {//this is vital. dont touch this shit.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    pre_auton();
    while(1) {
      vex::task::sleep(100);
    }    
       
}