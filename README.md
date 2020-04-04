## DayClock
### What day is it?!?!

![DayClock.gif](https://github.com/phreakmonkey/DayClock/blob/master/artifacts/DayClock.gif?raw=true)

A simple "clock" to tell you what day it is.  It utilizes the NTPtimeESP library (https://github.com/SensorsIot/NTPtimeESP) to determine the day of the week.

Parts list:
  - Wemos D1 (or suitable ESP8266 dev board)
  - "9g" Micro Servo (standard 12mm x 23mm)
  - 3D printed STL files in this repo

Connect the servo to the Wemos D1 as shown:

![DayClock-servo.png](https://github.com/phreakmonkey/DayClock/blob/master/artifacts/DayClock-servo.png?raw=true)

Edit DayClock.cpp to set your WiFi SSID, Password, and timezone (UTC_OFFSET)

Voila!
