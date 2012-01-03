//
//  
//
//  Init.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//

/* --------------------------------------------------------- */

void initLCD(void){
    // Start The Serial Connection
    HOSTLCD.begin(HOSTLCD_BAUD_Rate);
    // Wait for connection to establish
    delay(100);
}

/* --------------------------------------------------------- */

void initXBee(void){
    
    LCDprintln("***** INIT XBEE Rx/Tx *****");
    // Start The Serial Connection
    HOST.begin(HOST_BAUD_Rate);
    // Wait for connection to establish
    delay(100);
    LCDprintln("   [OK]    ");
    
    Connection = 'X';
}

/* --------------------------------------------------------- */

void initVDIP(void){
    
    LCDprintln("***** INIT VDIP Rx/Tx *****");
    // Start The Serial Connection
    HOSTUSB.begin(HOSTUSB_BAUD_Rate);
    // Wait for connection to establish
    delay(100); 
    
    printACK_Sys_files();
    
    LCDprintln("   [OK]    ");
    
    Connection = 'S';
}

/* --------------------------------------------------------- */

void initUSB(void){
    
    LCDprintln("***** INIT PC/USB Rx/Tx *****");
    // Start The Serial Connection
    HOST.begin(HOST_BAUD_Rate);
    // Wait for connection to establish
    delay(100);
    LCDprintln("   [OK]    ");
    
    Connection = 'P';
}

/* --------------------------------------------------------- */

void initMenus(void){
    
    // Start && Install the Menu system to the Memory
   
}

/* --------------------------------------------------------- */

void askForConnectionTypes(void){
    
    // connect to XBee?
    // Warning no connection to PC
    
#define XBeeConnected
    
    // connect to PC-USB
    
    // Make sure that they know to be on the D1 
    // select switch in order to send commands,
    // the xbee cannot be transparent, it will only
    // process AT commands preceeded by '+++'
    
#define USBConnected
    
    // Store Data?
#define StoreUSB

}

/* --------------------------------------------------------- */

void askToStoreData(void){
    
}

/* --------------------------------------------------------- */

void initDebugDialog(void){
    
    LCDprintln(" Staring Up the Debug Dialog ");

        // Start a Rx/Tx line from PC to send various types of data
        // and to view the status of the device
    
    LCDprintln("   [OK]    ");

}

/* --------------------------------------------------------- */

void initEEPROM(){
    LCDprintln("***** INIT EEPROM *****");
    byte readVersionID, readSessionID;
    
    // Check the Version ID
    //  If not VersionID -> write the proper ID
    
    readVersionID = EEPROMcheckVersionID();
    
    if(readVersionID != VersionID){
        EEPROMwriteVersionID(VersionID);
    }
    
    // Check the Session ID
    //  If not SessionID or DEBUG -> write the proper ID (usually +1)
    readSessionID = EEPROMcheckSessionID();
    
    if(readSessionID == DebugSession){
        LCDprintln("***** DEBUG MODE *****");    
    }
    else if(readSessionID != SessionID){
        EEPROMwriteSessionID(SessionID);
    }
    LCDprintln("   [OK]    ");
    
    delay(1000);
}

/* --------------------------------------------------------- */

void initLEDPins(void){
    
    // Setting IR and RED LED Pin modes and original values
    //  -> IR = Output, LOW
    //  -> Red = Output, high
    
    LCDprintln("Init LED Pins");
    
    pinMode(IrLED, OUTPUT); digitalWrite(IrLED, LOW);
    pinMode(RedLED, OUTPUT); digitalWrite(RedLED, LOW);
    
    LCDprintln("  [OK]    ");

}

/* --------------------------------------------------------- */

void initDigitalPins(void){
    
    // init buttons as inputs and INT
    
    LCDprintln("Init Digital Pins");
    
    pinMode(Left_Arrow_button, INPUT);
    pinMode(Select_OK_button, INPUT);
    pinMode(Right_Arrow_button, INPUT);
    
    // "turn on" the internal pullup resistors
    digitalWrite(Left_Arrow_button, HIGH);
    digitalWrite(Select_OK_button, HIGH);
    digitalWrite(Right_Arrow_button, HIGH);
    
#ifdef MEGA
    PCMSK2 |= (1 << PCINT16) | (1 << PCINT17) | (1 << PCINT18);
    PCICR  |= (1 << PCIE2);
#endif
    
    // the following pins are used by the thermocouple
    // to read in a grey code like temperature
    
    pinMode(VCC, OUTPUT); digitalWrite(VCC, HIGH);
    pinMode(GND, OUTPUT); digitalWrite(GND, LOW);
    
    pinMode(LoggingPin, INPUT); digitalWrite(LoggingPin, HIGH);
    pinMode(PulseOx, INPUT);
    
    LCDprintln("  [OK]    ");
    
}

/* --------------------------------------------------------- */


void initSensors(void){
    int sensorVoltageReading = 0;
    
    LCDprintln("Init Digital Pins");

    sensorVoltageReading = DigitalRead(Check_Sensors);
    
    if(sensorVoltageReading == HIGH){

#define SensorsOK
        LCDprintln("  [OK]    "); 
    }
    else{
        return;
    }
}

/* --------------------------------------------------------- */
/* --------------------------------------------------------- */
/* --------------------------------------------------------- */

