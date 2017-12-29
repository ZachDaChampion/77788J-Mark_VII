#include "pid_control.h"
#include "chassis.h"
#include "mogo.h"
#include "pid.h"

// run chasis PID
void pidRunChassis() {
  switch (chassis_mode) {

    // if controlling position
    case (CHASSIS_MODE_POSITION): {

      // reset integrals if at target
      if (pid_chassis_l.atTarget(false, chassis_left, 0)) pid_chassis_l.resetIntegral();
      if (pid_chassis_r.atTarget(false, chassis_right, 0)) pid_chassis_r.resetIntegral();

      // run the PID
      chassisSetPowerExt(
        pid_chassis_l.run(chassis_left, UPDATE_INTERVAL),
        pid_chassis_r.run(chassis_right, UPDATE_INTERVAL));

    } break;

    // if controlling orientation
    case (CHASSIS_MODE_ANGLE): {

      // reset the integral if at target
      if (pid_chassis_theta.atTarget(false, chassis_angle, 0)) pid_chassis_theta.resetIntegral();

      // run the PID
      int power = pid_chassis_theta.run(chassis_angle, UPDATE_INTERVAL);
      if (abs(power) < 24) power = 24 * (limit(power, -1, 1));
      chassisSetPowerExt(power, -power);

    } break;
  }
}

// run mogo lifter PID
void pidRunMogo() {

  // calculate PID
  float pid = pid_mogo.run(mogo_angle, UPDATE_INTERVAL);

  // if the mogo lifter is extended or retracted, make its minimum power +/-24
  if (pid_mogo.getTarget() == MOGO_ANGLE_EXTENDED &&
      mogo_angle > MOGO_ANGLE_EXTENDED - 5 &&
      pid < 24)
    mogoSetPower(24);

  else if (pid_mogo.getTarget() == MOGO_ANGLE_RETRACTED &&
           mogo_angle < MOGO_ANGLE_RETRACTED - 5 &&
           pid > -24)
      mogoSetPower(-24);

  else mogoSetPower(pid);
}

// run all PIDs
void updateAllPids() {

  // chassis
  pidRunChassis();

  // mogo lifter
  pidRunMogo();
}
