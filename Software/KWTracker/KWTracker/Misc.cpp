// Misc.cpp

/***********************************************************************************
 * #includes
 *
 * User defined headers, followed by 3rd party library headers, then standard library 
 * headers, with the headers in each section sorted alphabetically.
 * Put all #includes in .cpp file, unless needed in .h file.
 ************************************************************************************/
#include "Misc.h"

#include "Settings.h"

#include <avr/wdt.h>  // Watchdog Timer functions

#include <Arduino.h>


/**
 * Setup the LED
 *
 */
void setupLED(){
    pinMode(LED, OUTPUT);
}


/**
 * Blink the LED
 *
 * @param[in] ms the delay used for the blink
 * @param[in] times the number of times the LED is blinked
 */
void blinkLED(uint16_t ms, uint8_t times) {
  for (uint8_t i = 0; i < times; i++) {
    #ifdef LED
        analogWrite(LED, LED_BRIGHTNESS);
        delay(ms/2);
        analogWrite(LED, 0);
        delay(ms*2);
    #else
        delay(ms*2.5);  // Maintain timing approximately the same even if LED not in use to save power.
    #endif
        wdt_reset();
  }
}

/**
 * Setup Debug Output
 *
 */
void setupDebug(){
    serialDebug.begin(DEBUG_BAUD);
    serialDebug.println("\n\n\nKW Tracker.");
}


/**
 * Find the reason for the last processor reset
 *
 * @param[in] mcusrSaved the saved MCUSR register
 * @param[in] times the number of times the LED is blinked
 * @result a single char representing the reset reason
 */
char resetTest(uint8_t mcusrSaved){
  serialDebug.print(F("resetTest(): MCUSR Reg: "));
  serialDebug.print(mcusrSaved);  
  serialDebug.print(F(", "));

  if(mcusrSaved & _BV(WDRF)){
    // Watchdog reset occurred
    serialDebug.println(F("Watchdog."));
    return('W');
  }
  else if(mcusrSaved & _BV(BORF)){
    // Brownout reset occurred
    serialDebug.println(F("Brownout."));
    return('B');
  }
  else if(mcusrSaved & _BV(EXTRF)){
    // External reset occurred
    serialDebug.println(F("External."));
    return('E');
  }
  else if(mcusrSaved & _BV(PORF)){
    // Power on reset occurred
    serialDebug.println(F("Power on."));
    return('P');
  }
  else {
    // Unknown reset occurred
    serialDebug.println(F("Unknown."));
    return('U');
  }
}
