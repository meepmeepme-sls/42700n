#include "robot-config.h"
vex::competition    Competition;
//funtiond and varible setup for auto and dirver controle (primalrly auto tho)
//varibles (auto) | corrisopnds with thair respetible loops
int loop1;
int loop2;
int loop3;
//varibles user controle
int mloop1;
int mloop2;
int mloop3;
//other varibles
int cl;
int udistance;
int ds;
int l1;
int t1;
/*vex::task tstop(){
  if(Controller1.ButtonDown.pressing()){
    LF.stop();
    RF.stop();
    LB.stop();
    RB.stop();
    loop1=false;
    loop2=false;
    loop3=false;
    vex::task::sleep(10);
  }
  else{
    //nothing
    return;
  }
}*/
//move forwd with ultrasonic
  void uf(int upower){
    LF.rotateFor(udistance, vex::rotationUnits::deg,upower, vex::velocityUnits::pct,false);
    LB.rotateFor(udistance, vex::rotationUnits::deg,upower, vex::velocityUnits::pct,false);
    RF.rotateFor(-udistance, vex::rotationUnits::deg,upower, vex::velocityUnits::pct,false);
    RB.rotateFor(-udistance, vex::rotationUnits::deg,upower, vex::velocityUnits::pct);
  }
//sleep (shortened version of vex::task::sleep(x);) | napt = nap time LOL
  void sleep(int napt){
    vex::task::sleep(napt);
  }
//x axis movement Forward|Backward
  void dx(int xpower, int xdistance){
    LF.rotateFor(xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct,false);
    LB.rotateFor(xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct,false);
    RF.rotateFor(-xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct,false);
    RB.rotateFor(-xdistance, vex::rotationUnits::deg,xpower, vex::velocityUnits::pct);
  }
//z axis movement Left|Right
  void dz(int zpower, int zdistance){
      LF.rotateFor(-zdistance, vex::rotationUnits::deg,zpower, vex::velocityUnits::pct,false);
      LB.rotateFor(zdistance, vex::rotationUnits::deg,zpower, vex::velocityUnits::pct,false);
      RF.rotateFor(-zdistance, vex::rotationUnits::deg,zpower, vex::velocityUnits::pct,false);
      RB.rotateFor(zdistance, vex::rotationUnits::deg,zpower, vex::velocityUnits::pct);
  }
//rotate on y axis movement RotateLeft|RotateRight
  void dy(int ypower, int ydistance){
    LF.rotateFor(ydistance, vex::rotationUnits::deg,ypower, vex::velocityUnits::pct,false);
    LB.rotateFor(ydistance, vex::rotationUnits::deg,ypower, vex::velocityUnits::pct,false);
    RF.rotateFor(ydistance, vex::rotationUnits::deg,ypower, vex::velocityUnits::pct,false);
    RB.rotateFor(ydistance, vex::rotationUnits::deg,ypower, vex::velocityUnits::pct);
  }
//arm movement
  void a(int apower, int adistance){
    AR.rotateFor(adistance, vex::rotationUnits::deg,apower, vex::velocityUnits::pct,false);
    AL.rotateFor(adistance, vex::rotationUnits::deg,apower, vex::velocityUnits::pct,false);
  }
//somthing1 movment
  void c1(int c1power, int c1distance){
    CL.rotateFor(c1distance, vex::rotationUnits::deg,c1power, vex::velocityUnits::pct,false);
  }
//somthing2 movment
  void c2(int c2power, int c2distance){
    CR.rotateFor(c2distance, vex::rotationUnits::deg,c2power, vex::velocityUnits::pct,false);
  }
