void setTime(int busID, int dayMonthValue, int yearValue, int timeValue)
{
  setBusID(busID);
  
  //dayMonth.clear();
  setDigit(dayMonth, 0, busID, 0, dayMonthValue, false);
  setDigit(dayMonth, 0, busID, 1, dayMonthValue, true);//draw dot
  dayMonth.drawColon(false);
  setDigit(dayMonth, 0, busID, 2, dayMonthValue, false);
  setDigit(dayMonth, 0, busID, 3, dayMonthValue, false);
  dayMonth.writeDisplay();
  delay(10);
  if (debug)
    Serial.print(" ");
  
  //year.clear();
  setDigit(year, 1, busID, 0, yearValue, false);
  setDigit(year, 1, busID, 1, yearValue, false);
  year.drawColon(false);
  setDigit(year, 1, busID, 2, yearValue, false);
  setDigit(year, 1, busID, 3, yearValue, false);
  year.writeDisplay();
  delay(10);
  if (debug)
    Serial.print(" ");
  
  //time.clear();
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
      edit_pointer=0;
      if (debug)
      {
        Serial.print("bus ");
        Serial.println(current_edit_bus);
      }
    }
    else if (inputString=="B" && current_edit_bus!=PRESENT_BUS)
    {
      current_edit_bus=PRESENT_BUS;//activate bus B edit mode
      edit_pointer=0;
      if (debug)
      {
        Serial.print("bus ");
        Serial.println(current_edit_bus);
      }
    }
    else if (inputString=="C" && current_edit_bus!=LAST_TIME_DEPARTED_BUS)
    {
      current_edit_bus=LAST_TIME_DEPARTED_BUS;//activate bus C edit mode
      edit_pointer=0;
      if (debug)
      {
        Serial.print("bus ");
        Serial.println(current_edit_bus);
      }
    }
    else if (inputString=="D")
    {
      current_edit_bus=-1;//do something in the future?, for now just deactivate edit mode
      edit_pointer=0;
      if (debug)
        Serial.println("reset");
    }
    else if (inputString=="*" && edit_pointer>0 && edit_pointer!=-1)
    {
      edit_pointer--;
      if (debug)
        Serial.println("left");
    }
    else if (inputString=="#" && edit_pointer<11 && edit_pointer!=-1)
    {
      edit_pointer++;
      if (debug)
        Serial.println("right");
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
                  initialPresentDate->hour = initialPresentDate->hour-floor(initialPresentDate->hour/10)*10+(value*10);
                case (1):
                  initialPresentDate->hour = initialPresentDate->hour-floor(initialPresentDate->hour%10)+value;
                case (2):
                  initialPresentDate->minute = initialPresentDate->minute-floor(initialPresentDate->minute/10)*10+(value*10);//-initialPresentDate->getElapsedMinutes();
                case (3):
                  initialPresentDate->minute = initialPresentDate->minute-floor(initialPresentDate->minute%10)+value;
              };
              inputString.toInt();
          };
          inputString.toInt();
        case (LAST_TIME_DEPARTED_BUS):
          inputString.toInt();
      };
  
      edit_pointer++;
      
      if (edit_pointer>11)
      {
         //End of display. exit edit mode
         edit_pointer=-1;
         current_edit_bus=-1;
         if (debug)
           Serial.println("exit edit mode");
      } 
      
      if (debug)
      {
        Serial.print("number: ");
        Serial.println(inputString);
      }
    }
    else if ((inputString=="A" && current_edit_bus==DESTINATION_BUS) || (inputString=="B" && current_edit_bus==PRESENT_BUS) || (inputString=="C" && current_edit_bus==LAST_TIME_DEPARTED_BUS))
    {
      current_edit_bus=-1;//deactivate edit mode
      edit_pointer=0;
      if (debug)
        Serial.println("reset");
    }
}

uint8_t intRead(int number, int positionToRead)
{
  return (uint8_t)((uint16_t)(floor(number/pow(10,positionToRead)))%10);
}

void setDigit(Adafruit_7segment& module, int moduleID, int busID, int indexFromLeft, int value, bool drawDot)
{
  uint8_t address = indexFromLeft;
  if (indexFromLeft>=2)
    address++;
    
  uint8_t value_to_show = intRead(value, 3-indexFromLeft);
    
  //Serial.println(value_to_show);
  int selected_module_index = floor(edit_pointer/4);
  if (current_edit_bus==busID && indexFromLeft==edit_pointer%4 && selected_module_index==moduleID)
  {
    // Edit mode, visualize by blinking
    if (millis()%500>250)
    {
        module.writeDigitNum(address, value_to_show, drawDot);
        if (debug)
        {
          Serial.print(value_to_show);
        }
    }
    else
    {
        if (debug)
        {
          Serial.print(" ");
        }
    }
  }
  else
  {
    module.writeDigitNum(address, value_to_show, drawDot);
    if (debug)
    {
      Serial.print(value_to_show);
    }
  }
  
  if (debug && drawDot)
  {
      Serial.print(".");
  }
}

