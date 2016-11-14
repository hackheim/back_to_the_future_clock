void setTime(int busID, int dayMonthValue, int yearValue, int timeValue)
{
  setBusID(busID);
  
  dayMonth.clear();
  setDigit(dayMonth, 0, busID, 0, dayMonthValue, false);
  setDigit(dayMonth, 0, busID, 1, dayMonthValue, true);//draw dot
  dayMonth.drawColon(false);
  setDigit(dayMonth, 0, busID, 2, dayMonthValue, false);
  setDigit(dayMonth, 0, busID, 3, dayMonthValue, false);
  dayMonth.writeDisplay();
  if (debug)
    Serial.print(" ");
  delay(10);

  year.clear();
  setDigit(year, 1, busID, 0, yearValue, false);
  setDigit(year, 1, busID, 1, yearValue, false);
  year.drawColon(false);
  setDigit(year, 1, busID, 2, yearValue, false);
  setDigit(year, 1, busID, 3, yearValue, false);
  year.writeDisplay();
  if (debug)
    Serial.print(" ");
  delay(10);
  
  time.clear();
  setDigit(time, 2, busID, 0, timeValue, false);
  setDigit(time, 2, busID, 1, timeValue, false);
  if (millis()%1000>500)
  {
      time.drawColon(true);
      if (debug)
        Serial.print(":");
  }
  else
  {
      time.drawColon(false);
      if (debug)
        Serial.print(" ");
  }
  setDigit(time, 2, busID, 2, timeValue, false);
  setDigit(time, 2, busID, 3, timeValue, false);
  time.writeDisplay();
  if (debug)
    Serial.print(" ");
  delay(10);
  
  if (debug)
    Serial.print("\n");
}

void setBusID(int id)
{
  digitalWrite(BUS_SWITCH_0, bitRead(id, 0));
  digitalWrite(BUS_SWITCH_1, bitRead(id, 1));
  digitalWrite(BUS_SWITCH_2, bitRead(id, 2));
  digitalWrite(BUS_SWITCH_3, bitRead(id, 3));
  delay(10);
}


void processCommand()
{
    inputString.replace("\n", "");
    inputString.trim();
    
    if (inputString=="A" && current_edit_bus!=DESTINATION_BUS)
    {
      current_edit_bus=DESTINATION_BUS;//activate bus A edit mode
      Serial.print("bus ");
      Serial.println(current_edit_bus);
    }
    else if (inputString=="B" && current_edit_bus!=PRESENT_BUS)
    {
      current_edit_bus=PRESENT_BUS;//activate bus B edit mode
      Serial.print("bus ");
      Serial.println(current_edit_bus);
    }
    else if (inputString=="C" && current_edit_bus!=LAST_TIME_DEPARTED_BUS)
    {
      current_edit_bus=LAST_TIME_DEPARTED_BUS;//activate bus C edit mode
      Serial.print("bus ");
      Serial.println(current_edit_bus);
    }
    else if (inputString=="D")
    {
      current_edit_bus=-1;//do something in the future?, for now just deactivate edit mode
      edit_pointer=0;
      Serial.println("reset");
    }
    else if (isDigit(inputString.charAt(0)) && current_edit_bus!=-1)
    {
      int value = inputString.toInt();
      int selected_module_index = floor(edit_pointer/4);
      int selected_digit = edit_pointer%4;
      switch (current_edit_bus)
      {
        case (DESTINATION_BUS):
          inputString.toInt();
        case (PRESENT_BUS):
          switch (selected_module_index)
          {
            case (0):
              //dayMonth
              inputString.toInt();
            case (1):
              //year
              inputString.toInt();
            case (2):
              //time
              switch (selected_digit)
              {
                case (0):
                  initialDestinationDate->hour = initialDestinationDate->hour-floor(initialDestinationDate->hour/10)*10+(value*10);
                  Serial.println(initialDestinationDate->hour);
                case (1):
                  initialDestinationDate->hour = initialDestinationDate->hour-floor(initialDestinationDate->hour%10)+value;
                case (2):
                  initialDestinationDate->minute = initialDestinationDate->minute-floor(initialDestinationDate->minute/10)*10+(value*10);
                case (3):
                  initialDestinationDate->minute = initialDestinationDate->minute-floor(initialDestinationDate->minute%10)+value;
              };
              inputString.toInt();
          };
          inputString.toInt();
        case (LAST_TIME_DEPARTED_BUS):
          inputString.toInt();
      };
  
      edit_pointer++;
      Serial.println("number");
    }
    else if ((inputString=="A" && current_edit_bus==DESTINATION_BUS) || (inputString=="B" && current_edit_bus==PRESENT_BUS) || (inputString=="C" && current_edit_bus==LAST_TIME_DEPARTED_BUS))
    {
      current_edit_bus=-1;//deactivate edit mode
      edit_pointer=0;
      Serial.println("reset");
    }
}

int intRead(int number, int positionToRead)
{
  return ((int)floor(number/pow(10,positionToRead)))%10;
}

void setDigit(Adafruit_7segment module, int moduleID, int busID, int indexFromLeft, int value, bool drawDot)
{
  int selected_module_index = floor(edit_pointer/4);
  if (current_edit_bus==busID && indexFromLeft==edit_pointer%4 && selected_module_index==moduleID)
  {
    // Edit mode, visualize by blinking
    if (millis()%500>250)
    {
        module.writeDigitNum(indexFromLeft, intRead(value, 3-indexFromLeft), drawDot);
        if (debug)
          Serial.print(intRead(value, 3-indexFromLeft));
    }
    else
        if (debug)
          Serial.print(" ");
  }
  else
  {
    module.writeDigitNum(indexFromLeft, intRead(value, 3-indexFromLeft), drawDot);
    if (debug)
      Serial.print(intRead(value, 3-indexFromLeft));
  }
  
  if (debug && drawDot)
      Serial.print(".");
}

