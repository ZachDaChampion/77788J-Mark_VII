#include "macros.h"
#include "goliath.h"
#include "chainbar.h"
#include "lift.h"
#include "io_control.h"
#include "math.h"
#include "driver_control.h"

void stationaryLoaderUpdate() {
  if (joystick.btn8L || joystick_secondary.btn8L) {
    current_macro = MACRO_STATIONARY_LOADER;
    stationaryLoaderRun();
    current_macro = NONE;
  }
}

void stationaryLoaderRun() {

  float target = 0;

  // disable driver control of affected subsystems
  driver_goliath = false;
  driver_chainbar = false;

  // move 4-bar to drop position
  chainbarGoto(CHAINBAR_GRAB, false, false);

  // wait for user to lower lift around stationary goal
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
  target = lift_height + 3.f;

  // wait for lift to raise above target
  while (lift_height < target) {
    delay(1);
  }

  // retract 4-bar to grab position
  chainbarGoto(CHAINBAR_STACK, false, false);

  // switch goliath back to intake mode
  goliath_holding = false;
  goliath_spinning = false;
  goliathIntake(false);

  // re-enable driver control of affected subsystems
  driver_goliath = true;
  driver_chainbar = true;
}
