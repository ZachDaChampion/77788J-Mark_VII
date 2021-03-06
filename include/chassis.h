#ifndef CHASSIS_H_
#define CHASSIS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>
#include <motor.h>
#include <ap_filter.h>
#include <pid.h>

// chassis modes
#define CHASSIS_MODE_DIRECT 0
#define CHASSIS_MODE_POSITION 1
#define CHASSIS_MODE_ANGLE 2

// stores current chassis mode
extern int chassis_mode;

// motor ports
#define MOTOR_CHASSIS_FL 4
#define MOTOR_CHASSIS_BL 2
#define MOTOR_CHASSIS_FR 5
#define MOTOR_CHASSIS_BR 7

// distance scaling factor
#define CHASSIS_SCALE_DISTANCE 26.6962f

// motors
extern Motor motor_chassis_fl;
extern Motor motor_chassis_fr;

// sensor ports
#define LINE_L 3
#define LINE_R 4

// sensors
extern Gyro gyro_a;
extern Gyro gyro_b;
extern Encoder enc_chassis_l;
extern Encoder enc_chassis_r;

// orientation AP filter
extern ApFilterInput input_gyro_a;
extern ApFilterInput input_gyro_b;
extern ApFilterInput input_encoders;
extern ApFilter ap_filter_orientation;

// PIDs
extern Pid pid_chassis_l;
extern Pid pid_chassis_r;
extern Pid pid_chassis_theta;

// sensor values will be stored in these variables
extern float chassis_left;
extern float chassis_right;
extern float chassis_angle;
extern float orientation_ap;
extern bool line_l;
extern bool line_r;

// inits the chassis (PID, encoders, motors, etc)
void chassisInit();

// update all chassis motors
void chassisUpdateMotorData();
void chassisUpdateMotors();

// updates all chassis sensors
void chassisUpdateSensors();

// reset all chassis sensors
void chassisResetSensors();

// determines whether or not the chassis has reached its target
bool chassisAtTarget(bool vel, int mode);

// returns a recommended timeout for a position PID
unsigned int chassisGetTimeoutPosition(float l, float r);

// returns a recommended timeout for a rotation PID
unsigned int chassisGetTimeoutAngle(float theta);

// low-level chassis control
void chassisSetPowerL(int power);
void chassisSetPowerR(int power);

// mid-level chassis control
void chassisSetPower(int power);
void chassisSetPowerExt(int l, int r);
void chassisSetPowerAccel(int l, int r);

// high level chassis control
void chassisMove(float l, float r, bool wait, bool vel);
void chassisRotate(float theta, bool wait, bool vel);

#ifdef __cplusplus
}
#endif

#endif
