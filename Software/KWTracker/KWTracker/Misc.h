// Misc.h

#ifndef MISC_H
#define MISC_H

//#include "Settings.h"

#include <Arduino.h>

void setupLED();

void blinkLED(uint16_t ms, uint8_t times);

void setupDebug();

char resetTest(uint8_t mcusrSaved);

#endif