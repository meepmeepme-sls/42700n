#include "robot-config.h"

vex::competition    Competition;
float inchperdegree=.0359;
int AutoPotVal;
int AutoMode;
char y[16][10]={"Mode0 \n",
               "Mode1 \n",
               "Mode2 \n",
               "Mode3 \n",
               "Mode4 \n",
               "Mode5 \n",
               "Mode6 \n",
               "Mode7 \n",
               "Mode8 \n",
               "Mode9 \n",
               "Mode10\n",
              };

//Auto Functions
void pivotHeading(int heading)
{
    int currentHeading;
    int headingErr,headingErrI;
    currentHeading=GyroH.value(vex::rotationUnits::deg);
    headingErr=currentHeading-heading;
    headingErrI-headingErr;
    Controller1.Screen.clearScreen();    
    
    if (abs(headingErr)<10)
    {
    while(abs(headingErr) > 1)
    {
        if(abs(headingErr) <= 5)        
        {
        headingErr=(headingErr/abs(headingErr))*4;//rdw
        }
        headingErr=(headingErr*8)/10;
        Controller1.Screen.setCursor(1,1);
        Controller1.Screen.clearLine(); 
        Controller1.Screen.print("1 err=%d curr=%d",headingErr,currentHeading);        
        FRdrive.spin(vex::directionType::fwd,headingErr,vex::velocityUnits::pct);
        FLdrive.spin(vex::directionType::fwd,-headingErr,vex::velocityUnits::pct);
        BRdrive.spin(vex::directionType::fwd,headingErr,vex::velocityUnits::pct);
        BLdrive.spin(vex::directionType::fwd,-headingErr,vex::velocityUnits::pct);   
        currentHeading=GyroH.value(vex::rotationUnits::deg);
        headingErr=currentHeading-heading;
    }
    FRdrive.stop();
    FLdrive.stop();
    BRdrive.stop();
    BLdrive.stop();  
    }
    else
    {
    while(abs(headingErr) > 1)
    {
        if(abs(headingErr) < 5)
        {
        headingErr=(headingErr/abs(headingErr)*15);//rdw
        }
        headingErr=(headingErr*8)/10;
        Controller1.Screen.setCursor(1,1);
        Controller1.Screen.clearLine(); 
        Controller1.Screen.print("2 err=%d curr=%d",headingErr,currentHeading);        
        FRdrive.spin(vex::directionType::fwd,headingErr,vex::velocityUnits::pct);
        FLdrive.spin(vex::directionType::fwd,-headingErr,vex::velocityUnits::pct);
        BRdrive.spin(vex::directionType::fwd,headingErr,vex::velocityUnits::pct);
        BLdrive.spin(vex::directionType::fwd,-headingErr,vex::velocityUnits::pct);     
        currentHeading=GyroH.value(vex::rotationUnits::deg);
        headingErr=currentHeading-heading;
        }
        FRdrive.stop();
        FLdrive.stop();
        BRdrive.stop();
        BLdrive.stop();
        currentHeading=GyroH.value(vex::rotationUnits::deg);
        headingErr=currentHeading-heading;
        
    while(abs(headingErr) > 1)
    {
    while(abs(headingErr) > 1)
    {
        if(abs(headingErr) <5)
        {
        headingErr=(headingErr/abs(headingErr))*5;//rdw
        }
        Controller1.Screen.setCursor(1,1);
        Controller1.Screen.clearLine(); 
        Controller1.Screen.print("3 err=%d curr=%d",headingErr,currentHeading);        
        FRdrive.spin(vex::directionType::fwd,headingErr,vex::velocityUnits::pct);
        FLdrive.spin(vex::directionType::fwd,-headingErr,vex::velocityUnits::pct);
        BRdrive.spin(vex::directionType::fwd,headingErr,vex::velocityUnits::pct);
        BLdrive.spin(vex::directionType::fwd,-headingErr,vex::velocityUnits::pct);   
        currentHeading=GyroH.value(vex::rotationUnits::deg);
        headingErr=currentHeading-heading;
        }
    }
    }
    FRdrive.stop();
    FLdrive.stop();
    BRdrive.stop();
    BLdrive.stop();
}

