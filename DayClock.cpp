/** DayClock v.8 - Written 2020.04.01 by K.C. Budd 
 *              Phreakmonkey Enterprises
 *              https://www.thingiverse.com/
 * 
 * Because during the COVID-19 Global Pandemic, it's hard to remember what day it is.
 * 
 * Requres: NTPtimeESP library (https://github.com/SensorsIot/NTPtimeESP)
 **/

#include <Arduino.h>
#include <Servo.h>
#include <NTPtimeESP.h>

NTPtime NTPpool("0.us.pool.ntp.org");   // Choose server pool as required
const char *ssid       = "SSID";        // Set you WiFi SSID
const char *password   = "PASSWORD";    // Set you WiFi password
const float UTC_OFFSET = -8.0;          // TZ Offset in X.Y decimal hours.  (e.g -5.0 US EST, -8.0 US PST)
const int DST          = 2;             // 0 = None, 1 = European Summer Time, 2 = USA DST
const int ServoPin     = D6;            // Which Arduino pin is the servo connected to?

// Servo degree positons
// Adjust as needed:  Sun  Mon  Tue  Wed  Thu  Fri  Sat
const int day[7] =   {160, 133, 110,  87,  67,  44,  20};

// If your servo turns the "wrong direction" just reverse the order by 
// commenting out the above and using the following instead.
// Adjust as needed:  Sun  Mon  Tue  Wed  Thu  Fri  Sat
//const int day[7] =   { 20,  44,  67,  87, 110, 133, 160};

const int servodelay = 10;  // Servo speed, smaller is faster (default: 10)

// Interval Timer
unsigned long itimer = 0;
unsigned long interval = 21600000;  // Check NTP every six hours

// Rollover Timer
unsigned long rtimer = 0;
unsigned long rollover = 0;

strDateTime dateTime;
Servo myservo;
uint8_t today = 7;


void moveto(uint8_t d) {
  uint8_t idx = d - 1;
  int curpos = myservo.read();
  if (day[idx] > curpos) {
    for (int i=curpos; i < day[idx]; i++) {
      myservo.write(i);
      delay(servodelay);
    }
  } else {
    for (int i=curpos; i > day[idx]; i--) {
      myservo.write(i);
      delay(servodelay);
    }
  }
}

void setup() {
  // Startup Dance:
  myservo.attach(ServoPin);
  for (int i=1; i < 8; i++) {
    moveto(i);
    delay(1500);
  }
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booted");
  Serial.println("Connecting to Wi-Fi");

  WiFi.mode(WIFI_STA);
  WiFi.begin (ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("WiFi connected");
}

void loop() {
  unsigned long currentMillis = millis();

  if (rtimer && (unsigned long)(currentMillis - rtimer) >= rollover) {
    Serial.println("Rollover!");
    today++;
    if (today == 8) today = 1;  // Can't use modulus for 1-7
    moveto(today);
    rtimer = currentMillis;
    rollover = 86400000;
  }

  if ((unsigned long)(currentMillis - itimer) >= interval || !dateTime.valid) {
    dateTime = NTPpool.getNTPtime(UTC_OFFSET, DST);
    if(dateTime.valid) {
      itimer = currentMillis;
      int hremain = 0, minremain = 0, secremain = 0;
      hremain = 23 - dateTime.hour;
      minremain = 59 - dateTime.minute;
      secremain = 60 - dateTime.second;    
      
      if (today != dateTime.dayofWeek) {
        today = dateTime.dayofWeek;  // 1-7 because stupid
        moveto(today);
      }

      // Update rollover counter with more recent sync:
      unsigned long rolloversec = hremain * 3600 + minremain * 60 + secremain;
      rollover = rolloversec * 1000;
      rtimer = millis();

      NTPpool.printDateTime(dateTime);
      Serial.print("Seconds remaining: ");
      Serial.println(rolloversec);
    }
  }
}