//preauto----------------------------------------------------------------------------------------------------------------------------
void pre_auton( void ) {
  loop1 = false;
  loop2 = false;
  cl = 0;
  t1 = false;
}
//Autonomous---------------------------------------------------------------------------------------------------------------------------
void autonomous( void ) {
  //red_top-----------------------------------------------------
  if(pot1.value(pct) <= 16 && pot1.value(pct) >=0){
    //put Autonomous code here    
    //deadstick to cube~~
    dz(100,105);
    dx(150,540);
    dz(150,1080);
    sleep(100);

    //sets loop1 to true
    loop1 = true;

    //auto aliment to cube
    while (loop1 == true){
      //sees if thair is a maching colloed object infront of the bot
      Vision.takeSnapshot(SIG_2);
      if(Vision.objectCount > 0) {
        //bot movment code
        if(Vision.largestObject.centerX < 105  && Sonar.distance(vex::distanceUnits::cm)>10) {
          //strafe left
          Brain.Screen.setCursor(1,1);
          Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("Left                       .");
          //shuld find a way to bost speed
          LF.setVelocity(-50,vex::velocityUnits::pct);
          RF.setVelocity(-50,vex::velocityUnits::pct);
          LB.setVelocity(50,vex::velocityUnits::pct);
          RB.setVelocity(50,vex::velocityUnits::pct);
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::fwd);
          RF.spin(vex::directionType::fwd);
          sleep(40);
          Vision.takeSnapshot(SIG_2);
        }
        else if (Vision.largestObject.centerX > 210 && Sonar.distance(vex::distanceUnits::cm)>10) {
          //for debuging
          Brain.Screen.setCursor(1,1);
          Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("right                       .");
          //strafe right
          LF.setVelocity(50,vex::velocityUnits::pct);
          RF.setVelocity(50,vex::velocityUnits::pct);
          LB.setVelocity(-50,vex::velocityUnits::pct);
          RB.setVelocity(-50,vex::velocityUnits::pct);
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::fwd);
          RF.spin(vex::directionType::fwd);
          sleep(40);
        }
        else if (Vision.largestObject.centerX < 210 && Vision.largestObject.centerX > 105 && Sonar.distance(vex::distanceUnits::cm)>10) {
          //for debuging
          Brain.Screen.setCursor(1,1);
          Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("forwd                       .");
          //go forwd
          LF.setVelocity(50,vex::velocityUnits::pct);
          RF.setVelocity(-50,vex::velocityUnits::pct);
          LB.setVelocity(50,vex::velocityUnits::pct);
          RB.setVelocity(-50,vex::velocityUnits::pct);
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::fwd);
          RF.spin(vex::directionType::fwd);
          sleep(40);
        }
        else if(Vision.objectCount == 1 && Sonar.distance(vex::distanceUnits::cm)<10){
          LF.stop();
          RF.stop();
          LB.stop();
          RB.stop();
          loop1 = false;
          Brain.Screen.setCursor(2,1);
          Controller1.Screen.print ("aliment compleated");
        }
      }
    }

    //put claw code here | get cubes into claw
    Brain.Screen.print("moves claw                        .");  


    //sleep(150000);
    //ajust sleep timing below for claw movment
    sleep(1500);

    //rotate to wall
    dx(150,-280);
    dy(150,550);
    sleep(100);

    //movment to wall
    //3.25in wheels
    //math for wall | pie * wheel size in mm = x | distance to travle in cm / x *360 = degrese to move 10 cm| x = 25.93384735538374 | stop 25 cm befor wall
    loop3 = true;
    while(loop3 == true){
      ds = (Sonar.distance(vex::distanceUnits::cm) -40);
      if(ds <= 0){
        LF.stop();
        RF.stop();
        LB.stop();
        RB.stop();
      }
     else{
      udistance =(ds / 25.93384735538374 *360);
      uf(150);
     dy(150,450);
      loop3 =  false;
      }
    }
    //sleep for debuging purpuses
    //sleep(1500000);

    //LINE SENSOR DOSENT WORK, HAVE TO MANULY PROGRAM A 3WIER SENSOR WHITS IS LESS ACURET THAN ABOVE
    Brain.Screen.printAt( 10, 50, "Line sensor %d", line1.value( analogUnits::pct ) );

    //move to line than start deadstick to gole zone
    l1 = line1.value(analogUnits::range12bit);
    loop2 = true;


    while (loop2 == true){
      Controller1.Screen.print ("%d", line1.value( analogUnits::range12bit ));
      if(line1.value(analogUnits::range12bit) < 1000){
        //ends the loop | than start deadstick to cube (code is right after the loop)
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print("start deadstick                       .");
        LF.stop();
        RF.stop();
        LB.stop();
        RB.stop();
        //Controller1.Screen.print ("%d", line1.value( analogUnits::pct ));
        loop2 = false;
      }
      else if(line1.value(analogUnits::range12bit) > 1001){
        //keep moving fowrd
        Brain.Screen.setCursor(2,2);
        Brain.Screen.print("keep going                        .");
        LF.setVelocity(150,vex::velocityUnits::pct);
        RF.setVelocity(-150,vex::velocityUnits::pct);
        LB.setVelocity(150,vex::velocityUnits::pct);
        RB.setVelocity(-150,vex::velocityUnits::pct);
        LB.spin(vex::directionType::fwd);
        LF.spin(vex::directionType::fwd);
        RB.spin(vex::directionType::fwd);
        RF.spin(vex::directionType::fwd);
      }
    }



    //deadstick code here
    Controller1.Screen.print ("start deadstick2");


    //after deadstick long wait than end
    sleep(500000);
  }
  //red_mid---------------------------------------
  else if(pot1.value(pct) <= 17 && pot1.value(pct) >=33){
    dx(150,300);
    dy(150,550);
    dx(150,105);
    loop1=true;
    while (loop1 == true){
      //sees if thair is a maching colloed object infront of the bot
      Vision.takeSnapshot(SIG_2);
      if(Vision.objectCount > 0) {
        //bot movment code
        if(Vision.largestObject.centerX < 105  && Sonar.distance(vex::distanceUnits::cm)>10) {
          //strafe left
          Brain.Screen.setCursor(1,1);
          Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("Left                       .");
          //shuld find a way to bost speed
          LF.setVelocity(-50,vex::velocityUnits::pct);
          RF.setVelocity(-50,vex::velocityUnits::pct);
          LB.setVelocity(50,vex::velocityUnits::pct);
          RB.setVelocity(50,vex::velocityUnits::pct);
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::fwd);
          RF.spin(vex::directionType::fwd);
          sleep(40);
          Vision.takeSnapshot(SIG_2);
        }
        else if (Vision.largestObject.centerX > 210 && Sonar.distance(vex::distanceUnits::cm)>10) {
          //for debuging
          Brain.Screen.setCursor(1,1);
          Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("right                       .");
          //strafe right
          LF.setVelocity(50,vex::velocityUnits::pct);
          RF.setVelocity(50,vex::velocityUnits::pct);
          LB.setVelocity(-50,vex::velocityUnits::pct);
          RB.setVelocity(-50,vex::velocityUnits::pct);
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::fwd);
          RF.spin(vex::directionType::fwd);
          sleep(40);
        }
        else if (Vision.largestObject.centerX < 210 && Vision.largestObject.centerX > 105 && Sonar.distance(vex::distanceUnits::cm)>10) {
          //for debuging
          Brain.Screen.setCursor(1,1);
          Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("forwd                       .");
          //go forwd
          LF.setVelocity(50,vex::velocityUnits::pct);
          RF.setVelocity(-50,vex::velocityUnits::pct);
          LB.setVelocity(50,vex::velocityUnits::pct);
          RB.setVelocity(-50,vex::velocityUnits::pct);
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::fwd);
          RF.spin(vex::directionType::fwd);
          sleep(40);
        }
        else if(Vision.objectCount == 1 && Sonar.distance(vex::distanceUnits::cm)<10){
          LF.stop();
          RF.stop();
          LB.stop();
          RB.stop();
          loop1 = false;
          Brain.Screen.setCursor(2,1);
          Controller1.Screen.print ("aliment compleated");
        }
      }
    }
    //pickup cube
    dx(50,100);
    //place cube in tower
    dx(50,-200);
    sleep(900000);
  }
  //red_mid2--------------------------------------
  else if(pot1.value(pct) <= 34 && pot1.value(pct) >=50){
    dx(150,1000);
    loop1=true;
    while (loop1 == true){
      //sees if thair is a maching colloed object infront of the bot
      Vision.takeSnapshot(SIG_2);
      if(Vision.objectCount > 0) {
        //bot movment code
        if(Vision.largestObject.centerX < 105  && Sonar.distance(vex::distanceUnits::cm)>10) {
          //strafe left
          Brain.Screen.setCursor(1,1);
          Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("Left                       .");
          //shuld find a way to bost speed
          LF.setVelocity(-50,vex::velocityUnits::pct);
          RF.setVelocity(-50,vex::velocityUnits::pct);
          LB.setVelocity(50,vex::velocityUnits::pct);
          RB.setVelocity(50,vex::velocityUnits::pct);
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::fwd);
          RF.spin(vex::directionType::fwd);
          sleep(40);
          Vision.takeSnapshot(SIG_2);
        }
        else if (Vision.largestObject.centerX > 210 && Sonar.distance(vex::distanceUnits::cm)>10) {
          //for debuging
          Brain.Screen.setCursor(1,1);
          Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("right                       .");
          //strafe right
          LF.setVelocity(50,vex::velocityUnits::pct);
          RF.setVelocity(50,vex::velocityUnits::pct);
          LB.setVelocity(-50,vex::velocityUnits::pct);
          RB.setVelocity(-50,vex::velocityUnits::pct);
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::fwd);
          RF.spin(vex::directionType::fwd);
          sleep(40);
        }
        else if (Vision.largestObject.centerX < 210 && Vision.largestObject.centerX > 105 && Sonar.distance(vex::distanceUnits::cm)>10) {
          //for debuging
          Brain.Screen.setCursor(1,1);
          Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("forwd                       .");
          //go forwd
          LF.setVelocity(50,vex::velocityUnits::pct);
          RF.setVelocity(-50,vex::velocityUnits::pct);
          LB.setVelocity(50,vex::velocityUnits::pct);
          RB.setVelocity(-50,vex::velocityUnits::pct);
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::fwd);
          RF.spin(vex::directionType::fwd);
          sleep(40);
        }
        else if(Vision.objectCount == 1 && Sonar.distance(vex::distanceUnits::cm)<10){
          LF.stop();
          RF.stop();
          LB.stop();
          RB.stop();
          loop1 = false;
          Brain.Screen.setCursor(2,1);
          Controller1.Screen.print ("aliment compleated");
        }
      }
    }
    //place cube
    dx(-150,528);
    dy(-150,550);
    loop2=true;
    while (loop2 == true){
      //sees if thair is a maching colloed object infront of the bot
      Vision.takeSnapshot(SIG_2);
      if(Vision.objectCount > 0) {
        //bot movment code
        if(Vision.largestObject.centerX < 105  && Sonar.distance(vex::distanceUnits::cm)>10) {
          //strafe left
          Brain.Screen.setCursor(1,1);
          Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("Left                       .");
          //shuld find a way to bost speed
          LF.setVelocity(-50,vex::velocityUnits::pct);
          RF.setVelocity(-50,vex::velocityUnits::pct);
          LB.setVelocity(50,vex::velocityUnits::pct);
          RB.setVelocity(50,vex::velocityUnits::pct);
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::fwd);
          RF.spin(vex::directionType::fwd);
          sleep(40);
          Vision.takeSnapshot(SIG_2);
        }
        else if (Vision.largestObject.centerX > 210 && Sonar.distance(vex::distanceUnits::cm)>10) {
          //for debuging
          Brain.Screen.setCursor(1,1);
          Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("right                       .");
          //strafe right
          LF.setVelocity(50,vex::velocityUnits::pct);
          RF.setVelocity(50,vex::velocityUnits::pct);
          LB.setVelocity(-50,vex::velocityUnits::pct);
          RB.setVelocity(-50,vex::velocityUnits::pct);
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::fwd);
          RF.spin(vex::directionType::fwd);
          sleep(40);
        }
        else if (Vision.largestObject.centerX < 210 && Vision.largestObject.centerX > 105 && Sonar.distance(vex::distanceUnits::cm)>10) {
          //for debuging
          Brain.Screen.setCursor(1,1);
          Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
          Brain.Screen.setCursor(2,1);
          Brain.Screen.print("forwd                       .");
          //go forwd
          LF.setVelocity(50,vex::velocityUnits::pct);
          RF.setVelocity(-50,vex::velocityUnits::pct);
          LB.setVelocity(50,vex::velocityUnits::pct);
          RB.setVelocity(-50,vex::velocityUnits::pct);
          LB.spin(vex::directionType::fwd);
          LF.spin(vex::directionType::fwd);
          RB.spin(vex::directionType::fwd);
          RF.spin(vex::directionType::fwd);
          sleep(40);
        }
        else if(Vision.objectCount == 1 && Sonar.distance(vex::distanceUnits::cm)<10){
          LF.stop();
          RF.stop();
          LB.stop();
          RB.stop();
          loop2=false;
          Brain.Screen.setCursor(2,1);
          Controller1.Screen.print ("aliment compleated");
        }
      }
    }
    //get cube
    loop3 = true;
    while(loop3 == true){
      ds = (Sonar.distance(vex::distanceUnits::cm) -40);
      if(ds <= 0){
        LF.stop();
        RF.stop();
        LB.stop();
        RB.stop();
      }
     else{
      udistance =(ds / 25.93384735538374 *360);
      uf(150);
     dy(150,450);
      loop3 =  false;
      }
    }
    dy(50,550);
    dx(50,1163);
    sleep(900000);
  }
  //red-----------------------------------------------------------------
  else if(pot1.value(pct) <= 51 && pot1.value(pct) >=67){
    //4
  }
  else if(pot1.value(pct) <= 68 && pot1.value(pct) >=84){
    //5
  }
  else if(pot1.value(pct) <= 85 && pot1.value(pct) >=100){
    //5
  }
}

