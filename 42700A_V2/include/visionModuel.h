#include "robot-config.h"
#include "Vision.h"
int Visionloop;
//defult zones: left 105; right 210
void visionAuto(int Color, int distanceTostop, int speedVision, int leftzone, int rightzone) {
  Visionloop = true;
  while(Visionloop == true){
  Vision.takeSnapshot(Color);
  if (Vision.objectCount > 0) {
    LF.setVelocity(speedVision, vex::velocityUnits::pct);
    RF.setVelocity(speedVision, vex::velocityUnits::pct);
    LB.setVelocity(speedVision, vex::velocityUnits::pct);
    RB.setVelocity(speedVision, vex::velocityUnits::pct);
    // bot movment code
    if (Vision.largestObject.centerX < leftzone && Sonar.distance(vex::distanceUnits::cm) > distanceTostop) {
      // strafe left
      Brain.Screen.print("Left                       .");
      LB.spin(vex::directionType::rev);
      LF.spin(vex::directionType::fwd);
      RB.spin(vex::directionType::rev);
      RF.spin(vex::directionType::fwd);
      Vision.takeSnapshot(Color);
    } else if (Vision.largestObject.centerX > rightzone && Sonar.distance(vex::distanceUnits::cm) > distanceTostop) {
      Brain.Screen.print("Right                       .");
      // strafe right
      LB.spin(vex::directionType::fwd);
      LF.spin(vex::directionType::rev);
      RB.spin(vex::directionType::fwd);
      RF.spin(vex::directionType::rev);
    } else if (Vision.largestObject.centerX < rightzone && Vision.largestObject.centerX > leftzone && Sonar.distance(vex::distanceUnits::cm) > distanceTostop) {
      Brain.Screen.print("Forward                       .");
      // go forward
      LB.spin(vex::directionType::fwd);
      LF.spin(vex::directionType::fwd);
      RB.spin(vex::directionType::rev);
      RF.spin(vex::directionType::rev);
    } else if (Sonar.distance(vex::distanceUnits::cm) < distanceTostop) {
      LF.stop();
      RF.stop();
      LB.stop();
      RB.stop();
      Controller1.Screen.print("Alignment done");
      Visionloop = false;
    }
  }
  }
}

void visionDriver(int Color, int distanceTostop, int speedVision, int leftzone, int rightzone) {
  Vision.takeSnapshot(Color);
  if (Vision.objectCount > 0) {
    LF.setVelocity(speedVision, vex::velocityUnits::pct);
    RF.setVelocity(speedVision, vex::velocityUnits::pct);
    LB.setVelocity(speedVision, vex::velocityUnits::pct);
    RB.setVelocity(speedVision, vex::velocityUnits::pct);
    // bot movment code
    if (Vision.largestObject.centerX < leftzone && Sonar.distance(vex::distanceUnits::cm) > distanceTostop) {
      // strafe left
      Brain.Screen.print("Left                       .");
      LB.spin(vex::directionType::rev);
      LF.spin(vex::directionType::fwd);
      RB.spin(vex::directionType::rev);
      RF.spin(vex::directionType::fwd);
      Vision.takeSnapshot(Color);
    } else if (Vision.largestObject.centerX > rightzone && Sonar.distance(vex::distanceUnits::cm) > distanceTostop) {
      Brain.Screen.print("Right                       .");
      // strafe right
      LB.spin(vex::directionType::fwd);
      LF.spin(vex::directionType::rev);
      RB.spin(vex::directionType::fwd);
      RF.spin(vex::directionType::rev);
    } else if (Vision.largestObject.centerX < rightzone && Vision.largestObject.centerX > leftzone && Sonar.distance(vex::distanceUnits::cm) > distanceTostop) {
      Brain.Screen.print("Forward                       .");
      // go forward
      LB.spin(vex::directionType::fwd);
      LF.spin(vex::directionType::fwd);
      RB.spin(vex::directionType::rev);
      RF.spin(vex::directionType::rev);
    } else if (Sonar.distance(vex::distanceUnits::cm) < distanceTostop) {
      LF.stop();
      RF.stop();
      LB.stop();
      RB.stop();
      Controller1.Screen.print("Alignment done");
    }
  }
}