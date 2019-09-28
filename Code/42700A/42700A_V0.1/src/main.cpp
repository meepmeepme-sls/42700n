#include "funtion.h"
#include "todo.h"
vex::competition    Competition;
//preauto----------------------------------------------------------------------------------------------------------------------------
void pre_auton( void ) {
  //resets all varibles befor comp
  loop = 0;
  cl = 0;
  t1 = false;
  CLpos = CL.value();
  
  //auto select using the potentiomiter
  while(true){
    Brain.Screen.setCursor(5, 0);
    if(pot1.value(pct) >= 16 && pot1.value(pct) <=0){
      Brain.Screen.print("Red 1");
      Controller1.Screen.print("Red 1");
    }
    else if (pot1.value(pct) >= 17 && pot1.value(pct) <=33) {
      Brain.Screen.print("Red 2");
      Controller1.Screen.print("Red 2");
    }
    else if(pot1.value(pct) >= 34 && pot1.value(pct) <=50){
      Brain.Screen.print("Red 3");
      Controller1.Screen.print("Red 3");
    }
    else if(pot1.value(pct) >= 51 && pot1.value(pct) <=67){
      Brain.Screen.print("Blue 1");
      Controller1.Screen.print("Blue 1");
    }
    else if(pot1.value(pct) >= 68 && pot1.value(pct) <=84){
      Brain.Screen.print("auto skills test");
      Controller1.Screen.print("auto skills test");
    }
    else if(pot1.value(pct) >= 85 && pot1.value(pct) <=100){
      //Brain.Screen.print("Blue3");
      Brain.Screen.print("Blue 3");
      Controller1.Screen.print("Blue 3");
    }
  }
}
/*-----------------------------------------------------------------------------------------------------------------------------------    
Autonomous---------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------*/
void autonomous( void ) {
  //warnings
  Brain.Screen.setCursor(6, 0);
  Brain.Screen.print("auto are not done yet");
  //red_top-----------------------------------------------------
  if(pot1.value(pct) >= 16 && pot1.value(pct) <=0){    
    //1
    Controller1.Screen.print("red top running");
    Controller1.Screen.print("red top done");
  }
  //red_mid---------------------------------------
  else if(pot1.value(pct) >= 17 && pot1.value(pct) <=33){
    //2
    Controller1.Screen.print("red_mid running");
    Controller1.Screen.print("red_mid done");
  }
  //red_mid2--------------------------------------
  else if(pot1.value(pct) >= 34 && pot1.value(pct) <=50){
    //3
    Controller1.Screen.print("red_mid2 running");
    intake(200);
    dx(50, 650);
    sleep(50);
    dx(100, -600);
    intake(0);
    dy(50, 450);
    sleep(10);
    dz(50, 200);
    sleep(10);
    dx(50, 200);
    intake(-200);
    sleep(1000);
    dx(50,-200);
    intake(0);
    Controller1.Screen.print("red_mid2 done");
  }
  //Blue-----------------------------------------------------------------
  //blue top--------------------------------------
  else if(pot1.value(pct) >= 51 && pot1.value(pct) <=67){
    //4
    Controller1.Screen.print("Blue top running");
    Controller1.Screen.print("Blue top stop");
  }
  //blue 2----------------------------------------
  else if(pot1.value(pct) >= 68 && pot1.value(pct) <=84){
    //5
    Controller1.Screen.print("Blue 2 running");
    Controller1.Screen.print("Blue 2 stop");
  }
  //blue 3----------------------------------------
  else if(pot1.value(pct) >= 85 && pot1.value(pct) <=100){
    //6
    Controller1.Screen.print("Blue 3 running");
    intake(200);
    dx(50, 650);
    sleep(50);
    dx(100, -600);
    intake(0);
    dy(50, -450);
    sleep(10);
    dz(50, 200);
    sleep(10);
    dx(50, 200);
    intake(-200);
    sleep(1000);
    dx(50,-200);
    intake(0);
    Controller1.Screen.print("Blue 3 stop");
  }
}
/*-----------------------------------------------------------------------------------------------------------------------------------    
User controle------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------*/  
void usercontrol ( void ) {
  //clears screans befor driver use
  //Controller1.Screen.clearScreen();
  Brain.Screen.clearScreen();
  //optinal menu
  debug = true;
  temp = true; 
  while (true) {
    //top 2 rows debug
    //debug_______________________________________________________________________________________
    if (debug==true){
      //brain debuging output | comment out what isent needed
      Brain.Screen.setCursor(1,1);
      //Brain.Screen.print(" %f CM ",Sonar.distance(vex::distanceUnits::cm));
      //Brain.Screen.print("%d", line1.value( analogUnits::range12bit ));
      //Brain.Screen.print("%d", Vision.largestObject.width);
      //Brain.Screen.print("%t", AR.rotation(deg));
      

      //controler debuging output | comment out what isent needed
      //Controller1.Screen.print (" %f CM ",Sonar.distance(vex::distanceUnits::cm));
      //Controller1.Screen.print ("%f", AR.rotation(vex::rotationUnits::deg));
      //Controller1.Screen.print ("%d", line1.value( analogUnits::pct ));
      //Controller1.Screen.print("%d", Vision.largestObject.width);
      //Controller1.Screen.print(".                             .");
    }
    //motor temp feed back_________________________________________________________________________
    if (temp==true){
      if(LF.temperature(pct)>70){
        Brain.Screen.setCursor(4, 1);
        Brain.Screen.print("LF temp");
      }
      if(LF.temperature(pct)>50&&LF.temperature(pct)<70){
        Brain.Screen.setCursor(4, 1);
        Brain.Screen.print("LF warm");
      }
      if(LB.temperature(pct)>70){
        Brain.Screen.setCursor(4, 10);
        Brain.Screen.print("LB temp");
      }
      if(LB.temperature(pct)>50&&LF.temperature(pct)<70){
        Brain.Screen.setCursor(4, 10);
        Brain.Screen.print("LB warm");
      }
      if(RF.temperature(pct)>70){
        Brain.Screen.setCursor(4, 20);
        Brain.Screen.print("RF temp");
      }
      if(RF.temperature(pct)>50&&RF.temperature(pct)<70){
        Brain.Screen.setCursor(4, 20);
        Brain.Screen.print("RF warm");
      }
      if(RB.temperature(pct)>70){
        Brain.Screen.setCursor(4, 30);
        Brain.Screen.print("RB temp");
      }
      if(RB.temperature(pct)>50&&RB.temperature(pct)<70){
        Brain.Screen.setCursor(4, 300);
        Brain.Screen.print("RB warm");
      }
      if(AR.temperature(pct)>70){
        Brain.Screen.setCursor(3, 1);
        Brain.Screen.print("AR temp");
      }
      if(AR.temperature(pct)>50&&AR.temperature(pct)<70){
        Brain.Screen.setCursor(3, 1);
        Brain.Screen.print("AR warm");
      }
      if(AL.temperature(pct)>70){
        Brain.Screen.setCursor(3, 10);
        Brain.Screen.print("AL temp");
      }
      if(AL.temperature(pct)>50&&AL.temperature(pct)<70){
        Brain.Screen.setCursor(3, 10);
        Brain.Screen.print("AL warm");
      }
      if(CL.temperature(pct)>70){
        Brain.Screen.setCursor(3, 20);
        Brain.Screen.print("CL temp");
      }
      if(CL.temperature(pct)>50&&CL.temperature(pct)<70){
        Brain.Screen.setCursor(3, 200);
        Brain.Screen.print("CL warm");
      }
      //put display outputs and note lines
    }
    //Drive________________________________________________________________________________________

    //Holonomic_X_drive driver controle
    /*
    LF.spin(vex::directionType::fwd, Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
    RF.spin(vex::directionType::fwd, -Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
    RB.spin(vex::directionType::fwd, -Controller1.Axis3.value() - Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
    LB.spin(vex::directionType::fwd, Controller1.Axis3.value() - Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
    */
    //othe_controle_surfaes________________________________________________________________________
    //vexDeviceMotorVelocityPidSet(V5_DeviceT device, V5_DeviceMotorPid *pid);

    //Dubble reverce 4 bar
    if(Controller1.ButtonR1.pressing()) {
      AR.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      AL.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonR2.pressing()) {
      AR.spin(vex::directionType::rev, 95, vex::velocityUnits::pct);
      AL.spin(vex::directionType::fwd, 95, vex::velocityUnits::pct);
    }
        //preset hights
    else if(Controller1.ButtonA.pressing()){
      //auto hight code
      AR.rotateTo(473, deg,100,velocityUnits::pct,false);
      AL.rotateTo(-473, deg,100,velocityUnits::pct,false);
    }
    else if (Controller1.ButtonB.pressing()) {
      //autohight code
      AR.rotateTo(900, deg,100,velocityUnits::pct,false);
      AL.rotateTo(-900, deg,100,velocityUnits::pct,false);
    }
    else if (Controller1.ButtonX.pressing()) {
      //autohight code
      AR.rotateTo(200, deg,100,velocityUnits::pct,false);
      AL.rotateTo(-200, deg,100,velocityUnits::pct,false);
    }
    else {
      AR.stop(vex::brakeType::brake);
      AL.stop(vex::brakeType::brake);
    }
    
    //claw
    if(Controller1.ButtonL1.pressing()) {
      CL.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      CR.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonL2.pressing()) {
      CL.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      CR.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    else {
      CL.stop(vex::brakeType::brake);
      CR.stop(vex::brakeType::brake);
    }

    //autoaline orang
    if(Controller1.ButtonUp.pressing()){
      Controller1.Screen.print ("Oragng");
      Vision.takeSnapshot(SIG_1);
      if(Vision.objectCount > 0) {
        LF.setVelocity(50,vex::velocityUnits::pct);
        RF.setVelocity(50,vex::velocityUnits::pct);
        LB.setVelocity(50,vex::velocityUnits::pct);
        RB.setVelocity(50,vex::velocityUnits::pct);
        //bot movment code
        if(Vision.largestObject.centerX < 105  && Sonar.distance(vex::distanceUnits::cm)>10 ) {
          //strafe left
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("Left                       .");
          Controller1.Screen.print("Left");
          LB.spin(vex::directionType::rev);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::rev);
          RF.spin(vex::directionType::fwd);
          Vision.takeSnapshot(SIG_1);
        }
        else if (Vision.largestObject.centerX > 210 && Sonar.distance(vex::distanceUnits::cm)>10 ) {
          //for debuging
          Brain.Screen.setCursor(1,1);
          Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("right                       .");
          //strafe right
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::rev);
          RB.spin(vex::directionType::fwd);
          RF.spin(vex::directionType::rev);
        }
        else if (Vision.largestObject.centerX < 210 && Vision.largestObject.centerX > 105 && Sonar.distance(vex::distanceUnits::cm)>10 ) {
          //for debuging
          Brain.Screen.setCursor(1,1);
          Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("forwd                       .");
          //go forwd
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::rev);
          RF.spin(vex::directionType::rev);
        }
        else if(Sonar.distance(vex::distanceUnits::cm)<10){
          LF.stop();
          RF.stop();
          LB.stop();
          RB.stop();
          Controller1.Screen.print ("Aliment done");
        }
      }
    }
    //auto aline purple
    else if(Controller1.ButtonRight.pressing()){
      Controller1.Screen.print ("Purple");
      Vision.takeSnapshot(SIG_2);
      if(Vision.objectCount > 0) {
        LF.setVelocity(50,vex::velocityUnits::pct);
        RF.setVelocity(50,vex::velocityUnits::pct);
        LB.setVelocity(50,vex::velocityUnits::pct);
        RB.setVelocity(50,vex::velocityUnits::pct);
        //bot movment code
        if(Vision.largestObject.centerX < 105  && Sonar.distance(vex::distanceUnits::cm)>10 ) {
          //strafe left
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("Left                       .");
          LB.spin(vex::directionType::rev);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::rev);
          RF.spin(vex::directionType::fwd);
          Vision.takeSnapshot(SIG_2);
        }
        else if (Vision.largestObject.centerX > 210 && Sonar.distance(vex::distanceUnits::cm)>10 ) {
          //for debuging
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("right                       .");
          //strafe right
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::rev);
          RB.spin(vex::directionType::fwd);
          RF.spin(vex::directionType::rev);
        }
        else if (Vision.largestObject.centerX < 210 && Vision.largestObject.centerX > 105 && Sonar.distance(vex::distanceUnits::cm)>10 ) {
          //for debuging
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("forwd                       .");
          //go forwd
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::rev);
          RF.spin(vex::directionType::rev);
        }
        else if(Vision.objectCount == 1 && Sonar.distance(vex::distanceUnits::cm)<10 ){
          LF.stop();
          RF.stop();
          LB.stop();
          RB.stop();
          Controller1.Screen.print ("Aliment done");
        }
      }
    }
    //autoline purple
    else if (Controller1.ButtonLeft.pressing()) {
      Vision.takeSnapshot(SIG_3);
      Controller1.Screen.print ("Green");
      if(Vision.objectCount > 0) {
        LF.setVelocity(50,vex::velocityUnits::pct);
        RF.setVelocity(50,vex::velocityUnits::pct);
        LB.setVelocity(50,vex::velocityUnits::pct);
        RB.setVelocity(50,vex::velocityUnits::pct);
        //bot movment code
        if(Vision.largestObject.centerX < 105  && Sonar.distance(vex::distanceUnits::cm)>10 ) {
          //strafe left
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("Left                       .");
          LB.spin(vex::directionType::rev);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::rev);
          RF.spin(vex::directionType::fwd);
          Vision.takeSnapshot(SIG_3);
        } 
        else if (Vision.largestObject.centerX > 210 && Sonar.distance(vex::distanceUnits::cm)>10 ) {
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("right                       .");
          //strafe right
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::rev);
          RB.spin(vex::directionType::fwd);
          RF.spin(vex::directionType::rev);
        }
        else if (Vision.largestObject.centerX < 210 && Vision.largestObject.centerX > 105 && Sonar.distance(vex::distanceUnits::cm)>10 ) {
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("forwd                       .");
          //go forwd
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::rev);
          RF.spin(vex::directionType::rev);
        }
        else if(Vision.objectCount == 1 && Sonar.distance(vex::distanceUnits::cm)<10){
          LF.stop();
          RF.stop();
          LB.stop();
          RB.stop();
          Controller1.Screen.print ("Aliment done");
        }
      }
    }
    else {
      LF.spin(vex::directionType::fwd, Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
      RF.spin(vex::directionType::fwd, -Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
      RB.spin(vex::directionType::fwd, -Controller1.Axis3.value() - Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
      LB.spin(vex::directionType::fwd, Controller1.Axis3.value() - Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
    }
    //sleep(10);
  }
}
/*
  __________    _________       ______       _____      _____         __     __     _________     __________     ___________     ___________       ______
 |____   ___|  |   ______|     /   _  \     |     \    /     |       |  |   |  |   |_______  |   |_______   |   /   _____   \   /   _____   \     /   _  \
     |  |      |  |______     /   / \  \    |  |\  \  /  /|  |       |  |   |  |          |  |          /  /    |  |     |  |   |  |     |  |    /   / \  \
     |  |      |   ______|   /   /___\  \   |  | \  \/  / |  |       |  |___|  |    ______|  |         /  /     |  |     |  |   |  |     |  |   /   /___\  \
     |  |      |  |          |   ____   |   |  |  \    /  |  |       |______   |   |  _______|        /  /      |  |     |  |   |  |     |  |   |   ____   |
     |  |      |  |______    |  |    |  |   |  |   \  /   |  |              |  |   |  |______        /  /       |  |_____|  |   |  |     |  |   |  |    |  |
     |__|      |_________|   |__|    |__|   |__|    \/    |__|              |__|   |_________|      /__/        \___________/   \___________/   |__|    |__|
*/
//evrything under this point dont worry about it|its nessasary for the compition
int main() {
  pre_auton();    
  Competition.autonomous( autonomous );
  Competition.drivercontrol( usercontrol );
  while(1) {
    vex::task::sleep(100);
  }    
}