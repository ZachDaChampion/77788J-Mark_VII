#include "macros.h"
#include "goliath.h"
#include "chainbar.h"
#include "lift.h"
#include "io_control.h"
#include "math.h"
#include "driver_control.h"

void assistedStackerUpdate() {
  if ((joystick.btn8R || joystick_secondary.btn8R) /*&& goliath_holding*/) {
    current_macro = MACRO_ASSISTED_STACKER;
    assistedStackerRun();
    current_macro = NONE;
  }
}

void assistedStackerRun() {

  float target = 0;

  // disable driver control of affected subsystems
  driver_goliath = false;
  driver_chainbar = false;

  // move 4-bar back to stack position
  chainbarGoto(CHAINBAR_STACK, false, false);

  // wait for user to lower lift a bit
  while (!joystick.btn5D && !joystick_secondary.btn5D) {
    delay(1);
  }

  // wait for user to raise lift up
  while (!joystick.btn5U && !joystick_secondary.btn5U) {
    delay(1);
  }

  // spit out cone
  goliathDischarge(false);

  // store target height of lift
  target = lift_height + 4.f;

  // wait for lift to raise above target
  while (lift_height < target) {
  goliathDischarge(false);
    delay(UPDATE_INTERVAL);
  }

  // extend 4-bar to grab position
  chainbarGoto(CHAINBAR_GRAB, false, false);

  // switch goliath back to intake mode
  goliath_holding = false;
  goliath_spinning = false;
  goliathIntake(false);

  // re-enable driver control of affected subsystems
  driver_goliath = true;
  driver_chainbar = true;
}
