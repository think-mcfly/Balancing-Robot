// created 11-28-2018
// Joshua Mueller
//////////////////////
//StopWatch
////////////////////
#include "StopWatch.h"

  StopWatch::StopWatch(){}
  StopWatch::~StopWatch(){}
  void StopWatch::begin(){}

  void StopWatch::start(TimerType aType)
  {
    mType = aType;
    switch(mType)
    {
      case millisec:
      mStartTime = millis();
      break;
      case microsec:
      mStartTime = micros();
      break;
      default:
      Serial.println("ERROR: No timer type has been selected");
      break;
    }
  }
  unsigned long StopWatch::stop()
  {
    switch(mType)
    {
      case millisec:
      mStopTime = millis();
      break;
      case microsec:
      mStopTime = micros();
      break;
      default:
      Serial.println("ERROR: No timer type has been selected");
      return 0;
      break;
    }
    mWatchTime = mStopTime - mStartTime;
    return mWatchTime;
  }
  unsigned long StopWatch::getLastStartTime(TimeUnits aUnits)
  {
    return mStartTime;
  }
  unsigned long StopWatch::getLastStopTime(TimeUnits aUnits)
  {
    return mStopTime;
  }
  unsigned long StopWatch::getTime(TimeUnits aUnits)
  {
    double time = mWatchTime;
    if(mStopWatchInProgress)
    {
      Serial.println("ERROR: Stop watch is still running!!!");
      return 0;
    }
    switch(aUnits)
    {
      case microseconds:
        if(mType != microsec)
        {
          time *= 1000;
        }
      break;
      case milliseconds:
        if(mType != millisec)
        {
          time /= 1000;
        }
      break;
      case seconds:
        time /= 1000;
        if(mType == millisec)
        {
          time /= 1000;
        }
      break;
      case minutes:
        time /= 1000/60;
        if(mType == millisec)
        {
          time /= 1000;
        }
      break;
      case hours:
        time /= 1000/60/60;
        if(mType == millisec)
        {
          time /= 1000;
        }
      break;
      case days:
        time /= 1000/60/60/24;
        if(mType == millisec)
        {
          time /= 1000;
        }
      break;
      case weeks:
        time /= 1000/60/60/24/7;
        if(mType == millisec)
        {
          time /= 1000;
        }
      break;
      case months:
        time /= 1000/60/60/24/30;
        if(mType == millisec)
        {
          time /= 1000;
        }
      break;
      case years:
        time /= 1000/60/60/24/365;
        if(mType == millisec)
        {
          time /= 1000;
        }
      break;
    }
    return time;
  }

