# BasicTracker
Light weight long run time cheap tracker

# Hardware

## Power
Single AA or AAA cell, 0.8v to 1.6v input range - TPS61200 to boost to 1.8 or 3.3v

Solar Panel, 0.5v to 4.2v input range - either connect direct or use TPS61200 to boost or limit or MCP1700T to limit to 1.8 or 3.3v

Single AA or AAA cell and Solar Panel, needs 2 x MAX40200 ideal diodes to keep supplies separate and TPS61200 to boost or limit to 1.8v or 3.3v
	Primary cells will keep tracker going over night till battery runs out

Single Lithium, 2.8v to 4.2v useful range, needs Battery Protection on Lipo to limit min discharge voltage and MCP1700T to limit to 1.8 or 3.3v
	Will likely freeze at night

Single Lithium and Solar Panel, Solar Panel needs TPS61200 to stop lithium discharging through it and buck/boost voltage to max 4.2v for Lithium charging.  Lithium needs Battery Protection to limit min discharge voltage and MCP1700T to limit to 1.8 or 3.3v. Lithium will likely freeze at night.


### Boost Converter
Boost converter to 1.8v with 3.3v and 4.2v (for lithium charge) option

Step ups in stock with JLC:
L6920DBTR - $1.40 RP Protect, Min startup for 3.3vout@40mA = 0.72v
TPS61220DCKR - $0.49 Min startup for 3.3vout@40mA = 0.7v
TLV61220DBVR - $0.26. Min startup for 3.3vout@40mA = 0.7v
*TPS61200DRC - $0.85.  Min startup for 3.3vout@40mA = 0.4v, max 150mA at 0.7v in*

#### Inductor
*SMD_Murata-Electronics-1227AS-H-2R2M-P2_C435389*



### Voltage Measuring
Measure Battery, Solar and Lithium voltages

 
## GPS Module
Ublox Max 6G 1.75v to 2.0v
Ublox Max 7C / M8C 1.65v to 3.6v
Ublox Max M8Q 2.7v to 3.6v

ATGM336N 2.7v to 3.6v.
Quectel L70 2.8v to 4.3v

Connected I2C, PPS, Battery Backup, etc
Battery backup via resistor, capacitor and diode
Antenna Options - Chip, Wire, static leak resister option

### GPS Power Switch
*SIP32431DR3-T1GE3 - instock in JLC*

### GPS Filtering
*MuRata_BLM15HD102SN1D_1kR-25-at100MHz-250mA_C21516*

### GPS Antenna
1/4 wave wire = 45.2mm (1575Mhz) (1/4 wave generally better than chip antenna IMO)
 
 
## Processor
ATMega1284p - In stock in JLC, 10mmx10mm, 128kb of storage, 16kb of ram
	Step up from 328 but still same family
	JTAG interface not one wire debug.
	Info on using the 1284 - https://prominimicros.com/
	Arduino Core - https://github.com/MCUdude/MightyCore
4Mhz crystal (max at 1.8v) and option to use /8 fuse.

Move to a ATSAMD21G18A-AU or similar?  Still arduinio compatible but so much more powerful.
	ARM Cortex SWD interface?  Built in RTC.  Not instock with JLC

STM xx?
Ideally would get a USB Interface, but no easy in JLC stock way found.

### Crystal
XXFEELNANF-14.7456M & 16pF.  Divide by 8 to get 1.843200Mhz and use 115,200 comms


## Fuses
Extended = 0xFF
High = 0x16
Low = 0x7F (ck div 8 set)

Arduino
	Clock External 14.7456 (even though clk/8 fuse set)?

 
## Radio
SX1278 (137-525MHz) on the DORJI DRF1278F module - http://www.dorji.com/products-detail.php?ProId=14
	1.8v to 3.6v, < 1uA standby

or

Hope RF RFM98W - 433MHz band
https://www.hoperf.com/modules/lora/RFM98.html
	1.8v to 3.7v, < 1uA standby


# IDE
Move away from Arduinio V1?

Mightcore for ATMega1284p - https://github.com/MCUdude/MightyCore

Arduino V2 - https://www.arduino.cc/en/Tutorial/getting-started-with-ide-v2
Visual Micro - Arduino for Visual Studio - https://www.visualmicro.com/
PlatformIO IDE - Arduino and Visual Studio Code - https://platformio.org/

## Arduino V2
Too add the AVR Dragon programmer, add the below to:

C:\Users\WALTONK\AppData\Local\Arduino15\packages\MightyCore\hardware\avr\2.1.2\programmers.txt

dragon_jtag.name=Dragon JTAG (KW)
dragon_jtag.communication=usb
dragon_jtag.protocol=dragon_jtag
dragon_jtag.program.protocol=dragon_jtag
dragon_jtag.program.tool=avrdude
dragon_jtag.program.extra_params=-P usb

## Microchip Studio
Good Device Programming interface for fuses
Works with:
	Pololu USB AVR (STK500) - can supply / program at 3.3 or 5v; and
	AVR Dragon - can supply 5v, can program down to 1.8v

# Others Projects
UPU's original 1.8v 4Mhz - https://ava.upuaut.net/?p=383 https://ava.upuaut.net/?p=353
	RFM22B

# Code Research
Dave's flexavr - https://github.com/daveake/flexavr
	Designed for Standalone AVR attached to a Pi Zero
	APRS via PWM to radio module, LoRa via RFM98W (sx1278, no library, direct register writes), Some RTTY functions, but doesn't seem complete?

OK1CDJ Picotracker - https://github.com/ok1cdj/Picotracker/blob/master/sw/picotracker.ino
	RTTY via RFM22 only, but useful power saving code.


