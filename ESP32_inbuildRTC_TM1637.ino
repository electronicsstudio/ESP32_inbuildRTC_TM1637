/*
Electronics Studio
@file ESP23_inbuiltRTC_TM1637.ino
@date  15-08-2024
@url https:https: https://github.com/electronicsstudio
@url YouTube: https://www.youtube.com/@ElectronicsStudio-v7o/featured
*/

#include <TM1637TinyDisplay6.h>  // TM1637 display
#include <ESP32Time.h>

#define CLK 26
#define DIO 27
TM1637TinyDisplay6 display(CLK, DIO); // 6-Digit Display Class CLK to pin no. 1 and DIO to pin no. 2
ESP32Time rtc(3600);  

void setup() {
  Serial.begin(115200);
  rtc.setTime(0, 41, 11, 17, 1, 2024);  // 17th Jan 2021 15:24:30
      //sec, min, hour, date, month, year
  display.setBrightness(0x0f); // Set brightness of the display (0x00 to 0x0f)
}

void loop() {
  Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));    
  struct tm timeinfo = rtc.getTimeStruct();
  
  //rtc.updateTime(); // Update the time
  displayRTCTimestamp();
  delay(1000);
}

void displayRTCTimestamp() {
  struct tm timeinfo = rtc.getTimeStruct(); // Get the time structure
  
  long hour = timeinfo.tm_hour; // Access hours from timeinfo
  long minute = timeinfo.tm_min; // Access minutes from timeinfo
  long second = timeinfo.tm_sec; // Access seconds from timeinfo
  long dayofweek = timeinfo.tm_wday; // Access day of week from timeinfo

  long hr1 = hour / 10;
  long hr2 = hour % 10;
  long mn1 = minute / 10;
  long mn2 = minute % 10;
  long sc1 = second / 10;
  long sc2 = second % 10;
  long dw1 = dayofweek / 10;
  long dw2 = dayofweek % 10;

  uint8_t data[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

  data[0] = display.encodeDigit(mn1);
  data[1] = display.encodeDigit(hr2);
  data[2] = display.encodeDigit(hr1);
  data[3] = display.encodeDigit(sc2);
  data[4] = display.encodeDigit(sc1);
  data[5] = display.encodeDigit(mn2);
  data[6] = display.encodeDigit(dw2);
  data[7] = display.encodeDigit(dw1);
  display.setSegments(data);
}
