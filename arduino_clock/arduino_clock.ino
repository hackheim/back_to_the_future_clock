#include <Wire.h> // included, docs https://www.arduino.cc/en/Reference/Wire
#include <Adafruit_LEDBackpack.h> // https://github.com/adafruit/Adafruit_LED_Backpack
#include <Adafruit_GFX.h> // https://github.com/adafruit/Adafruit-GFX-Library
#include "TimeMachineLib.h"

// 9x backpack modules, configured like this //https://learn.adafruit.com/adafruit-led-backpack/0-dot-56-seven-segment-backpack
// format: dayMonthModule: [DD.MM] yearModule: [YYYY] timeModule: [hh:mm]
// in three rows
// [dayMonthModule] [yearModule] [timeModule] (DESTINATION_BUS, bus 0)
// [dayMonthModule] [yearModule] [timeModule] (PRESENT_BUS, bus 1)
// [dayMonthModule] [yearModule] [timeModule] (LAST_TIME_DEPARTED_BUS, bus 2)

bool debug = false;//outputs datetime as serial

// Pins
int const BUS_SWITCH_0 = 9;
int const BUS_SWITCH_1 = 10;
int const BUS_SWITCH_2 = 11;
int const BUS_SWITCH_3 = 12;

// Bus definations
int const DESTINATION_BUS = 2;
int const PRESENT_BUS = 0;
int const LAST_TIME_DEPARTED_BUS = 1;

Adafruit_7segment dayMonth = Adafruit_7segment();
Adafruit_7segment year = Adafruit_7segment();
Adafruit_7segment time = Adafruit_7segment();

DateTime *initialDestinationDate;
DateTime *initialPresentDate;
DateTime *initialLastTimeDepartedDate;
String inputString = "";
boolean stringComplete = false;
int current_edit_bus=-1;
int edit_pointer=0;

// i2c signal is located at A4 (SDA) and A5 (SCL) on arduino nano

void setup()
{
  Serial.begin(9600);
  inputString.reserve(100);
  
  pinMode(BUS_SWITCH_0, OUTPUT);
  pinMode(BUS_SWITCH_1, OUTPUT);
  pinMode(BUS_SWITCH_2, OUTPUT);
  pinMode(BUS_SWITCH_3, OUTPUT);
  
  Wire.begin();
  for(int i = 0; i < 3; i++) 
  {
    setBusID(i);  
    dayMonth.begin(0x70);
    year.begin(0x71);
    time.begin(0x72);
  }
  
  initialDestinationDate = new DateTime(1984, 8, 12, 23, 7);
  initialPresentDate = new DateTime(2017, 4, 10, 9, 36);
  initialLastTimeDepartedDate = new DateTime(2016, 4, 29, 21, 6);
}

void loop()
{
  setTime(DESTINATION_BUS, initialDestinationDate->getDateAsInt(), initialDestinationDate->year, initialDestinationDate->getCurrentTimeAsInt());
  setTime(PRESENT_BUS, initialPresentDate->getDateAsInt(), initialPresentDate->year, initialPresentDate->getCurrentTimeAsInt());
  setTime(LAST_TIME_DEPARTED_BUS, initialLastTimeDepartedDate->getDateAsInt(), initialLastTimeDepartedDate->year, initialLastTimeDepartedDate->getCurrentTimeAsInt());
  

  if (stringComplete) {
    processCommand();
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}


