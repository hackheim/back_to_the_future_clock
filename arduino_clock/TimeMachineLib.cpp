#include "Arduino.h"
#include "TimeMachineLib.h"


DateTime::DateTime(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minute)
{
  this->year = year;
  this->month = month;
  this->day = day;
  this->hour = hour;
  this->minute = minute;
}
unsigned long DateTime::getCurrentTotalSeconds()
{
    return (hour*3600ul)+(minute*60ul);//+(millis()/1000ul);
}

unsigned int DateTime::getCurrentMins()
{
    return (getCurrentTotalSeconds()/60)%60;
}

unsigned int DateTime::getCurrentHours()
{
    return (getCurrentTotalSeconds()/3600)%24;
}

unsigned int DateTime::getCurrentTimeAsInt()
{
  return getCurrentMins()+(getCurrentHours()*100); // 23:59 => 2359
}

unsigned int DateTime::getDateAsInt()
{
  return day*100+month; // 24/12 -> 2412
}

int DateTime::getElapsedMinutes()
{
    return (getCurrentTotalSeconds()/60)%60;
}

