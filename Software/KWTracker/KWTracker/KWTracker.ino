// KWTracker.ino

/***********************************************************************************
 * #includes
 *
 * User defined headers, followed by 3rd party library headers, then standard library 
 * headers, with the headers in each section sorted alphabetically.
 * Put all #includes in .cpp file, unless needed in .h file.
 ************************************************************************************/

#include "KWTracker.h"

#include "Misc.h"
#include "Settings.h"

#include <avr/wdt.h>  // Watchdog Timer functions
#include <SPI.h> // Required by RadioLib, Move to Radio.h when I create it
#include <SoftwareSerial.h>  // Required by RadioLib, Move to Radio.h when I create it

#include <Arduino.h>

/**
 * Put your setup code here, to run once.
 *
 */
void setup() {
  // Watchdog Timer Setup
  #ifdef DEBUG
    wdt_enable(WDTO_4S); // Use a 4 second timeout in testing to make sure we dont get close to 8S WDT in normal operation.
  #else
    wdt_enable(WDTO_8S);
  #endif
    
  wdt_reset();
  

  // Save the MCUSR register so that we can work out why we reset
  uint8_t mcusrSaved = MCUSR;
  MCUSR = 0;  // Must clear the MCUSR register ready for next reset

  // TODO Power Down everything we dont use

  setupLED();
  blinkLED(250, 30);

  setupDebug();

  // Work out why we reset, and print answer if in debug mode.
  resetTest(mcusrSaved);


}


/**
 * Put your main code here, to run repeatedly.
 *
 */
void loop() {


}