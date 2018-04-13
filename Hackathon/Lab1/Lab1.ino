// Lab1.ino

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include <LoRa.h>
#define debugSerial SerialUSB
#define loraSerial  Serial2

// Variables will contain your personal OTAA Activation Keys
uint8_t devEUI[8] ;   // Device EUI
uint8_t appEUI[8] ;   // App EUI
uint8_t appKey[16] ;  // App Key
const uint8_t appKeyPrefix[8] = {0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88} ;

const uint8_t appEUIfromTTN[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} ;

void setup()
{
  while (!debugSerial && (millis() < 10000)) ;
	debugSerial.begin(115200) ;
  debugSerial.println("Microchip Technology ExpLoRer Starter Kit") ;
  debugSerial.println("21080_IoT3 Masters 2017 Class") ;
  debugSerial.println("Lab 1") ;

  // --------------------------------------------------------------------------
  // Init section
  // --------------------------------------------------------------------------
  // Temperature sensor
  //pinMode(TEMP_SENSOR, INPUT) ;
  //analogReadResolution(12) ;

  // LoRa
  LoRa.hwInit() ;
	loraSerial.begin(LoRa.getDefaultBaudRate()) ;
  LoRa.initLoRaStream(loraSerial) ;
  LoRa.swInit() ;

  // --------------------------------------------------------------------------
  // Activation keys section
  // --------------------------------------------------------------------------
  // Get the internal Hardware EUI of the LoRaWAN module
  uint8_t hwEUI[8] ;
  uint8_t len = LoRa.getHWEUI(hwEUI, sizeof(hwEUI)) ;
  if (len == 0) { debugSerial.println("Error to get HwEUI") ; while(1) ; }
  
  // Device EUI is the unique identifier for this device on the network
  // Assign the Hardware EUI as the devEUI key
  memcpy(devEUI, hwEUI, sizeof(hwEUI)) ;
  // App EUI is generated by the TTN Application Server
  memcpy(appEUI, appEUIfromTTN, sizeof(appEUIfromTTN)) ;
  // App Key can be a default key for all devices or can be unique per device
  // Here the key is computed by the help of the Device EUI
  // The 16-Bytes format will start by: FF EE DD CC BB AA 99 88 and 
  // will finish by: the 8 Bytes of the devEUI
  memcpy(appKey, appKeyPrefix, sizeof(appKeyPrefix)) ;
  memcpy(appKey + 8, devEUI, sizeof(devEUI)) ; 
}

void loop()
{
  debugSerial.println("") ;
  debugSerial.print("devEUI = ") ;
  displayArrayInOneLine(devEUI, sizeof(devEUI)) ;
  debugSerial.print("appEUI = ") ;
  displayArrayInOneLine(appEUI, sizeof(appEUI)) ;
  debugSerial.print("appKey = ") ;
  displayArrayInOneLine(appKey, sizeof(appKey)) ; 
  
  // Step 9.1 Read value from analog input
  // ### Your code here ###
  // Step 9.2 Convert the value to voltage
  // ### Your code here ###
  // Step 9.3 Calibrate to 0°C
  // ### Your code here ###
  // Step 9.4 Convert to temperature value
  // ### Your code here ###
  // Step 9.5 Display the temperature on the serial monitor
  // ### Your code here ###
  // Step 9.6 Add a 3 sec delay before reading a new value
  delay(10000) ;
}

// --------------------------------------------------------------------------
// Display array in HEX format routine
// --------------------------------------------------------------------------
void displayArrayInOneLine(const uint8_t tab[], uint8_t tabSize)
{
  char c[2] ;
  for (uint8_t i = 0; i < tabSize; i++)
  {
    sprintf(c, "%02X", tab[i]) ;
    debugSerial.print(c) ;
  }
  debugSerial.println("") ;
}

