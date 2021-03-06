#include "main.h"
#include "autos.h"
#include "controller.h"
#include "io_control.h"
#include "chassis.h"
#include "chainbar.h"
#include "lift.h"
#include "mogo.h"
#include "goliath.h"
#include "math.h"


void autoRunRight5ConeMogo() {

  float b = pid_chassis_theta.target_buffer;
  pid_chassis_theta.target_buffer = 3.f;

  chassisResetSensors();

  // move to mogo
  chassisMove(56.81f, 56.81f, true, true);

  // intake mogo
  mogoGoto(MOGO_ANGLE_EXTENDED, true, false);
  delay(250);

  // stack (?) preload
  goliathDischarge(true);

  if (auto_cone) {

    // switch goliath back to intake mode
    goliath_timeout = -1;
    goliathIntake(false);

    // move backwards a bit
    chassisMove(-8.f, -8.f, true, false);

    // start moving forwards slowly
    chassis_mode = CHASSIS_MODE_DIRECT;
    chassisSetPower(15);

    // lower chainbar for second cone
    chainbarGoto(CHAINBAR_GRAB, true, false);

    // move forwards until holding second cone
    chassis_mode = CHASSIS_MODE_DIRECT;
    chassisSetPower(40);

    // wait for cone intake
    while (!goliath_holding && time < 7500) {
      delay(1);
    }

    // stop chassis
    chassisSetPower(0);
    chassisMove(10.f, 10.f, false, false);
    chassis_mode = CHASSIS_MODE_POSITION;

    // stack second cone
    chainbarGoto(CHAINBAR_STACK, true, false);
    goliathDischarge(true);

    goliathIntake(false);

    // lower chainbar for third cone
    chainbarGoto(CHAINBAR_GRAB, true, false);

    // move forwards until holding third cone
    chassis_mode = CHASSIS_MODE_DIRECT;
    chassisSetPower(30);

    // wait for cone intake
    while (!goliath_holding && time < 7500) {
      delay(1);
    }

    // stop chassis
    chassisSetPower(0);
    chassisMove(0, 0, false, false);
    chassis_mode = CHASSIS_MODE_POSITION;

    // start moving back
    chassisMove(-chassis_left / CHASSIS_SCALE_DISTANCE + 2.f, -chassis_right / CHASSIS_SCALE_DISTANCE + 2.f, false, false);

    // stack cone
    pid_lift_enabled = false;
    liftSetPower(100);
    while (lift_height < 9.5f) {
      delay(1);
    }
    liftSetPower(0);

    // stack third cone
    chainbarGoto(CHAINBAR_STACK, true, false);
    liftSetPower(-100);
    delay(400);
    liftSetPower(0);
    goliathDischarge(false);
    liftSetPower(100);
    while (lift_height < 12.f) {
      delay(1);
    }
    liftSetPower(0);
  }

  // make sure mogo is lifted all the way
  pid_mogo_enabled = false;
  mogoSetPower(100);
  delay(250);
  mogoSetPower(0);
  pid_mogo_enabled = true;

  // move chainbar way back
  chainbarGoto(CHAINBAR_RETRACTED, false, false);

  // shut down goliath
  goliathDisable();

  // move back to line
  chassisMove(-chassis_left / CHASSIS_SCALE_DISTANCE + 4.f, -chassis_right / CHASSIS_SCALE_DISTANCE + 4.f, true, true);

  // rotate to 5 zone
  chassisRotate(-200.f, true, true);

  chassisMove(8.f, 8.f, false, false);

  // drop mogo
  mogoGoto(MOGO_ANGLE_GRAB, true, false);

  delay(min(500, 14675 - time));

  mogoGoto(MOGO_ANGLE_RETRACTED, false, false);

  // move out of zones
  chassisMove(-12.f, -12.f, true, false);

  mogoGoto(MOGO_ANGLE_GRAB, false, false);

  pid_chassis_theta.target_buffer = b;
}
