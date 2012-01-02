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

#include "max6675.h"

/*________________________________________________________________________________*/
/*__________________________________ Serial ______________________________________*/
/*________________________________________________________________________________*/

//#define DEBUG // This will send boggus data to the computer
#define MEGA

#define EnableLogging
#define PWRFailDetect

#ifdef MEGA
#define HOSTXbee           Serial
#define HOSTLCD            Serial1
#define HOSTUSB            Serial2
#define HOSTXbee_BAUD_Rate 115200
#define HOSTLCD_BAUD_Rate  115200
#define HOSTUSB_BAUD_Rate  115200
#endif

/*________________________________________________________________________________*/
/*____________________________________ Pins ______________________________________*/
/*________________________________________________________________________________*/
//Digital Pins

// Digital Pin 2 is attached to the powerfail interrupt

#define RedLED             3
#define IrLED              4
#define PulseOx            5
#define StartupLED         6

#define GND                8
#define VCC                9
#define DS                 10
#define CS                 11
#define CLK                12

#define Check_Sensors      13

//Analog Pins
#define ECG                0
#define Light              1
#define Resp               2
#define AmbTemp            3

#define Battery            5

#ifdef MEGA
#define Select_OK_button   62
#define Right_Arrow_button 63
#define Left_Arrow_button  64

#define Select_button_bit  1
#define Right_button_bit   2
#define Left_button_bit    4

#define Speaker            36
#endif

#define buttonsUp 0 // start with the buttons in the 'not pressed' state

int buttonState = buttonsUp;

#define vcc                4.91  // only used for display purposes
#define pad                9850  // balance/pad resistor value, set this to
                                 // the measured resistance of your pad resistor
#define thermr             10000 // thermistor nominal resistance

#define KEY_WAIT           1000  // Wait for potential other key press
#define VerisonID          1     // Firmware version ID
#define SessionID          0     // the SessionID
#define DeBugSession       'X'

/*________________________________________________________________________________*/
/*_________________________________ INT __________________________________________*/
/*________________________________________________________________________________*/

// Easy to read macros

#define LEFT_BUTTON_PRESSED (buttonState&lbuttonBit)
#define MIDDLE_BUTTON_PRESSED (buttonState&mbuttonBit)
#define RIGHT_BUTTON_PRESSED (buttonState&rbuttonBit)

/*________________________________________________________________________________*/

MAX6675 thermocouple(CLK, CS, DS);

int ConnectionChoice = 0

/*________________________________________________________________________________*/

