//
//  **** COMPLETE ****
//
//  Defines_Includes.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//

/*________________________________________________________________________________*/

//defines/includes

#include <stdio.h>
#include <limits.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>
#include <PString.h>
#include <serialGLCD.h>

#include "max6675.h"

/*________________________________________________________________________________*/
/*__________________________________ Serial ______________________________________*/
/*________________________________________________________________________________*/

//#define DEBUG // This will send boggus data to the computer to test the parsing
                // of the client and server applications.
#define MEGA

#define EnableLogging
#define PWRFailDetect

#ifdef  MEGA
#define HOSTXbee                Serial
#define HOSTLCD                 Serial1
#define HOSTUSB                 Serial2
#define HOSTXbee_BAUD_Rate      115200
#define HOSTLCD_BAUD_Rate       115200
#define FAST_HOSTUSB_BAUD_Rate  115200
#define SLOW_HOSTUSB_BAUD_Rate  9600
#endif

/*________________________________________________________________________________*/
/*____________________________________ Pins ______________________________________*/
/*________________________________________________________________________________*/
//Digital Pins

// Digital Pin 2 is attached to the powerfail interrupt

#define RedLED                  3
#define IrLED                   4
#define PulseOx                 5
#define StartupLED              6
#define ECGPulse                7
#define GND                     8
#define VCC                     9
#define DS                      10
#define CS                      11
#define CLK                     12

#define Check_Sensors           13
#define SetupLED                14

//Analog Pins
#define ECG                     0
#define Light                   1
#define Resp                    2
#define AmbTemp                 3
#define ECGBatt                 4
#define Battery                 5

#ifdef  MEGA
#define Select_OK_button        62
#define Right_Arrow_button      63
#define Left_Arrow_button       64

#define Select_button_bit       1
#define Right_button_bit        2
#define Left_button_bit         4

#define LoggingPin              21
#endif

#define buttonsUp               0 // start with the buttons in the 'not pressed' state

int buttonState = buttonsUp;

#define vcc                     4.91  // only used for display purposes
#define pad                     9850  // balance/pad resistor value, set this to
                                      // the measured resistance of your pad resistor
#define thermr                  10000 // thermistor nominal resistance

#define KEY_WAIT                1000  // Wait for potential other key press
#define VerisonID               1     // Firmware version ID
#define SessionID               0     // the SessionID
#define DeBugSession            'X'
#define SessionFolder           "\\Session:" + SessionID;
#define TempHeader              "Time, Tympanic, Ambient, Diff.\n"
#define VitalsHeader            "Time, ECG, ECG Pulse, RED, IR, ERROR, RESP\n"
#define OthersHeader            "Time, Light, Battery, ECG Battery\n"

/*________________________________________________________________________________*/
/*_________________________________ INT __________________________________________*/
/*________________________________________________________________________________*/

// Easy to read macros

#define LEFT_BUTTON_PRESSED (buttonState&Left_button_bit)
#define MIDDLE_BUTTON_PRESSED (buttonState&Select_button_bit)
#define RIGHT_BUTTON_PRESSED (buttonState&Right_button_bit)

/*________________________________________________________________________________*/

char Connection, Store;
int LoggingState = 0;
int DEBUGsendRandom = 0;
int ACK = 0;
int ON = 0;
int BuffersFull = 0;
int pulse = 0;
double temp = 0;
double tempIr = 0;
double tempError = 0;
double tempRed = 0;
double tempECG = 0;
double tempRESP = 0;
double tempLight = 0;
double AmbientTemp = 0;
double tempBat = 0;
double tempECGBat = 0;
double ECGPulseTemp = 0;
const string ACK = "********************************************************\n
            The System has booted up and no issue has undergone.\n
            The System has initialized the following:\n
            \t->initLCD();\n
            \t->initEEPROM();\n
            \t->initbuttons();\n
            \t->initLEDPins();\n
            \t->initDigitalPins();\n
            \t->initSensors();\n
            \t->attachInterrupts()\n
            \t->initXbee();\n
            \t->initUSB();\n
            \t->initVDIP();\n
            \t->initBuffers();\n
            \t->initMenus();\n\n
            The startup took:" + millis() + "ms\n
            This is an acknoledgement of smooth running.\n\n
            ********************************************************\n
            Copyright. 2012 Frank and Thai's Med. R&D CANADA.\n
            ********************************************************\n";

// in this one:
// time, ambientTemp, TympTemp, DiffTemp (7 characters -> in 140 we get 20 samples/page)

char vdipBuffer1[140];
PString logEntryTemp(vdipBuffer1, sizeof(vdipBuffer1)); // Create a PString object called logEntry

// in this one:
// time, ECG, ECG Pulse, SPO2 RAW, SPO2 IR, SPO2 ERROR, RESP (13 characters -> in 260 we get 20 samples/page)

char vdipBuffer2[260];
PString logEntryVitals(vdipBuffer2, sizeof(vdipBuffer2)); // Create a PString object called logEntry

// in this one:
// time, Light, Battery, ECG Battery (5 characters -> in 100 we get 20 samples/page)

char vdipBuffer3[140];
PString logEntryOthers(vdipBuffer3, sizeof(vdipBuffer3)); // Create a PString object called logEntry

char valBuffer[15];  // Buffer for converting numbers to strings before appending to vdipBuffer


/*________________________________________________________________________________*/
/*________________________________________________________________________________*/
/*________________________________________________________________________________*/


