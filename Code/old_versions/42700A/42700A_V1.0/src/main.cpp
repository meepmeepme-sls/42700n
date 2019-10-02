#include "Funtions.h"
vex::competition    Competition;
//preauto----------------------------------------------------------------------------------------------------------------------------
void pre_auton( void ) {
	//resets all varibles befor comp
	loop = 0;
	cl = 0;
  autoselect = true;
	//Autonomous select using the potentiomiter|feed back goes to brain
	while(autoselect == true){
		Brain.Screen.setCursor(2, 20);
		if(pot1.value(pct) <= 16 && pot1.value(pct) >=0){
			Brain.Screen.print("Auto: Red 1 ");
			Controller1.Screen.print("Auto: Red 1                           .");
		}
		else if (pot1.value(pct) >= 17 && pot1.value(pct) <=33) {
			Brain.Screen.print("Auto: Red 2 ");
			Controller1.Screen.print("Auto: Red 2                           .");
		}
		else if(pot1.value(pct) >= 34 && pot1.value(pct) <=50){
			Brain.Screen.print("Auto: Red 3 ");
			Controller1.Screen.print("Auto: Red 3                           .");
		}
		else if(pot1.value(pct) >= 51 && pot1.value(pct) <=67){
			Brain.Screen.print("Auto: Blue 1");
			Controller1.Screen.print("Auto: Blue 1                           .");
		}
		else if(pot1.value(pct) >= 68 && pot1.value(pct) <=84){
			Brain.Screen.print("Auto: Blue 2");
			Controller1.Screen.print("Auto: Blue 2                           .");
		}
		else if(pot1.value(pct) >= 85 && pot1.value(pct) <=100){
			//Brain.Screen.print("Blue3");
			Brain.Screen.print("Auto: Blue 3");
			Controller1.Screen.print("Auto: Blue 3                           .");
		}
	}
}
/*-----------------------------------------------------------------------------------------------------------------------------------    
Autonomous---------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------*/
void autonomous( void ) {
	//red 1-----------------------------------------------------
	if(pot1.value(pct) >= 16 && pot1.value(pct) <=0){
		Controller1.Screen.print("red 1 running");
    dx(100, -375);
		Controller1.Screen.print("red 1 done");
	}
	//red 2---------------------------------------
	else if(pot1.value(pct) >= 17 && pot1.value(pct) <=33){
		Controller1.Screen.print("red 2 running");
		Controller1.Screen.print("red 2 done");
	}
	//red 3--------------------------------------
	else if(pot1.value(pct) >= 34 && pot1.value(pct) <=50){
		Controller1.Screen.print("red 3 running");
    //for deploying the intake
    arm(100, 500,true);
    arm(100, 500,true);
    //start the intke in
		intake(200);
    //go foward with sleep at the end to stop
		dx(50, 650);
		sleep(50);
    //go backward and stop intake
		dx(100, -600);
		intake(0);
    //trun right
		dy(50, 450);
		sleep(10);
    //strafe left
		dz(50, 200);
		sleep(10);
    //go foward
		dx(50, 200);
    //place cubs in scoring zone
		intake(-200);
		sleep(1000);
		dx(50,-200);
		intake(0);
		Controller1.Screen.print("red 3 done");
	}
	//Blue-----------------------------------------------------------------
	//blue 1---------------------------------------
	else if(pot1.value(pct) >= 51 && pot1.value(pct) <=67){
		Controller1.Screen.print("Blue 1 running");
    dx(100, -375);
		Controller1.Screen.print("Blue 1 stop");
	}
	//blue 2----------------------------------------
	else if(pot1.value(pct) >= 68 && pot1.value(pct) <=84){
		Controller1.Screen.print("Blue 2 running");

		Controller1.Screen.print("Blue 2 stop");
	}
	//blue 3----------------------------------------
	else if(pot1.value(pct) >= 85 && pot1.value(pct) <=100){
		Controller1.Screen.print("Blue 3 running");
    arm(100, 500,true);
    arm(100, 500,true);
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
  //resets and enables/disables things for driver controle
  OH=false;
  autoselect = true;
	temp = true; 
  vex::thread TS(ToggleButton); 
	//optinal menu
	debug = true;
	//clears brain screen befor driver use
	Brain.Screen.clearScreen();
  Controller1.Screen.clearLine(3);

	while (true) {
		//top 2 rows debug
		//debug________________________________________________________________________________________
		if (debug==true){
			//brain debuging output | comment out what isent needed
			Brain.Screen.setCursor(1,1);
			//Brain.Screen.print(" %f CM ",Sonar.distance(vex::distanceUnits::cm));
			//Brain.Screen.print("%d", line1.value( analogUnits::range12bit ));
			//Brain.Screen.print("%d", Vision.largestObject.width);
			//Brain.Screen.print("%t", AR.rotation(deg));
      Brain.Screen.print ("%f",pot2.value(vex::rotationUnits::deg));
      Brain.Screen.setCursor(1,20);
      Brain.Screen.print ("%f",AL.rotation(vex::rotationUnits::deg));

			//controler debuging output | comment out what isent needed
			//Controller1.Screen.print (" %f CM ",Sonar.distance(vex::distanceUnits::cm));
			//Controller1.Screen.print ("%f", AR.rotation(vex::rotationUnits::deg));
			//Controller1.Screen.print ("%d", line1.value( analogUnits::pct ));
			//Controller1.Screen.print("%d", Vision.largestObject.width);
      //Controller1.Screen.print ("%f",pot2.value(vex::rotationUnits::deg));
			//Controller1.Screen.print(".                             .");
		}
		//motor temp feed back_________________________________________________________________________
		if (temp==true){
			if(LF.temperature(pct)>70){
				Brain.Screen.setCursor(4, 1);
        OH=true;
				Brain.Screen.print("LF temp");
        Controller1.Screen.print("LF temp");
			}
			else if(LF.temperature(pct)>50&&LF.temperature(pct)<70){
				Brain.Screen.setCursor(4, 1);
				Brain.Screen.print("LF warm");
			}
			if(LB.temperature(pct)>70){
				Brain.Screen.setCursor(4, 10);
        OH=true;
				Brain.Screen.print("LB temp");
        Controller1.Screen.print("LB temp");
			}
			else if(LB.temperature(pct)>50&&LF.temperature(pct)<70){
				Brain.Screen.setCursor(4, 10);
				Brain.Screen.print("LB warm");
			}
			if(RF.temperature(pct)>70){
				Brain.Screen.setCursor(4, 20);
        OH=true;
				Brain.Screen.print("RF temp");
        Controller1.Screen.print("RF temp");
			}
			else if(RF.temperature(pct)>50&&RF.temperature(pct)<70){
				Brain.Screen.setCursor(4, 20);
				Brain.Screen.print("RF warm");
			}
			if(RB.temperature(pct)>70){
				Brain.Screen.setCursor(4, 30);
        OH=true;
				Brain.Screen.print("RB temp");
        Controller1.Screen.print("RB temp");
			}
			else if(RB.temperature(pct)>50&&RB.temperature(pct)<70){
				Brain.Screen.setCursor(4, 300);
				Brain.Screen.print("RB warm");
			}
			if(AR.temperature(pct)>70){
				Brain.Screen.setCursor(3, 1);
        OH=true;
				Brain.Screen.print("AR temp");
        Controller1.Screen.print("AR temp");
			}
			else if(AR.temperature(pct)>50&&AR.temperature(pct)<70){
				Brain.Screen.setCursor(3, 1);
				Brain.Screen.print("AR warm");
			}
			if(AL.temperature(pct)>70){
				Brain.Screen.setCursor(3, 10);
        OH=true;
				Brain.Screen.print("AL temp");
        Controller1.Screen.print("AL temp");
			}
			else if(AL.temperature(pct)>50&&AL.temperature(pct)<70){
				Brain.Screen.setCursor(3, 10);
				Brain.Screen.print("AL warm");
			}
			if(CL.temperature(pct)>70){
				Brain.Screen.setCursor(3, 20);
        OH=true;
				Brain.Screen.print("CL temp");
        Controller1.Screen.print("CL temp");
			}
			else if(CL.temperature(pct)>50&&CL.temperature(pct)<70){
				Brain.Screen.setCursor(3, 20);
				Brain.Screen.print("CL warm");
      }
			if(CR.temperature(pct)>70){
				Brain.Screen.setCursor(3, 25);
        OH=true;
				Brain.Screen.print("CR temp");
        Controller1.Screen.print("CR temp");
			}
			else if(CR.temperature(pct)>50&&CR.temperature(pct)<70){
				Brain.Screen.setCursor(3, 25);
				Brain.Screen.print("CR warm");
      }
		}
		//Dubble reverse 4 bar__________________________________________________________________________
		if(Controller1.ButtonR1.pressing()) {
			AR.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
			AL.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
		}
		else if(Controller1.ButtonR2.pressing()) {
			AR.spin(vex::directionType::rev, 95, vex::velocityUnits::pct);
			AL.spin(vex::directionType::fwd, 95, vex::velocityUnits::pct);
		}
		//preset hights low tower
		else if(Controller1.ButtonB.pressing()){
			AR.rotateTo(540, deg,100,velocityUnits::pct,false);
			AL.rotateTo(-540, deg,100,velocityUnits::pct,false);
		}
		//preset hights mid tower
		else if (Controller1.ButtonX.pressing()){
			AR.rotateTo(1080, deg,100,velocityUnits::pct,false);
			AL.rotateTo(-1080, deg,100,velocityUnits::pct,false);
		}
		//preset hights high tower
		else if (Controller1.ButtonA.pressing()) {
			AR.rotateTo(680, deg,100,velocityUnits::pct,false);
			AL.rotateTo(-680, deg,100,velocityUnits::pct,false);
		}
		//stop
		else {
			AR.stop(vex::brakeType::brake);
			AL.stop(vex::brakeType::brake);
		}
    //arm moter encoder reset
    if(Controller1.ButtonRight.pressing()){
      AR.resetRotation();
      AL.resetRotation();
    }
		//intake________________________________________________________________________________________
		//in
		if(Controller1.ButtonL1.pressing()) {
			CR.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
			CL.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
		}
		//out
		else if(Controller1.ButtonL2.pressing()) {
			CR.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
			CL.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
		}
		//stop
		else {
			CL.stop(vex::brakeType::brake);
			CR.stop(vex::brakeType::brake);
		}
    Brain.Screen.setCursor(2,1);
		//drive and AutoAlign___________________________________________________________________________
		//Autoalign orange
		if(Controller1.ButtonUp.pressing()){
			Controller1.Screen.print ("Orange");
			Vision.takeSnapshot(Orange);
			if(Vision.objectCount > 0) {
				LF.setVelocity(75,vex::velocityUnits::pct);
				RF.setVelocity(75,vex::velocityUnits::pct);
				LB.setVelocity(75,vex::velocityUnits::pct);
				RB.setVelocity(75,vex::velocityUnits::pct);
				Brain.Screen.setCursor(2,1);
				//bot movment code
				if(Vision.largestObject.centerX < 105  && Sonar.distance(vex::distanceUnits::cm)>10 ) {
					//strafe left
					Brain.Screen.print("Left                       .");
					LB.spin(vex::directionType::rev);
					LF.spin(vex::directionType::fwd);
					RB.spin(vex::directionType::rev);
					RF.spin(vex::directionType::fwd);
					Vision.takeSnapshot(Orange);
				}
				else if (Vision.largestObject.centerX > 210 && Sonar.distance(vex::distanceUnits::cm)>10 ) {
					Brain.Screen.print("Right                       .");
					//strafe right
					LB.spin(vex::directionType::fwd);
					LF.spin(vex::directionType::rev);
					RB.spin(vex::directionType::fwd);
					RF.spin(vex::directionType::rev);
				}
				else if (Vision.largestObject.centerX < 210 && Vision.largestObject.centerX > 105 && Sonar.distance(vex::distanceUnits::cm)>10 ) {
					Brain.Screen.print("Forward                       .");
					//go forward
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
					Controller1.Screen.print ("Alignment done");
				}
			}
		}
		//Autoalign Green
		else if(Controller1.ButtonRight.pressing()){
			Controller1.Screen.print ("Green");
			Vision.takeSnapshot(Green);
			if(Vision.objectCount > 0) {
				LF.setVelocity(50,vex::velocityUnits::pct);
				RF.setVelocity(50,vex::velocityUnits::pct);
				LB.setVelocity(50,vex::velocityUnits::pct);
				RB.setVelocity(50,vex::velocityUnits::pct);
				Brain.Screen.setCursor(2,1);
				//bot movment code
				if(Vision.largestObject.centerX < 105  && Sonar.distance(vex::distanceUnits::cm)>10 ) {
					//strafe left
					Brain.Screen.print("Left                       .");
					LB.spin(vex::directionType::rev);
					LF.spin(vex::directionType::fwd);
					RB.spin(vex::directionType::rev);
					RF.spin(vex::directionType::fwd);
					Vision.takeSnapshot(Green);
				}
				else if (Vision.largestObject.centerX > 210 && Sonar.distance(vex::distanceUnits::cm)>10 ) {
					Brain.Screen.print("Right                       .");
					//strafe right
					LB.spin(vex::directionType::fwd);
					LF.spin(vex::directionType::rev);
					RB.spin(vex::directionType::fwd);
					RF.spin(vex::directionType::rev);
				}
				else if (Vision.largestObject.centerX < 210 && Vision.largestObject.centerX > 105 && Sonar.distance(vex::distanceUnits::cm)>10 ) {
					Brain.Screen.print("Forward                       .");
					//go forward
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
					Controller1.Screen.print ("Alignment done");
				}
			}
		}
		//Autoalign purple
		else if (Controller1.ButtonLeft.pressing()) {
			Vision.takeSnapshot(Purple);
			Controller1.Screen.print ("Purple");
			if(Vision.objectCount > 0) {
				LF.setVelocity(50,vex::velocityUnits::pct);
				RF.setVelocity(50,vex::velocityUnits::pct);
				LB.setVelocity(50,vex::velocityUnits::pct);
				RB.setVelocity(50,vex::velocityUnits::pct);
				Brain.Screen.setCursor(2,1);
				//bot movment code
				if(Vision.largestObject.centerX < 105  && Sonar.distance(vex::distanceUnits::cm)>10 ) {
					//strafe left
					Brain.Screen.print("Left                       .");
					LB.spin(vex::directionType::rev);
					LF.spin(vex::directionType::fwd);
					RB.spin(vex::directionType::rev);
					RF.spin(vex::directionType::fwd);
					Vision.takeSnapshot(Purple);
				}
				else if (Vision.largestObject.centerX > 210 && Sonar.distance(vex::distanceUnits::cm)>10 ) {
					Brain.Screen.print("Right                       .");
					//strafe right
					LB.spin(vex::directionType::fwd);
					LF.spin(vex::directionType::rev);
					RB.spin(vex::directionType::fwd);
					RF.spin(vex::directionType::rev);
				}
				else if (Vision.largestObject.centerX < 210 && Vision.largestObject.centerX > 105 && Sonar.distance(vex::distanceUnits::cm)>10 ) {
					Brain.Screen.print("Forward                       .");
					//go forward
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
					Controller1.Screen.print ("Alignment done");
				}
			}
		}
    //tank drive mode|Y button is the toggle
    else if(ToggleState==true){
      if(OH==false){
        Controller1.Screen.print ("Tank Drive                           .");
      }
      Brain.Screen.setCursor(2, 0);
      Brain.Screen.print ("Tank Drive ");
      LF.spin(vex::directionType::fwd, Controller1.Axis3.value() + Controller1.Axis4.value(),vex::velocityUnits::pct);
			LB.spin(vex::directionType::fwd, Controller1.Axis3.value() - Controller1.Axis4.value(),vex::velocityUnits::pct);
			RF.spin(vex::directionType::fwd, -Controller1.Axis2.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
			RB.spin(vex::directionType::fwd, -Controller1.Axis2.value() - Controller1.Axis1.value(),vex::velocityUnits::pct);
      
    }
    //arcade drive mode|Y button is the toggle
		else if(ToggleState==false){
      if(OH==false){
        Controller1.Screen.print ("Arcade Drive  ");
      }
      Brain.Screen.setCursor(2, 0);
      Brain.Screen.print ("Arcade Drive  ");
			LF.spin(vex::directionType::fwd, Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
			RF.spin(vex::directionType::fwd, -Controller1.Axis3.value() + Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
			RB.spin(vex::directionType::fwd, -Controller1.Axis3.value() - Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
			LB.spin(vex::directionType::fwd, Controller1.Axis3.value() - Controller1.Axis4.value() + Controller1.Axis1.value(),vex::velocityUnits::pct);
		}
    //for power saving
		sleep(20);
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
やきとり, chicken;;*/
//evrything under this point dont worry about it|it's nessasary for the compition
int main() {
	pre_auton();
	Competition.autonomous( autonomous );
	Competition.drivercontrol( usercontrol );
	while(1) {
		vex::task::sleep(100);
	}
}