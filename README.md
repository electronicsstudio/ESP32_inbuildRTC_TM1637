# ESP32_inbuildRTC_TM1637

Here, we are using this process to print the inbuilt ESP32 RTC time on a 6-digit TM1637 display. There are some 
changes, as the time format may be 72-hour based. We can't rely on the inbuilt RTC time because the ESP32 lacks 
a battery backup pin for the RTC.
