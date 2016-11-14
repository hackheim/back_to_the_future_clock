#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class DateTime {
  public:
    DateTime(unsigned int year, unsigned int month, unsigned int day, unsigned int hour, unsigned int minute);
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int hour;
    unsigned int minute;
    unsigned long getCurrentTotalSeconds();
    unsigned int getCurrentMins();
    unsigned int getCurrentHours();
    unsigned int getCurrentTimeAsInt();
    unsigned int getDateAsInt();
};
#endif

