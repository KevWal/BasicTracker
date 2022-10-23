/*
   RadioLib Horus Binary FSK4 Packet Generation & Transmitter Example

   This example sends an example FSK-4 'Horus Binary' message using SX1278's
   FSK modem. This example uses 'stock' RadioLib - and makes calls into the radio's 
   lower-level functions.

   This signal can be demodulated using a SSB demodulator (SDR or otherwise), and
   horusdemodlib: https://github.com/projecthorus/horusdemodlib/wiki

   Other modules that can be used for FSK4:
   (Untested, but work with RTTY to are likely to work here too)
    - SX127x/RFM9x
    - RF69
    - SX1231
    - CC1101
    - SX126x
    - nRF24
    - Si443x/RFM2x
    - SX128x

*/

#include <RadioLib.h>
#include "Horus_L2.h"
#include "Horus_L1.h"
#include <util/crc16.h>
#include <arduino.h>


// RADIO SETUP
#define TX_FREQ         434.200
#define FSK4_BAUD       100
#define FSK4_SPACING    270    // NOTE: This results in a shift of 244 Hz due to the PLL Resolution of the SX127x

// SX1278 has the following connections:
// NSS pin:   10
// DIO0 pin:  2
// RESET pin: 9
// DIO1 pin:  3
SX1278 radio = new Module(10, 2, 9, 3);

// Horus v2 Mode 1 (32-byte) Binary Packet Struct
struct HorusBinaryPacketV2
{
    uint16_t  PayloadID;
    uint16_t  Counter;
    uint8_t   Hours;
    uint8_t   Minutes;
    uint8_t   Seconds;
    float     Latitude;
    float     Longitude;
    uint16_t  Altitude;
    uint8_t   Speed;       // Speed in Knots (1-255 knots)
    uint8_t   Sats;
    int8_t    Temp;        // Twos Complement Temp value.
    uint8_t   BattVoltage; // 0 = 0.5v, 255 = 2.0V, linear steps in-between.
    // The following 9 bytes (up to the CRC) are user-customizable. The following just
    // provides an example of how they could be used.
    uint8_t     dummy1;      // unsigned int
    float     dummy2;       // Float 
    uint8_t     dummy3;     // battery voltage test
    uint8_t     dummy4;     // divide by 10
    uint16_t     dummy5;    // divide by 100
    uint16_t    Checksum;    // CRC16-CCITT Checksum.
}  __attribute__ ((packed));

// Buffers and counters.
uint8_t rawbuffer [128];   // Buffer to temporarily store a raw binary packet.
uint8_t codedbuffer [128]; // Buffer to store an encoded binary packet
//char debugbuffer[256]; // Buffer to store debug strings
uint16_t packet_count = 1;  // Packet counter




// Fast CRC16 code, using Atmel's optimized libraries!
unsigned int crc16(unsigned char *string, unsigned int len) {
	unsigned int i;
	unsigned int crc;
	crc = 0xFFFF; // Standard CCITT seed for CRC16.
	// Calculate the sum, ignore $ sign's
	for (i = 0; i < len; i++) {
		crc = _crc_xmodem_update(crc,(uint8_t)string[i]);
	}
	return crc;
}

void PrintHex(char *data, uint8_t length, char *tmp){
 // Print char data as hex
 byte first;
 int j=0;
 for (uint8_t i=0; i<length; i++) 
 {
   first = ((uint8_t)data[i] >> 4) | 48;
   if (first > 57) tmp[j] = first + (byte)39;
   else tmp[j] = first ;
   j++;

   first = ((uint8_t)data[i] & 0x0F) | 48;
   if (first > 57) tmp[j] = first + (byte)39; 
   else tmp[j] = first;
   j++;
 }
 tmp[length*2] = 0;
}


int build_horus_binary_packet_v2(uint8_t *buffer){
  // Generate a Horus Binary v2 packet, and populate it with data.
  // The assignments in this function should be replaced with real data

  struct HorusBinaryPacketV2 BinaryPacketV2;

  BinaryPacketV2.PayloadID = 256; // 0 = 4FSKTEST-V2. Refer https://github.com/projecthorus/horusdemodlib/blob/master/payload_id_list.txt
  BinaryPacketV2.Counter = packet_count;
  BinaryPacketV2.Hours = 12;
  BinaryPacketV2.Minutes = 34;
  BinaryPacketV2.Seconds = 56;
  BinaryPacketV2.Latitude = 0.0;
  BinaryPacketV2.Longitude = 0.0;
  BinaryPacketV2.Altitude = 0;
  BinaryPacketV2.Speed = 0;
  BinaryPacketV2.BattVoltage = 0;
  BinaryPacketV2.Sats = 0;
  BinaryPacketV2.Temp = 0;
  // Custom section. This is an example only, and the 9 bytes in this section can be used in other
  // ways. Refer here for details: https://github.com/projecthorus/horusdemodlib/wiki/5-Customising-a-Horus-Binary-v2-Packet
  BinaryPacketV2.dummy1 = 1;        // uint8
  BinaryPacketV2.dummy2 = 1.23456;  // float32
  BinaryPacketV2.dummy3 = 100;      // uint8 - interpreted as a battery voltage 0-5V
  BinaryPacketV2.dummy4 = 123;      // uint8 - interpreted as a fixed-point value (div/10)
  BinaryPacketV2.dummy5 = 1234;     // uint16 - interpreted as a fixed-point value (div/100)

  BinaryPacketV2.Checksum = (uint16_t)crc16((unsigned char*)&BinaryPacketV2,sizeof(BinaryPacketV2)-2);

  memcpy(buffer, &BinaryPacketV2, sizeof(BinaryPacketV2));
	
  return sizeof(struct HorusBinaryPacketV2);
}


void setup() {
  Serial.begin(9600);

  // initialize SX1278 with default settings
  Serial.print(F("[SX1278] Initializing ... "));
  int state = radio.beginFSK();

  // when using one of the non-LoRa modules for FSK4
  // (RF69, CC1101, Si4432 etc.), use the basic begin() method
  // int state = radio.begin();

  if(state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while(true);
  }

  Serial.print(F("[FSK4] Initializing ... "));

  // initialize FSK4 transmitter
  state = fsk4_setup(&radio, TX_FREQ, FSK4_SPACING, FSK4_BAUD);

  if(state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while(true);
  }

}

void loop() {
  Serial.println(F("Generating Horus Binary v2 Packet"));
  // Generate packet
  int pkt_len = build_horus_binary_packet_v2(rawbuffer);
  // Debugging
  Serial.print(F("Uncoded Length (bytes): "));
  Serial.println(pkt_len);
  //Serial.print("Uncoded: ");
  //PrintHex(rawbuffer, pkt_len, debugbuffer);
  //Serial.println(debugbuffer);

  // Apply Encoding
  int coded_len = horus_l2_encode_tx_packet((unsigned char*)codedbuffer,(unsigned char*)rawbuffer,pkt_len);
  // Debugging
  Serial.print(F("Encoded Length (bytes): "));
  Serial.println(coded_len);
  //Serial.print("Coded: ");
  //PrintHex(codedbuffer, coded_len, debugbuffer);
  //Serial.println(debugbuffer);

  // Transmit!
  Serial.println(F("Transmitting Horus Binary v2 Packet"));

  // send out idle condition for 1000 ms
  fsk4_idle(&radio);
  delay(1000);
  fsk4_preamble(&radio, 8);
  fsk4_write(&radio, codedbuffer, coded_len);

  Serial.println(F("done!"));

  delay(1000);

  packet_count++;
}