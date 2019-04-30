#ifndef PID_vj_h
#define PID_vj_h
#define LIBRARY_VERSION	1.2.1

#include <stdint.h>
#include "StopWatch.h"


using K_Type = int8_t;
using Accel_Type = int16_t;
using Temp_Type = int16_t;
using PWM_Type = int16_t;


class PID
{


  public:

  //Constants used in some of the functions below
  #define AUTOMATIC	1
  #define MANUAL	0
  #define DIRECT  0
  #define REVERSE  1
  #define P_ON_M 0
  #define P_ON_E 1

  //commonly used functions **************************************************************************
    PID();
    
    void begin(Accel_Type*, PWM_Type*, Accel_Type*,        // * constructor.  links the PID to the Input, Output, and 
        K_Type, K_Type, K_Type, K_Type, int);//   Setpoint.  Initial tuning parameters are also set here.
                                          //   (overload for specifying proportional mode)

    void begin(Accel_Type*, PWM_Type*, Accel_Type*,        // * constructor.  links the PID to the Input, Output, and 
        K_Type, K_Type, K_Type, int);     //   Setpoint.  Initial tuning parameters are also set here
	
    void SetMode(int Mode);               // * sets PID to either Manual (0) or Auto (non-0)

    bool Compute();                       // * performs the PID calculation.  it should be
                                          //   called every time loop() cycles. ON/OFF and
                                          //   calculation frequency can be set using SetMode
                                          //   SetSampleTime respectively

    void SetOutputLimits(PWM_Type, PWM_Type); // * clamps the output to a specific range. 0-255 by default, but
										                      //   it's likely the user will want to change this depending on
										                      //   the application
	


  //available but not commonly used functions ********************************************************
    void SetTunings(K_Type, K_Type,       // * While most users will set the tunings once in the 
                    K_Type);         	    //   constructor, this function gives the user the option
                                          //   of changing tunings during runtime for Adaptive control
    void SetTunings(K_Type, K_Type,       // * overload for specifying proportional mode
                    K_Type, K_Type);         	  

	void SetControllerDirection(int);	  // * Sets the Direction, or "Action" of the controller. DIRECT
										  //   means the output will increase when error is positive. REVERSE
										  //   means the opposite.  it's very unlikely that this will be needed
										  //   once it is set in the constructor.
    void SetSampleTime(int);              // * sets the frequency, in Milliseconds, with which 
                                          //   the PID calculation is performed.  default is 100
										  
										  
										  
  //Display functions ****************************************************************
	K_Type GetKp();						  // These functions query the pid for interal values.
	K_Type GetKi();						  //  they were created mainly for the pid front-end,
	K_Type GetKd();						  // where it's important to know what is actually 
	int GetMode();						  //  inside the PID.
	int GetDirection();					  //

  private:
  StopWatch mStopWatch;
  
	void Initialize();
	
	K_Type dispKp;				// * we'll hold on to the tuning parameters in user-entered 
	K_Type dispKi;				//   format for display purposes
	K_Type dispKd;				//
    
	K_Type kp;                  // * (P)roportional Tuning Parameter
    K_Type ki;                  // * (I)ntegral Tuning Parameter
    K_Type kd;                  // * (D)erivative Tuning Parameter

	int controllerDirection;
	K_Type pOn;

    Accel_Type *myInput;              // * Pointers to the Input, Output, and Setpoint variables
    PWM_Type *myOutput;             //   This creates a hard link between the variables and the 
    Accel_Type *mySetpoint;           //   PID, freeing the user from having to constantly tell us
                                  //   what these values are.  with pointers we'll just know.
			  
	unsigned long lastTime;
	double outputSum, lastInput;

	unsigned long SampleTime;
	double outMin, outMax;
	bool inAuto, pOnE;
};
#endif

