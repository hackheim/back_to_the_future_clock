# Back to the future clock

## Partlist
- 2x Arduino Nano
- 9x Adafruit 0.56" 4-Digit 7-Segment Display w/I2C Backpack https://www.adafruit.com/product/881
- 1x CD74HC4067 16-Channel Multiplexer
- 3mm plywood

## Setup software
- Install Arduino IDE https://www.arduino.cc/en/Main/Software
- Install CH340G drivers http://www.wch.cn/download/CH341SER_EXE.html
- Download this repository. Click the green "Clone or download" button to do this.
- In the Arduino IDE: Install this library by selecting Sketch > Include Library > Add .ZIP library and navigate to the file you just downloaded
- Download the two following libraries and install it in Arduino IDE by selecting Sketch > Include Library > Add .ZIP Library
  - https://github.com/adafruit/Adafruit_LED_Backpack
  - https://github.com/adafruit/Adafruit-GFX-Library
- Open the arduino_keypad/arduino_keypad.ino file in the Arduino IDE and check that every thing is ok by clicking the verify button. (no red errors)
- Connect the arduino to the computer
- Configure the board and port by selecting Tools > Board > Arduino Nano, and Tools > Port > /dev/cu.wchusbserial1450. (or on windows, select the correct COM port)
- Upload code to the arduino by clicking the upload button

## To change date and time

Change these lines and upload the code
```
   initialDestinationDate = new DateTime(1984, 8, 12, 23, 7);
   initialPresentDate = new DateTime(2017, 4, 10, 9, 36);
   initialLastTimeDepartedDate = new DateTime(2016, 4, 29, 21, 6);
```

## Licenses
- This project itself is licensed MIT, see LICENSE file for details
- Adafruit_LED_Backpack (MIT) https://github.com/adafruit/Adafruit_LED_Backpack
- Adafruit-GFX-Library (BSD License) https://github.com/adafruit/Adafruit-GFX-Library
