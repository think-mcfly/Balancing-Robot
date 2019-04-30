#ifndef STOP_WATCH_H
#define STOP_WATCH_H

#include <Arduino.h>

class StopWatch
{
  public:
  enum TimerType
  {
    millisec,
    microsec
  };
  enum TimeUnits
  {
    microseconds,
    milliseconds,
    seconds,
    minutes,
    hours,
    days,
    weeks,
    months,
    years
  };
  private:
  TimerType mType;
  bool mStopWatchInProgress;
  unsigned long mStartTime, mStopTime, mWatchTime;
  
  public:
  StopWatch();
  ~StopWatch();
  void begin();

  void start(TimerType aType);
  unsigned long stop();
  unsigned long getLastStartTime(TimeUnits aUnits);
  unsigned long getLastStopTime(TimeUnits aUnits);
  unsigned long getTime(TimeUnits aUnits);
  
};



#endif
