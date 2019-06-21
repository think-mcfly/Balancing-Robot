/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include "PID_vj.h"
#include "static_balance.h"
#include "BalanceRobot.h"
#include "StopWatch.h"

#define PIN_INPUT 0
#define PIN_OUTPUT 3


//Define Variables we'll be connecting to

BalanceRobot gRobot;

void setup()
{
  Serial.begin(9600);


  gRobot.begin( RFWD, RBWD, LFWD, LBWD, RENA, RENB, LENA, LENB );
}

void loop()
{
  int start = micros();
  gRobot.UpdateSensors();
  gRobot.ExecutePidCorrection();
  gRobot.UpdateMotorOutputs();
  int stop = micros();
  Serial.print("Loop Run Time: "); Serial.print(stop - start); Serial.println("us");
  
}


