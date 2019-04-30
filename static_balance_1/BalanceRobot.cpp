
#include "BalanceRobot.h"

BalanceRobot::BalanceRobot(){}

Encoder mRightEncoder(RENA, RENB); // right encoder A, right encoder B
Encoder mLeftEncoder(LENA, LENB); // left encoder A, left encoder B
MPU6050 mpu6050(Wire);
Motor mRightMotor;
Motor mLeftMotor;

PID mRightPID;
PID mLeftPID;

void BalanceRobot::begin( uint8_t aRFWD, uint8_t aRBWD, uint8_t aLFWD, uint8_t aLBWD, 
                          uint8_t aRENA, uint8_t aRENB, uint8_t aLENA, uint8_t aLENB )
{
  mRightMotor.begin(aRFWD, aRBWD); // right forward, right backward
  mLeftMotor.begin(aLFWD, aLBWD); // left forward, left backward
  mStopWatch.begin();
  
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  mRightK.p=10; mRightK.i=0; mRightK.d=0;
  mLeftK.p=10; mLeftK.i=0; mLeftK.d=0;
  mRightSetpoint = 0;
  mLeftSetpoint = 0;
  mRightPID.begin(&mRightTiltAngle, &mRightMotorOut, &mRightSetpoint, mRightK.p, mRightK.i, mRightK.d, DIRECT);
  mRightPID.SetMode(AUTOMATIC);
  mRightPID.SetOutputLimits(-255, 255);
  mLeftPID.begin(&mLeftTiltAngle, &mLeftMotorOut, &mLeftSetpoint, mLeftK.p, mLeftK.i, mLeftK.d, DIRECT);
  mLeftPID.SetMode(AUTOMATIC);
  mLeftPID.SetOutputLimits(-255, 255);
}

BalanceRobot::~BalanceRobot()
{
  
}

void BalanceRobot::ExecutePidCorrection()
{
  int start = micros();
  mRightPID.Compute();
  mLeftPID.Compute();
//  Serial.print("tilt "); Serial.print(mRightTiltAngle); Serial.print(", Motor "); Serial.print(mRightMotorOut); Serial.println();
  int stop = micros();
  Serial.print("PID Compute Time: "); Serial.print(stop - start); Serial.println("us");
}

void BalanceRobot::UpdateMotorOutputs()
{
  int start = micros();
  // RIGHT MOTOR
  if(mRightMotorOut > 0)
  {
    analogWrite(RFWD, mRightMotorOut);
    analogWrite(RBWD, 0);
  }
  else if(mRightMotorOut < 0)
  {
    analogWrite(RFWD, 0);
    analogWrite(RBWD, -mRightMotorOut);
  }
  else
  {
    analogWrite(RFWD, 0);
    analogWrite(RBWD, 0);
  }

  // LEFT MOTOR
  if(mLeftMotorOut > 0)
  {
    analogWrite(LFWD, mLeftMotorOut);
    analogWrite(LBWD, 0);
  }
  else if(mLeftMotorOut < 0)
  {
    analogWrite(LFWD, 0);
    analogWrite(LBWD, -mLeftMotorOut);
  }
  else
  {
    analogWrite(LFWD, 0);
    analogWrite(LBWD, 0);
  }
  int stop = micros();
  Serial.print("Motor Update Time: "); Serial.print(stop - start); Serial.println("us");
}

void BalanceRobot::UpdateSensors()
{
  int start = micros();
  UpdateAccel();
  int stop = micros();
  Serial.print("Accel Update Time: "); Serial.print(stop - start); Serial.println("us");
}

void BalanceRobot::UpdateAccel()
{
  mpu6050.update();
  mRightTiltAngle = (int)(mpu6050.getAccAngleY() / 180 * 255);
  mLeftTiltAngle = (int)(mpu6050.getAccAngleY() / 180 * 255);
//  mTiltAngle = mpu6050.getAngleY();
  
  Serial.print("\tangleY : ");
  Serial.println(mpu6050.getAccAngleY());
}




