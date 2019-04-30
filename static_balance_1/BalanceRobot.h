#ifndef BALANCE_ROBOT_H
#define BALANCE_ROBOT_H

#include <stdint.h>
#include "static_balance.h"
#include "Encoder_j.h"
#include "Motor.h"
#include "StopWatch.h"

#include "MPU6050_j.h"
#include <Wire.h>

class BalanceRobot
{
public:
  BalanceRobot();
  BalanceRobot( uint8_t aRFWD, uint8_t aRBWD, uint8_t aLFWD, uint8_t aLBWD, 
                uint8_t aRENA, uint8_t aRENB, uint8_t aLENA, uint8_t aLENB );
  ~BalanceRobot();

  void begin( uint8_t aRFWD, uint8_t aRBWD, uint8_t aLFWD, uint8_t aLBWD, 
              uint8_t aRENA, uint8_t aRENB, uint8_t aLENA, uint8_t aLENB );

  void UpdateSensors();
  void UpdateAccel();
  void ExecutePidCorrection();
  void UpdateMotorOutputs();

  struct PidConstants
  {
    K_Type p; 
    K_Type i;
    K_Type d;
  };
private:
  StopWatch mStopWatch;
  Accel_Type mRightTiltAngle, mLeftTiltAngle;
  PWM_Type mRightMotorOut, mLeftMotorOut;
  Accel_Type mRightSetpoint, mLeftSetpoint;
  
  PidConstants mRightK;
  PidConstants mLeftK;
};


#endif
