#include "controller.h"
#include "io_control.h"
#include "driver_control.h"
#include "pid_control.h"

// update literally everything on the bot
void updateAll() {

  // update joystick inputs
  updateAllJoysticks();

  // update sensor inputs
  updateAllSensors();

  // update motors' data
  updateAllMotorData();

  // run driver control (if in driver control mode)
  if (isEnabled() && !isAutonomous()) updateDriverControl();

  // update PIDs
  updateAllPids();

  // update physical motors
  updateAllMotors();
}

// starts a background task with the controller in it
void startController() {
  taskRunLoop(updateAll, UPDATE_INTERVAL);
}
