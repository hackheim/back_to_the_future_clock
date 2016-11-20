# Back to the future clock

## Partlist
- 2x Arduino Nano
...

## Setup software
- Install Arduino IDE https://www.arduino.cc/en/Main/Software
- Install CH340G drivers http://www.wch.cn/download/CH341SER_EXE.html
- Download and unzip this repository. Click the green "Clone or download" button to do this.
- Download the two following libraries and install it in Arduino IDE by selecting Sketch > Include Library > Add .ZIP Library
  - https://github.com/adafruit/Adafruit_LED_Backpack
  - https://github.com/adafruit/Adafruit-GFX-Library
- Open the arduino_keypad/arduino_keypad.ino file in the Arduino IDE and check that every thing is ok by clicking the verify button. (no red errors)
- Connect the arduino to the computer
- Configure the board and port by selecting Tools > Board > Arduino Nano, and Tools > Port > /dev/cu.wchusbserial1450. (or on windows, select the correct COM port)
- Upload code to the arduino by clicking the upload button
