# BasicTracker
Light weight long run time cheap tracker

#Hardware


##Power

###Battery
Single AA or AAA cell, so 0.8v to 1.6v input kind of range.
PCB mounted metal battery mount option, and solder option.
Ideal Diode option so solar panel doesnt try to charge battery?

###Solar
Option via MAX40200AUK ideal diode


###Boost Converter
Boost converter to 1.8v with 3.3v option

Step ups in stock with JLC:
L6920DBTR - $1.40 RP Protect, Min startup for 3.3vout@40mA = 0.72v
TPS61220DCKR - $0.49 Min startup for 3.3vout@40mA = 0.7v
TLV61220DBVR - $0.26. Min startup for 3.3vout@40mA = 0.7v

* TPS61200DRC - $0.85.  Min startup for 3.3vout@40mA = 0.4v, max 150mA at 0.7in

####Inductor
* SMD_Murata-Electronics-1227AS-H-2R2M-P2_C435389



###Voltage Measuring
Measure both Battery and Solar

 
##GPS Module
Ublox Max M8C / M7C to get 1.8v operation and power saving.
Cheap ATGM336N would have been nice as low price, but needs 3v plus.
Quectel L70 is cheap and great performance but only 3.3v
Copy Raj (OK1kvk) and go for a bare GPS chip rather than module?

Connected I2C, PPS, Battery Backup etc
Battery backup via resistor, capacitor and diode
Antenna Options - Chip, Wire, static leak resister

###GPS Power Switch
* SIP32431DR3-T1GE3

###GPS Filtering
* MuRata_BLM15HD102SN1D_1kR-25-at100MHz-250mA_C21516
 
##Processor
ATMega1284 - In stock in JLC, 10mmx10mm, 128kb of storage, 16kb of ram
	Step up from 328 but still same family
	JTAG interface not one wire debug.
	Info on using the 1284 - https://prominimicros.com/
	Arduino Core - https://github.com/MCUdude/MightyCore
4Mhz crystal (max at 1.8v) and option to use /8 fuse.

Move to a ATSAMD21G18A-AU or similar?  Still arduinio compatible but so much more powerful.
	ARM Cortex SWD interface?  Built in RTC.  Not instock with JLC

STM xx?
Ideally would get a USB Interface, but no easy in JLC stock way found.

###Crystal
* TAXM8M4RFDCET2T * 12pF
 
##Radio
SX1276 on the DRF1278F module - http://www.dorji.com/products-detail.php?ProId=14
	1.8v to 3.6v, < 1uA standby
Options of LoRa or RTTY etc.
Use footprint that can do SRF1278, XL1278 and RFM9X


#Protocols
#LoRa - UKHAS style

#RTTY - UKHAS style

#The Things Network (TTN)
How about TTN upload too? - 868Mhz

Steve G8KHW did a tracker based on xx but cant find the code?
	https://groups.google.com/g/ukhas/c/SxUo0VpO1XQ/m/mD6qNCW9BgAJ
	

Stuarts TTN code: https://github.com/StuartsProjects/TTN_GPS_Tracker
	Based on https://www.thethingsnetwork.org/labs/story/lorawan-gsp-tracker
	Uses the ATmega328P, RFM98 & LMIC library

Junior IOT code: https://github.com/JuniorIOT/GPS-Lora-Balloon-rfm95-TinyGPS
	Uses the ATmega328P, RFM95 & LMIC library
	
Nick's example of LMIC library on a 328p
	https://github.com/descartes/Arduino-LMIC-example
	
LMIC library https://github.com/matthijskooijman/arduino-lmic
	Supports SX1272 and SX1276 families (inc RFM92 and RFM95)
	
Adafruit TTN library: https://github.com/adafruit/TinyLoRa/

ICSpace Multi region TTN Tracker - https://github.com/ImperialSpaceSociety/picotracker-Lora
	Uses Murata ABZ LoRa Module (STM32 and LoRa radio combined)
	Updated TTNHABBridge - https://github.com/ImperialSpaceSociety/ttnhabbridge

Draguinio STM32 based TTN Tracker - https://www.tindie.com/products/edwin/lorawan-gps-tracker-with9-axis-accelerometer-lgt92/

http://revspace.nl/TTNHABBridge for uploader to HabHub

Needs dedicated LoraWAN reciever like:
Or could use loraGateway with this:  https://github.com/bokse001/dual_chan_pkt_fwd


#IDE
Move away from Arduinio?
Still need Minicore to work?  What does minicore give us when not using a bootloader?
Or Mightcore for ATMega1284p - https://github.com/MCUdude/MightyCore

PlatformIO? - https://platformio.org/
VisualCode?


#Code
Stuarts SX12XX Library will do RTTY and Lora - https://github.com/StuartsProjects/SX12XX-LoRa
as used in Stuarts HAB2 code - https://github.com/StuartsProjects/HAB2

Dave's code does RTTY & Lora - https://github.com/daveake/FlexTrack

OK1CDJ Picotracker code -  https://github.com/ok1cdj/Picotracker/blob/master/sw/picotracker.ino

RoelKroes TB Tracker -  https://github.com/RoelKroes/TBTracker
 
 
#Others Projects
UPU's original 1.8v 4Mhz - https://ava.upuaut.net/?p=383 https://ava.upuaut.net/?p=353