Dave's FlexTrack - https://github.com/daveake/FlexTrack
	APRS via PWM to radio module, RTTY via Radiometrix MTX2 or Lora, LoRa via RFM98W (sx1278) 
	No library, direct register writes, spread across multiple ino's
	Onboard landing position prediction
	
Dave's FlexTrack TTGO - https://github.com/daveake/FlexTrack_TTGO
	As above, designed for TTGO board, LoRa & RTTY


*RoelKroes TB Tracker -  https://github.com/RoelKroes/TBTracker*
	RTTY and LoRa via SX127x (or Hope RFM9x)
	Uses RadioLib - https://github.com/jgromes/RadioLib and tinyGPS++ https://github.com/mikalhart/TinyGPSPlus
		Radiolib supports SX126/7/8x, RFM9x and many others, supports RTTY, Morse, SSTV, Hellschreiber, LoRa and support for LoRaWAN and APRS in discussion, but complex
	Has sleep functionality, nicely laid out
	

Stuarts HAB2 code - https://github.com/StuartsProjects/HAB2
	RTTY and Lora via SX126/7/8x
	Uses Stuarts SX12XX Library https://github.com/StuartsProjects/SX12XX-LoRa
	All in a single .ino and .h
	Has Upload command capability, Sleep, EEPROM config complexity
	Looks like the one file does command mode upload and tracker functionality




## The Things Network (TTN)
How about TTN upload too?

https://www.thethingsnetwork.org/docs/lorawan/frequency-plans/
EU 868, US 902, CN 470, AU 915, AS 923, etc

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
Or could use LoRaGateway with this:  https://github.com/bokse001/dual_chan_pkt_fwd


## APRS
Can't do airbourne in the UK or on a UK call sign, 144Mhz, licensed spectrum


## Issues
Want to do RTTY, LoRa, APRS & LoRaWAN (TTN) from the same tracker.
LoRa HAB and RTTY are best done on 433Mhz license free, although could be done on 868Mhz
LoRaWAN has to be done on 868Mhz license free in Europe
APRS is on 144Mhz

HopeRF modules dont seem to have lower and upper band outputs connected to aerial?
RadioLib doesn't do APRS or LoRaWAN

## LoRa Modes

### From lora-gateway code:
Num; ImplicitOrExplicit; ErrorCoding; Bandwidth; SpreadingFactor; LowDataRateOptimize; BaudRate; Description
0: EXPLICIT_MODE, ERROR_CODING_4_8, BANDWIDTH_20K8, SPREADING_11, 1,    60, Telemetry - Normal mode for telemetry
1: IMPLICIT_MODE, ERROR_CODING_4_5, BANDWIDTH_20K8, SPREADING_6,  0,  1400, SSDV - Normal mode for SSDV
2: EXPLICIT_MODE, ERROR_CODING_4_8, BANDWIDTH_62K5, SPREADING_8,  0,  2000, Repeater - Normal mode for repeater network	
3: EXPLICIT_MODE, ERROR_CODING_4_6, BANDWIDTH_250K, SPREADING_7,  0,  8000, Turbo - Normal mode for high speed images in 868MHz band
4: IMPLICIT_MODE, ERROR_CODING_4_5, BANDWIDTH_250K, SPREADING_6,  0, 16828, TurboX - Fastest mode within IR2030 in 868MHz band
5: EXPLICIT_MODE, ERROR_CODING_4_8, BANDWIDTH_41K7, SPREADING_11, 0,   200, Calling - Calling mode
6: EXPLICIT_MODE, ERROR_CODING_4_5, BANDWIDTH_20K8, SPREADING_7,  0,  2800, Uplink - Uplink explicit mode (variable length)
7: IMPLICIT_MODE, ERROR_CODING_4_5, BANDWIDTH_41K7, SPREADING_6,  0,  2800, Uplink - Uplink mode for 868
8: EXPLICIT_MODE, ERROR_CODING_4_5, BANDWIDTH_20K8, SPREADING_7,  0,   910, Telnet - Telnet-style comms with HAB on 434
9: IMPLICIT_MODE, ERROR_CODING_4_5, BANDWIDTH_62K5, SPREADING_6,  0,  4500, SSDV Repeater - Fast (SSDV) repeater network

# Launch Announcement

Also testing some backup trackers:


Hoping to do a launch on Sunday (20th, tomorrow) morning, before 9am GMT from Northamptonshire, UK of a Yokohama Balloon, carrying a custom built 'Single AA' tracker based originally on the TBTracker code base, but heavily expanded and modified.

Looking to A) test my ability to get a Yokohama to float, and B) the custom tracker being able to be decoded across RTTY, LoRa and Horus FSK4.  Flight path is predicted to take it across Holland, Germany & maybe Poland - but with the weather systems all over the place at the moment, who knows! :)

The tracker is based on the ATmega1284 running at 1.8432Mhz, Ublox GPS and DRF1278 radio module, all with a 1.8v VCC.  About 25g with 1 x AA.

Yokohama is 48.6g and was pre stretched at 0.22PSI up to about 99" circumference and filled to 6g of free lift.

RTTY - KW-BCK1 - 50 Baud, 8n2, 610Hz shift, 434.113Mhz, 1 short sentence repeated 3 times every once every 2 minutes
	RX Frequency for me was about 434.084Mhz

LoRa - KW-BCK2 - Mode 5, 433.650Mhz, 1 sentence repeated 3 times every once every 2 minutes
	Field String of 0123456AI9, RX frequency for me of 433.653

Horus FSK4 - G7PMO-V2 - 100 Baud, 244Hz shift, 434.340Mhz, 1 binary packet repeated 3 times every once every 2 minutes
	RX frequency for me was about 434.312Mhz
	
Weight

28g + 6g free lift = 34