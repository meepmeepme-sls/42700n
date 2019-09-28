#include "robot-config.h"
vex::competition    Competition;
//funtiond and varible setup for auto and dirver controle (primalrly auto tho)
//varibles (auto) | corrisopnds with thair respetible loops
int loop;
//other varibles
int CLpos;
int cl;
int udistance;
int ds;
int l1;
int t1;
int v1;
int currds;
int Speed;
int MaxSpeed;
int debug;
int temp;
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
//pid x axis movment
  void pdx(int Top_speed, int xdistance){
    //put pid code here
  }
//z axis movement Left|Right
  void dz(int zpower, int zdistance){
      LF.rotateFor(-zdistance, vex::rotationUnits::deg,zpower, vex::velocityUnits::pct,false);
      LB.rotateFor(zdistance, vex::rotationUnits::deg,zpower, vex::velocityUnits::pct,false);
      RF.rotateFor(-zdistance, vex::rotationUnits::deg,zpower, vex::velocityUnits::pct,false);
      RB.rotateFor(zdistance, vex::rotationUnits::deg,zpower, vex::velocityUnits::pct);
  }
//rotate on y axis movement RotateLeft|RotateRight | use gyro for rotate
  void dy(int ypower, int ydistance){
    LF.rotateFor(ydistance, vex::rotationUnits::deg,ypower, vex::velocityUnits::pct,false);
    LB.rotateFor(ydistance, vex::rotationUnits::deg,ypower, vex::velocityUnits::pct,false);
    RF.rotateFor(ydistance, vex::rotationUnits::deg,ypower, vex::velocityUnits::pct,false);
    RB.rotateFor(ydistance, vex::rotationUnits::deg,ypower, vex::velocityUnits::pct);
  }
//arm movement
  void arm(int apower, int adistance){
    AR.rotateTo(adistance, vex::rotationUnits::deg, apower, vex::velocityUnits::pct);
    AL.rotateTo(adistance, vex::rotationUnits::deg, apower, vex::velocityUnits::pct);
  }
//claw movment
  void claw(int c1power, int c1distance){
    CL.rotateFor(c1distance, vex::rotationUnits::deg,c1power, vex::velocityUnits::pct,false);
  }
//vision auto aliment
  void autoc( int dts, int aspeed){
	//sets speed
    LF.setVelocity(aspeed,vex::velocityUnits::pct);
    RF.setVelocity(aspeed,vex::velocityUnits::pct);
    LB.setVelocity(aspeed,vex::velocityUnits::pct);
    RB.setVelocity(aspeed,vex::velocityUnits::pct);	
	//sees if thair is a maching colloed object infront of the bot
    //left check
    if(Vision.largestObject.centerX < 105  && Sonar.distance(vex::distanceUnits::cm)>dts) {
    //strafe left
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("Sonar Distance is %f CM ",Sonar.distance(vex::distanceUnits::cm));
      Brain.Screen.setCursor(2,1);
      Brain.Screen.print("Left                       .");
      LB.spin(vex::directionType::rev);
      LF.spin(vex::directionType::fwd);
      RB.spin(vex::directionType::rev);
      RF.spin(vex::directionType::fwd);
      sleep(40);
    }
    else if (Vision.largestObject.centerX > 210 && Sonar.distance(vex::distanceUnits::cm)>dts) {
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
      sleep(40);
    }
    else if (Vision.largestObject.centerX < 210 && Vision.largestObject.centerX > 105 && Sonar.distance(vex::distanceUnits::cm)>dts) {
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
      sleep(40);
    }
    else if(Vision.objectCount == 1 && Sonar.distance(vex::distanceUnits::cm)<dts){
      LF.stop();
      RF.stop();
      LB.stop();
      RB.stop();
      loop = 0;
      Brain.Screen.setCursor(2,1);
    Controller1.Screen.print ("aliment compleated");
    }
  }
