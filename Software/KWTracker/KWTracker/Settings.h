// Settings.h

#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>


// Comment out for live flight
#define DEBUG

// Output pin for LED, Comment out to not use LED
#define LED                 PIN_PA3
#define LED_BRIGHTNESS      150

#define DEBUG_BAUD          115200
#define serialDebug         Serial

#define GPS_BAUD            9600
#define serialGPS           Serial1

#endif