void Drive(int distance, int speed)
{
    int distancedegrees;
    distancedegrees=distance/inchperdegree;
    FRdrive.startRotateFor(distancedegrees,vex::rotationUnits::deg,speed,vex::velocityUnits::rpm);
    FLdrive.startRotateFor(distancedegrees,vex::rotationUnits::deg,speed,vex::velocityUnits::rpm);
    BRdrive.startRotateFor(distancedegrees,vex::rotationUnits::deg,speed,vex::velocityUnits::rpm);
    BLdrive.startRotateFor(distancedegrees,vex::rotationUnits::deg,speed,vex::velocityUnits::rpm); 
}

void LiftArm (int Rotation, int Speed)
{
    Lift.startRotateTo(Rotation,vex::rotationUnits::deg,Speed,vex::velocityUnits::rpm);   
}

void Intake (int Speed)
{
    LeftIntake.spin(vex::directionType::fwd,Speed,vex::velocityUnits::rpm);
    RightIntake.spin(vex::directionType::fwd,Speed,vex::velocityUnits::rpm);
}

void IntakeStop (void)
{
    LeftIntake.stop();  
    RightIntake.stop();
}

void IntakeAngleUp (int Rotation, int Speed)
{
    IntakeAngle.rotateTo(Rotation,vex::rotationUnits::deg,Speed,vex::velocityUnits::rpm);
}


void WaitForDrive(int timeout)
{
    Brain.resetTimer();
    while(
        ((FRdrive.isSpinning() ||  
        FLdrive.isSpinning() ||
        BRdrive.isSpinning() ||  
        BLdrive.isSpinning()) &&
        (Brain.timer(vex::timeUnits::msec)<timeout)
    )
    )
    {}
 }

//AUTO CODE 
void auto0(void)
{
    
}

void auto1(void)
{
  Intake(200);
  Drive(110,75);
  WaitForDrive(3000);
  Intake(100);
  Drive(-120,-75);
  WaitForDrive(500);
  pivotHeading(135);
  Drive(25,100);
  WaitForDrive(3000);
  Intake(0);
  IntakeAngleUp(-900,-50);
  vex::task::sleep(500);  
  Intake(-50);
  vex::task::sleep(200);
  Drive(-20,-50);
}

void auto2(void)
{
  Intake(200);
  Drive(110,75);
  WaitForDrive(3000);
  Intake(100);
  Drive(-120,-75);
  WaitForDrive(500);
  pivotHeading(-135);
  Drive(25,100);
  WaitForDrive(3000);
  Intake(0);
  IntakeAngleUp(-900,-50);
  vex::task::sleep(500);  
  Intake(-50);
  vex::task::sleep(200);
  Drive(-20,-50);
}

void auto3(void)
{
Intake(200);
Drive(18, 30);
WaitForDrive(2000);
pivotHeading(-88);
Drive(16, 40);
WaitForDrive(3000);
IntakeStop();
pivotHeading(-130);
Drive(15, 30);
WaitForDrive(2000);
IntakeAngleUp(-1000, -60);
vex::task::sleep(1000);
Intake(0);
Intake(-40);
Drive(-20, -50);
    
}

void auto4(void)
{
    
}

void auto5(void)
{
    
}

void auto6(void)
{
    
}

void auto7(void)
{
    
}

void auto8(void)
{
    
}

void auto9(void)
{
    
}

void auto10(void)
{
    
}

void pre_auton( void ) 
{
    GyroH.startCalibration(135);
    while(GyroH.isCalibrating()) 
    {}
    Controller1.Screen.clearScreen(); 
 
}

void autonomous( void )
{
    switch(AutoMode)
{
    case 0: auto0();
            break;
        
    case 1: auto1();
            break;
   
    case 2: auto2();
            break;  
            
    case 3: auto3();
            break;
  
    case 4: auto4();
            break;     
            
    case 5: auto5();
            break;  
            
    case 6: auto6();
            break; 
        
    case 7 :auto7();
            break;  
            
    case 8 :auto8();
            break; 
            
    case 9 :auto9();
            break;  
            
    case 10 :auto10();
            break; 
            
    default:
            break;
}
}