//preauto----------------------------------------------------------------------------------------------------------------------------
void pre_auton( void ) {
  loop = 0;
  cl = 0;
  t1 = false;
  CLpos = CL.value();
  //feedback for auto select
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
void Drive_stop( void ) {
  LF.stop();
  RF.stop();
  LB.stop();
  RB.stop();
}
void Move_Fwd(int pwr){
  LF.setVelocity(pwr,vex::velocityUnits::pct);
  RF.setVelocity(-1*pwr,vex::velocityUnits::pct);
  LB.setVelocity(pwr,vex::velocityUnits::pct);
  RB.setVelocity(-1*pwr,vex::velocityUnits::pct);
}
void Move_Right(int pwr){
  LF.setVelocity(pwr,vex::velocityUnits::pct);
  RF.setVelocity(pwr,vex::velocityUnits::pct);
  LB.setVelocity(-1*pwr,vex::velocityUnits::pct);
  RB.setVelocity(-1*pwr,vex::velocityUnits::pct);
}
void Move_Left(int pwr){
  LF.setVelocity(-1*pwr,vex::velocityUnits::pct);
  RF.setVelocity(-1*pwr,vex::velocityUnits::pct);
  LB.setVelocity(pwr,vex::velocityUnits::pct);
  RB.setVelocity(pwr,vex::velocityUnits::pct);
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
    //deadstick to cube~~
    dz(100,105);
    dx(150,540);
    dz(150,1080);
    sleep(100);

    //sets loop1 to true
    loop = 1;
    //auto aliment to cube
    while(loop == 1){
      Vision.takeSnapshot(SIG_2);
      autoc(10, 50);
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
    
    
    ds = (Sonar.distance(vex::distanceUnits::cm) -40);
    currds = ds;
    MaxSpeed = 120;
    while(ds > 0){
      ds = .95*ds+.05*(Sonar.distance(vex::distanceUnits::cm)-20);
      Speed = MaxSpeed;
      Speed = 6.*MaxSpeed*(ds/currds)+.4*MaxSpeed;
      Move_Fwd(Speed);
    }
    Drive_stop();

    //movment to wall
    //3.25in wheels
    //math for wall | pie * wheel size in mm = x | distance to travle in cm / x *360 = degrese to move 10 cm| x = 25.93384735538374 | stop 25 cm befor wall
    /*
    while(loop == 2){
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
      loop =  0;
      }
    }
    */
    //LINE SENSOR DOSENT WORK, HAVE TO MANULY PROGRAM A 3WIER SENSOR WHITS IS LESS ACURET THAN ABOVE
    Brain.Screen.printAt( 10, 50, "Line sensor %d", line1.value( analogUnits::pct ) );

    //move to line than start deadstick to gole zone
    l1 = line1.value(analogUnits::range12bit);
    loop = 3;
    while (loop == 3){
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
        loop = 3;
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
  else if(pot1.value(pct) >= 17 && pot1.value(pct) <=33){
    Brain.Screen.setCursor(5, 0);
    Brain.Screen.print("2");
    dx(150,300);
    dy(150,550);
    dx(150,105);
    loop = 1;
    while (loop == 1){
      Vision.takeSnapshot(SIG_2);
      autoc(10,50);
    }
    //pickup cube
    dx(50,100);
    //place cube in tower


    dx(50,-200);
    sleep(900000);
  }
  //red_mid2--------------------------------------
  else if(pot1.value(pct) >= 34 && pot1.value(pct) <=50){
    dx(150,1000);
    loop=1;
    while (loop == 1){
      //sees if thair is a maching colloed object infront of the bot
      Vision.takeSnapshot(SIG_2);
      autoc(10,50);
    }
    //place cube in tower


    //goes to next cube
    dx(-150,528);
    dy(-150,550);
    loop=2;
    while (loop == 2){
      Vision.takeSnapshot(SIG_2);
      autoc(10,50);
    }
    //get cube
    loop = 3;
    while(loop == 3){
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
        loop =  0;
       }
      }
    dy(50,550);
    dx(50,1163);
    sleep(900000);
  }
  //Blue-----------------------------------------------------------------
  //blue top--------------------------------------
  else if(pot1.value(pct) >= 51 && pot1.value(pct) <=67){
    Brain.Screen.setCursor(5, 0);
    Brain.Screen.print("Blue top running");
    dx(175, 300);
    //dx(150, 300);
    dy(50,450);
    dx(150, 300);
    dz(150, 300);
    //dz(100, -1125);
    loop=1;
    while(loop==1){
      Vision.takeSnapshot(SIG_3);
      autoc(20, 50);
    }
    //move claw
    sleep(100);
    dy(50, -450);
    //movment to wall
    //3.25in wheels
    //math for wall | pie * wheel size in mm = x | distance to travle in cm / x *360 = degrese to move 10 cm| x = 25.93384735538374 | stop 25 cm befor wall
    loop=2;
    while(loop == 2){
      ds = (Sonar.distance(vex::distanceUnits::cm) -40);
      if(ds <= 0){
        LF.stop();
        RF.stop();
        LB.stop();
        RB.stop();
      }
     else{
      udistance =(ds / 25.93384735538374 *360);
      uf(50);
      loop =  0;
      }
    }
    dy(150,-450);
    loop=3;
    while(loop==3){
      Vision.takeSnapshot(SIG_2);
      autoc(40, 50);
    }
    sleep(500);
    //move claw
    dx(150, -300);
  }
  //blue 2----------------------------------------| skills test
  else if(pot1.value(pct) >= 68 && pot1.value(pct) <=84){
    //5
    dz(150, -635);
    sleep(10);
    dz(150, 635);
    sleep(10);
    dx(150, 2245);
    dy(50, -450);
    arm(50, 50);
    loop=1;
    while (loop == 1){
      Vision.takeSnapshot(SIG_2);
      autoc(10,50);
    }
    sleep(100);
    //grabe cubes
    dx(100, 500);
    dy(100, 450);
    //auto to wall
    ds = (Sonar.distance(vex::distanceUnits::cm) -40);
    currds = ds;
    MaxSpeed = 120;
    while(ds > 0){
      ds = .95*ds+.05*(Sonar.distance(vex::distanceUnits::cm)-20);
      Speed = MaxSpeed;
      Speed = 6.*MaxSpeed*(ds/currds)+.4*MaxSpeed;
      Move_Fwd(Speed);
    }
    Drive_stop();
    dy(100, 450);
    dx(100, 900);
    loop=3;
    while (loop == 3){
      Vision.takeSnapshot(SIG_3);
      autoc(10,50);
    }
    sleep(100);
    //place cubes
    dx(150, -900);
    
  }
  //blue 3----------------------------------------
  else if(pot1.value(pct) >= 85 && pot1.value(pct) <=100){
    //6
  }
}
/*-----------------------------------------------------------------------------------------------------------------------------------    
User controle------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------*/  
void usercontrol ( void ) {
  Controller1.Screen.clearScreen();
  Brain.Screen.clearScreen();
  debug = true;
  temp = false; 
  while (true) {
    //top 2 rows debug
    //debug_______________________________________________________________________________________
    if (debug==true){
      //brain debuging output | comment out what isent needed
      Brain.Screen.setCursor(1,1);
      //Brain.Screen.print(" %f CM ",Sonar.distance(vex::distanceUnits::cm));
      //Brain.Screen.print("%d", line1.value( analogUnits::range12bit ));
      //Brain.Screen.print("%d", Vision.largestObject.width);
      //Brain.Screen.print("%t", AR.rotation(vex::rotationUnits::raw));
      //vexDeviceMotorVelocityPidSet(V5_DeviceT device, V5_DeviceMotorPid *pid);
      

      //controler debuging output | comment out what isent needed
      Controller1.Screen.print (" %f CM ",Sonar.distance(vex::distanceUnits::cm));
      //Controller1.Screen.print ("%d", line1.value( analogUnits::pct ));
      //Controller1.Screen.print("%d", Vision.largestObject.width);
      Controller1.Screen.print(".                             .");
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

    //preset hights
    if(Controller1.ButtonA.pressing()){
      //auto hight code
    }
    else if (Controller1.ButtonB.pressing()) {
      //autohight code
    }
    else if (Controller1.ButtonX.pressing()) {
      //autohight code
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
      RF.spin(vex::directionType::fwd, -Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct,false);
      RB.spin(vex::directionType::fwd, -Controller1.Axis3.value() - Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct,false);
      LB.spin(vex::directionType::fwd, Controller1.Axis3.value() - Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
    }
    sleep(10);
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