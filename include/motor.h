#ifndef MOTORS_H_
#define MOTORS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>

class Motor {

public:

  // motor port
  int port;

  // is the motor reversed?
  bool reversed;

  // motor slew control
  bool slew;
  float slew_rate;

  // default initializer
  // MAKE SURE TO FULLY INITIALIZE WITH <Motor>.init()
  Motor();

  // actually initializes the PID
  void init(int port_, bool reversed_, float angle_);

  // gets the current power output of the motor
  int getPower();

  // gets the current velocity of the motor
  float getVelocity();

  // sets the power of the motor
  void setPower(int p);

  // updates motor varaibles and statistics
  void updateData(float angle, int interval);

  // updates the physical motor
  void updateMotor(int interval);

private:

  // current motor power output
  float power;

  // target motor power output
  int target_power;

  // current motor velocity
  float velocity;

  // previous motor angle
  float prev;

};

#ifdef __cplusplus
}
#endif

#endif
