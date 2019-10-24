/*    loop = 3;
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
      }*/


          //deadstick to cube~~


/*    dz(100,105);
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
    
    while(loop == 2){
      ds = (Sonar.distance(vex::distanceUnits::cm) -40);
      if(ds <= 0){
        LF.stop();
        RF.stop(); m
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

*/
/*  //blue 2----------------------------------------| skills test
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
*/
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
    //toggle switch for switching between tank and arcade drive____________________________________
    /*if(Controller1.ButtonY.pressing()==true&&ToggleState == false){
      //tank drive
      Controller1.Screen.print ("Warning                           .");
      ToggleState = true;
      sleep(200);
    }
    //arcade drive
    else if(Controller1.ButtonY.pressing()==true&&ToggleState == true) {
      Controller1.Screen.print ("Warning                           .");
      
      sleep(200);
      ToggleState=false;
    }*/
        /*Equation is intended value-current value and multiply the result by 5 (for gear ratio convrsions) and feed the motrs to go to that value.
    Reson for doing this is the potenteomiters valu will always be constant while the moter encoders value will differ between runs.*/