## DayClock
### What day is it?!?!

![DayClock.gif](https://github.com/phreakmonkey/DayClock/blob/master/artifacts/DayClock.gif?raw=true)

A simple "clock" to tell you what day it is.  It utilizes the NTPtimeESP library (https://github.com/SensorsIot/NTPtimeESP) to determine the day of the week.

Parts list:
  - Wemos D1 Mini (or suitable ESP8266 dev board)
  - "9g" Micro Servo (standard 12mm x 23mm)
  - 3D printed STL files in this repo. (STL models are in millimeters)

Connect the servo to the Wemos D1 as shown:

![DayClock-servo.png](https://github.com/phreakmonkey/DayClock/blob/master/artifacts/DayClock-servo.png?raw=true)

Edit DayClock.cpp to set your WiFi SSID, Password, and timezone (UTC_OFFSET)
Compile & upload to the ESP8266.  (Personally, I use PlatformIO.  YMMV with the Arduino IDE.)

When the unit first powers on it will cycle the servo to each of the 7 "day" positions.  Make a note of any that you want to adjust and increase/decrease the "degrees" in the source file appropriately.

The program will output some diagnostic info (Wifi connection status, current time & date when it syns with NTP, &etc) via the USB serial port at 115200 baud.

Have fun!