void usercontrol( void ) 
{
    
    //Display that the program has started to the screen.
    Brain.Screen.print("359A Competition Started");
    Brain.Screen.print("    Ready For Liftoff");
    Brain.Screen.printAt(2,40,"Destination: Deep Space");
    
    //Varables
    int LeftJoystick;
    int RightJoystick;
    int LiftSpeed=100;
    int IntakeSpeed=100;
    int IntakeAngleSpeed=50;

    FRdrive.setMaxTorque(100,vex::percentUnits::pct);
    FLdrive.setMaxTorque(100,vex::percentUnits::pct);
    BRdrive.setMaxTorque(100,vex::percentUnits::pct);
    BLdrive.setMaxTorque(100,vex::percentUnits::pct);
    Lift.setStopping(vex::brakeType::brake);
    FRdrive.setStopping(vex::brakeType::brake);
    FLdrive.setStopping(vex::brakeType::brake); 
    BRdrive.setStopping(vex::brakeType::brake);
    BLdrive.setStopping(vex::brakeType::brake); 
    IntakeAngle.setStopping(vex::brakeType::brake); 

    while(1) {
        
        //Drive Control
        FLdrive.spin(vex::directionType::fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
        FRdrive.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);
        BLdrive.spin(vex::directionType::fwd, Controller1.Axis3.value(), vex::velocityUnits::pct);
        BRdrive.spin(vex::directionType::fwd, Controller1.Axis2.value(), vex::velocityUnits::pct);

        if(Controller1.ButtonB.pressing())
        {
        IntakeAngleUp(-350,100);
        LiftArm(400,100);
        }

        else if(Controller1.ButtonA.pressing())
        {
        LiftArm(0,100);
        vex::task::sleep(500);  
        IntakeAngleUp(0,100);
        }

        if(Controller1.ButtonDown.pressing())
        {
        IntakeAngleUp(-250,100);
        LiftArm(400,100);
        }

        else if(Controller1.ButtonLeft.pressing())
        {
        LiftArm(0,100);
        vex::task::sleep(500);  
        IntakeAngleUp(0,100);
        }

        //Lift Control
        if(Controller1.ButtonY.pressing())
        {
        Lift.spin(vex::directionType::fwd,LiftSpeed,vex::velocityUnits::pct);
        }
		else if(Controller1.ButtonRight.pressing())
        {
        Lift.spin(vex::directionType::fwd,-LiftSpeed,vex::velocityUnits::pct);
        }
        else 
        {

        //Intake Angle Control
        if(Controller1.ButtonL2.pressing())
        {
         IntakeAngle.spin(vex::directionType::fwd,100,vex::velocityUnits::pct); 
        }
		else if(Controller1.ButtonL1.pressing())
        {
         IntakeAngle.spin(vex::directionType::fwd,-IntakeAngleSpeed,vex::velocityUnits::pct); 
        }
        else 
        {
         IntakeAngle.stop(); 
        }
        
        //Intake Control
        if(Controller1.ButtonR1.pressing())
        {
         RightIntake.spin(vex::directionType::fwd,IntakeSpeed,vex::velocityUnits::pct); 
         LeftIntake.spin(vex::directionType::fwd,IntakeSpeed,vex::velocityUnits::pct);   
        }
		else if(Controller1.ButtonR2.pressing())
        {
         RightIntake.spin(vex::directionType::fwd,-IntakeSpeed,vex::velocityUnits::pct); 
         LeftIntake.spin(vex::directionType::fwd,-IntakeSpeed,vex::velocityUnits::pct); 
        }
        else 
        {
         RightIntake.stop(); 
         LeftIntake.stop(); 
        }

        vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources.
    }

}  
}
int main() {
  
    pre_auton();
        Brain.Screen.setFont(vex::fontType::mono60);    
    while(Competition.isEnabled()==false)
    {
        AutoPotVal=AutoPot.value(vex::analogUnits::range8bit);
        AutoMode=(AutoPotVal+1)/16;
        Controller1.Screen.setCursor(1,1);
        Controller1.Screen.print("%s %4d",y[AutoMode],AutoPotVal);
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print("%s %4d",y[AutoMode],AutoPotVal);
      
    }
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
                      
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}
