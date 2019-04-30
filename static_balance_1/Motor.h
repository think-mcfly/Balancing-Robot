#ifndef MOTOR_H
#define MOTOR_H

#include "PID_vj.h"
#include "StopWatch.h"

class Motor
{
public:
  Motor();

  // this one uses enable pins tide to Vcc so only PWM outputs determin direction and power
  // Config 1
  void begin(uint8_t aFwdPwmPin, uint8_t aBwdPwmPin);

  // this one uses all available settings for PWM and enable
  // Config 2
  void begin(uint8_t aFwdPwmPin, uint8_t aBwdPwmPin, uint8_t aFwdEnablePin, uint8_t aBwdEnablePin);

  // this one uses a single PWM for both, but will only enable one at a time
  // Config 3
  void begin(uint8_t aPwmPin, uint8_t aFwdEnablePin, uint8_t aBwdEnablePin);

  ~Motor();
  
  void SetMotorOutput(PWM_Type aMotorOut);

private:
  enum Configuration{ CONFIG_1, CONFIG_2, CONFIG_3 };
  PWM_Type mFwdPwmValue;
  PWM_Type mBwdPwmValue;
  uint8_t mFwdPwmPin;
  uint8_t mBwdPwmPin;
  uint8_t mFwdEnablePin;
  uint8_t mBwdEnablePin;

  StopWatch mStopWatch;
  
  Configuration mConfig;
};


#endif
