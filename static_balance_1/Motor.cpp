
#include "Motor.h"
#include <Arduino.h>

Motor::Motor(){}
void Motor::begin(uint8_t aFwdPwmPin, uint8_t aBwdPwmPin)
{
  mConfig = CONFIG_1;
  mFwdPwmPin = aFwdPwmPin;
  mBwdPwmPin = aBwdPwmPin;
  mFwdEnablePin = 99;
  mBwdEnablePin = 99;
  mFwdPwmValue = 0;
  mBwdPwmValue = 0;
  pinMode(mFwdPwmPin, OUTPUT);
  pinMode(mBwdPwmPin, OUTPUT);
  mStopWatch.begin();
}

void Motor::begin(uint8_t aFwdPwmPin, uint8_t aBwdPwmPin, uint8_t aFwdEnablePin, uint8_t aBwdEnablePin)
{
  mConfig = CONFIG_2;
  mFwdPwmPin = aFwdPwmPin;
  mBwdPwmPin = aBwdPwmPin;
  mFwdEnablePin = aFwdEnablePin;
  mBwdEnablePin = aBwdEnablePin;
  mFwdPwmValue = 0;
  mBwdPwmValue = 0;

  pinMode(mFwdPwmPin, OUTPUT);
  pinMode(mBwdPwmPin, OUTPUT);
  pinMode(mFwdEnablePin, OUTPUT);
  pinMode(mBwdEnablePin, OUTPUT);
}

void Motor::begin(uint8_t aPwmPin, uint8_t aFwdEnablePin, uint8_t aBwdEnablePin)
{
  mConfig = CONFIG_3;
  mFwdPwmPin = aPwmPin;
  mBwdPwmPin = aPwmPin;
  mFwdEnablePin = aFwdEnablePin;
  mBwdEnablePin = aBwdEnablePin;
  mFwdPwmValue = 0;
  mBwdPwmValue = 0;

  pinMode(mFwdPwmPin, OUTPUT);
  pinMode(mBwdPwmPin, OUTPUT);
  pinMode(mFwdEnablePin, OUTPUT);
  pinMode(mBwdEnablePin, OUTPUT);
}

Motor::~Motor()
{
  
}

void Motor::SetMotorOutput(PWM_Type aMotorOut)
{
  if(aMotorOut > 0)
  {
    mFwdPwmValue = aMotorOut;
    mBwdPwmValue = 0;
    switch(mConfig)
    {
      case CONFIG_1:
      analogWrite(mFwdPwmPin, mFwdPwmValue);
      analogWrite(mBwdPwmPin, mBwdPwmValue);
      break;
      case CONFIG_2:
      digitalWrite(mBwdEnablePin, LOW);
      digitalWrite(mFwdEnablePin, HIGH);
      analogWrite(mFwdPwmPin, mFwdPwmValue);
      analogWrite(mBwdPwmPin, mBwdPwmValue);
      break;
      case CONFIG_3:
      digitalWrite(mBwdEnablePin, HIGH); // only one enable
      analogWrite(mFwdPwmPin, mFwdPwmValue);
      analogWrite(mBwdPwmPin, mBwdPwmValue);
      break;
    }
  }
  else if(aMotorOut < 0)
  {
    mFwdPwmValue = 0;
    mBwdPwmValue = aMotorOut;
    switch(mConfig)
    {
      case CONFIG_1:
      analogWrite(mFwdPwmPin, mFwdPwmValue);
      analogWrite(mBwdPwmPin, mBwdPwmValue);
      break;
      case CONFIG_2:
      digitalWrite(mBwdEnablePin, HIGH);
      digitalWrite(mFwdEnablePin, LOW);
      analogWrite(mFwdPwmPin, mFwdPwmValue);
      analogWrite(mBwdPwmPin, mBwdPwmValue);
      break;
      case CONFIG_3:
      digitalWrite(mBwdEnablePin, HIGH); // only one enable
      analogWrite(mFwdPwmPin, mFwdPwmValue);
      analogWrite(mBwdPwmPin, mBwdPwmValue);
      break;
    }
  }
  else
  {
    mFwdPwmValue = 0;
    mBwdPwmValue = 0;
    switch(mConfig)
    {
      case CONFIG_1:
      analogWrite(mFwdPwmPin, mFwdPwmValue);
      analogWrite(mBwdPwmPin, mBwdPwmValue);
      break;
      case CONFIG_2:
      digitalWrite(mBwdEnablePin, LOW);
      digitalWrite(mFwdEnablePin, LOW);
      analogWrite(mFwdPwmPin, mFwdPwmValue);
      analogWrite(mBwdPwmPin, mBwdPwmValue);
      break;
      case CONFIG_3:
      digitalWrite(mBwdEnablePin, LOW); // only one enable
      analogWrite(mFwdPwmPin, mFwdPwmValue);
      analogWrite(mBwdPwmPin, mBwdPwmValue);
      break;
    }
  }
}




