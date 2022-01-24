using namespace vex;

extern brain Brain;
extern controller Controller;

extern motor frontLeft;
extern motor midLeft;
extern motor rearLeft;
extern motor frontRight;
extern motor midRight;
extern motor rearRight;

extern motor claw;
extern motor lift;

extern motor_group leftDrive;
extern motor_group rightDrive;

extern inertial imu;

extern digital_in rearLimit;

extern digital_out sauron;
extern digital_out rearClaw;

extern digital_in frontLimit;
extern digital_in backLimit;

extern pot potGAuto;
extern pot liftLevel;
extern pot clawLevel;

extern color autoncolor;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