/*-----------------------------------------------------------------------------------------------------------------------------------    
User controle------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------*/  
void usercontrol ( void ) {
  Brain.Screen.clearScreen();
  while (1) {
    //tstop();
    
    //debugging_____________________________________________________________________________________

    //brain debuging output | comment out what isent needed
    Brain.Screen.setCursor(1,1);
    //Brain.Screen.print(" %f CM ",Sonar.distance(vex::distanceUnits::cm));
    //Brain.Screen.print("%d", line1.value( analogUnits::range12bit ));
    //Brain.Screen.print("%d", Vision2.largestObject.width);

    //controler debuging output | comment out what isent needed
    Controller1.Screen.print (" %f CM ",Sonar.distance(vex::distanceUnits::cm));
    //Controller1.Screen.print ("%d", line1.value( analogUnits::pct ));
    //Controller1.Screen.print("%d", Vision2.largestObject.width);

    //Drive________________________________________________________________________________________

    //Holonomic_X_drive driver controle
    LF.spin(vex::directionType::fwd, Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
    RF.spin(vex::directionType::fwd, -Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
    RB.spin(vex::directionType::fwd, -Controller1.Axis3.value() - Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
    LB.spin(vex::directionType::fwd, Controller1.Axis3.value() - Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
  
    //othe_controle_surfaes________________________________________________________________________
    
    //Rrme
    if(Controller1.ButtonA.pressing()) {
      AR.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      AL.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonB.pressing()) {
      AR.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
      AL.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    else {
      AR.stop(vex::brakeType::brake);
      AL.stop(vex::brakeType::brake);
    }
    
    //claw
    if(Controller1.ButtonL1.pressing()) {
      CL.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonL2.pressing()) {
      CL.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    else {
      CL.stop(vex::brakeType::brake);
    }
    
    //other
    if(Controller1.ButtonR1.pressing()) {
      CR.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonR2.pressing()) {
      CR.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
    }
    else {
      CR.stop(vex::brakeType::brake);
    }

    //auto aliment trigers___________________________________________________________________________
    //this may seem all dume but put the shek fo ontroler button pressing in the loop
    
    //autoaline green
    if(Controller1.ButtonUp.pressing()){
      mloop1=true;
    }
    else{
      mloop1=false;
    }
  //autoaline orange
  if(Controller1.ButtonRight.pressing()){
    mloop2=true;
  }
  else{
    mloop2=false;
  }
  //autoaline purple
  if(Controller1.ButtonLeft.pressing()){
    mloop3=true;
  }
  else{
    mloop3=false;
  }

    
  while (mloop1 == true){
    Brain.Screen.print("1 ");
    Vision.takeSnapshot(SIG_2);
    if(Vision.objectCount > 0) {
      Brain.Screen.print("2 ");
      //bot movment code
      if(Vision.largestObject.centerX < 105  && Sonar.distance(vex::distanceUnits::cm)>10 && Controller1.ButtonDown.pressing()==false) {
        //strafe left
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
        Brain.Screen.setCursor(2,1);
        Brain.Screen.print("Left                       .");
        //shuld find a way to bost speed
        LF.setVelocity(-50,vex::velocityUnits::pct);
        RF.setVelocity(-50,vex::velocityUnits::pct);
        LB.setVelocity(50,vex::velocityUnits::pct);
        RB.setVelocity(50,vex::velocityUnits::pct);
        LB.spin(vex::directionType::fwd);
        LF.spin(vex::directionType::fwd);
        RB.spin(vex::directionType::fwd);
        RF.spin(vex::directionType::fwd);
        sleep(40);
        Vision.takeSnapshot(SIG_2);
      }
      else if (Vision.largestObject.centerX > 210 && Sonar.distance(vex::distanceUnits::cm)>10 && Controller1.ButtonDown.pressing()==false) {
        //for debuging
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
        Brain.Screen.setCursor(2,1);
        Brain.Screen.print("right                       .");
        //strafe right
        LF.setVelocity(50,vex::velocityUnits::pct);
        RF.setVelocity(50,vex::velocityUnits::pct);
        LB.setVelocity(-50,vex::velocityUnits::pct);
        RB.setVelocity(-50,vex::velocityUnits::pct);
        LB.spin(vex::directionType::fwd);
        LF.spin(vex::directionType::fwd);
        RB.spin(vex::directionType::fwd);
        RF.spin(vex::directionType::fwd);
        sleep(40);
      }
      else if (Vision.largestObject.centerX < 210 && Vision.largestObject.centerX > 105 && Sonar.distance(vex::distanceUnits::cm)>10 && Controller1.ButtonDown.pressing()==false) {
        //for debuging
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
        Brain.Screen.setCursor(2,1);
        Brain.Screen.print("forwd                       .");
        //go forwd
        LF.setVelocity(50,vex::velocityUnits::pct);
        RF.setVelocity(-50,vex::velocityUnits::pct);
        LB.setVelocity(50,vex::velocityUnits::pct);
        RB.setVelocity(-50,vex::velocityUnits::pct);
        LB.spin(vex::directionType::fwd);
        LF.spin(vex::directionType::fwd);
        RB.spin(vex::directionType::fwd);
        RF.spin(vex::directionType::fwd);
        sleep(40);
      }
      else if(Vision.objectCount == 1 && Sonar.distance(vex::distanceUnits::cm)<10 && Controller1.ButtonDown.pressing()==false){
        mloop1 = false;
        LF.stop();
        RF.stop();
        LB.stop();
        RB.stop();
        Controller1.Screen.print ("Aliment done");
        //mloop1 = false;
      }
      else if(Controller1.ButtonDown.pressing()){
        mloop1 = false;
        LF.stop();
        RF.stop();
        LB.stop();
        RB.stop();
        Controller1.Screen.print ("Aliment error");
        //mloop1 = false; 
      }
    }
  }
  while (mloop2 == true){
    Brain.Screen.print("1 ");
    Vision.takeSnapshot(SIG_1);
    if(Vision.objectCount > 0) {
      Brain.Screen.print("2 ");
      //bot movment code
      if(Vision.largestObject.centerX < 105  && Sonar.distance(vex::distanceUnits::cm)>10 && Controller1.ButtonDown.pressing()==false) {
        //strafe left
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
        Brain.Screen.setCursor(2,1);
        Brain.Screen.print("Left                       .");
        //shuld find a way to bost speed
        LF.setVelocity(-50,vex::velocityUnits::pct);
        RF.setVelocity(-50,vex::velocityUnits::pct);
        LB.setVelocity(50,vex::velocityUnits::pct);
        RB.setVelocity(50,vex::velocityUnits::pct);
        LB.spin(vex::directionType::fwd);
        LF.spin(vex::directionType::fwd);
        RB.spin(vex::directionType::fwd);
        RF.spin(vex::directionType::fwd);
        sleep(40);
        Vision.takeSnapshot(SIG_1);
      }
    }
      else if (Vision.largestObject.centerX > 210 && Sonar.distance(vex::distanceUnits::cm)>10 && Controller1.ButtonDown.pressing()==false) {
        //for debuging
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
        Brain.Screen.setCursor(2,1);
        Brain.Screen.print("right                       .");
        //strafe right
        LF.setVelocity(50,vex::velocityUnits::pct);
        RF.setVelocity(50,vex::velocityUnits::pct);
        LB.setVelocity(-50,vex::velocityUnits::pct);
        RB.setVelocity(-50,vex::velocityUnits::pct);
        LB.spin(vex::directionType::fwd);
        LF.spin(vex::directionType::fwd);
        RB.spin(vex::directionType::fwd);
        RF.spin(vex::directionType::fwd);
        sleep(40);
      }
      else if (Vision.largestObject.centerX < 210 && Vision.largestObject.centerX > 105 && Sonar.distance(vex::distanceUnits::cm)>10 && Controller1.ButtonDown.pressing()==false) {
        //for debuging
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
        Brain.Screen.setCursor(2,1);
        Brain.Screen.print("forwd                       .");
        //go forwd
        LF.setVelocity(50,vex::velocityUnits::pct);
        RF.setVelocity(-50,vex::velocityUnits::pct);
        LB.setVelocity(50,vex::velocityUnits::pct);
        RB.setVelocity(-50,vex::velocityUnits::pct);
        LB.spin(vex::directionType::fwd);
        LF.spin(vex::directionType::fwd);
        RB.spin(vex::directionType::fwd);
        RF.spin(vex::directionType::fwd);
        sleep(40);
      }
      else if(Vision.objectCount == 1 && Sonar.distance(vex::distanceUnits::cm)<10 && Controller1.ButtonDown.pressing()==false){
        LF.stop();
        RF.stop();
        LB.stop();
        RB.stop();
        Controller1.Screen.print ("Aliment done");
        mloop2 = false;
      }
      else if(Controller1.ButtonDown.pressing()){
        LF.stop();
        RF.stop();
        LB.stop();
        RB.stop();
        Controller1.Screen.print ("Aliment error");
        mloop2 = false; 
      }
    }
  }
  while (mloop3 == true){
    Brain.Screen.print("1 ");
    Vision.takeSnapshot(SIG_3);
    if(Vision.objectCount > 0) {
      Brain.Screen.print("2 ");
      //bot movment code
      if(Vision.largestObject.centerX < 105  && Sonar.distance(vex::distanceUnits::cm)>10 && Controller1.ButtonDown.pressing()==false) {
        //strafe left
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
        Brain.Screen.setCursor(2,1);
        Brain.Screen.print("Left                       .");
        //shuld find a way to bost speed
        LF.setVelocity(-50,vex::velocityUnits::pct);
        RF.setVelocity(-50,vex::velocityUnits::pct);
        LB.setVelocity(50,vex::velocityUnits::pct);
        RB.setVelocity(50,vex::velocityUnits::pct);
        LB.spin(vex::directionType::fwd);
        LF.spin(vex::directionType::fwd);
        RB.spin(vex::directionType::fwd);
        RF.spin(vex::directionType::fwd);
        sleep(40);
        Vision.takeSnapshot(SIG_3);
      }
      else if (Vision.largestObject.centerX > 210 && Sonar.distance(vex::distanceUnits::cm)>10 && Controller1.ButtonDown.pressing()==false) {
        //for debuging
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
        Brain.Screen.setCursor(2,1);
        Brain.Screen.print("right                       .");
        //strafe right
        LF.setVelocity(50,vex::velocityUnits::pct);
        RF.setVelocity(50,vex::velocityUnits::pct);
        LB.setVelocity(-50,vex::velocityUnits::pct);
        RB.setVelocity(-50,vex::velocityUnits::pct);
        LB.spin(vex::directionType::fwd);
        LF.spin(vex::directionType::fwd);
        RB.spin(vex::directionType::fwd);
        RF.spin(vex::directionType::fwd);
        sleep(40);
      }
      else if (Vision.largestObject.centerX < 210 && Vision.largestObject.centerX > 105 && Sonar.distance(vex::distanceUnits::cm)>10 && Controller1.ButtonDown.pressing()==false) {
        //for debuging
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
        Brain.Screen.setCursor(2,1);
        Brain.Screen.print("forwd                       .");
        //go forwd
        LF.setVelocity(50,vex::velocityUnits::pct);
        RF.setVelocity(-50,vex::velocityUnits::pct);
        LB.setVelocity(50,vex::velocityUnits::pct);
        RB.setVelocity(-50,vex::velocityUnits::pct);
        LB.spin(vex::directionType::fwd);
        LF.spin(vex::directionType::fwd);
        RB.spin(vex::directionType::fwd);
        RF.spin(vex::directionType::fwd);
        sleep(40);
      }
      else if(Vision.objectCount == 1 && Sonar.distance(vex::distanceUnits::cm)<10 && Controller1.ButtonDown.pressing()==false){
        LF.stop();
        RF.stop();
        LB.stop();
        RB.stop();
        Controller1.Screen.print ("Aliment done");
        mloop3 = false;
      }
      else if(Controller1.ButtonDown.pressing()){
        LF.stop();
        RF.stop();
        LB.stop();
        RB.stop();
        Controller1.Screen.print ("Aliment error");
        mloop3 = false; 
      }
    }
  }
  //shuld i have 2 controle with the screen on controler 2 reading all of the bots actions?
  //shuld i take out sleep, causes screen flicker but saves come battery?
    //sleep(20);
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