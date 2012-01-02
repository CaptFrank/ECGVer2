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
    
    LCDprint("***** INIT XBEE Rx/Tx *****");
    // Start The Serial Connection
    HOST.begin(HOST_BAUD_Rate);
    // Wait for connection to establish
    delay(100);
    LCDprint("   [OK]    ");
    
    Connection = 'X';
}

/* --------------------------------------------------------- */

void initVDIP(void){
    
    LCDprint("***** INIT VDIP Rx/Tx *****");
    // Start The Serial Connection
    HOSTUSB.begin(HOSTUSB_BAUD_Rate);
    // Wait for connection to establish
    delay(100); 
    LCDprint("   [OK]    ");
    
    Connection = 'S';
}

/* --------------------------------------------------------- */

void initUSB(void){
    
    LCDprint("***** INIT PC/USB Rx/Tx *****");
    // Start The Serial Connection
    HOST.begin(HOST_BAUD_Rate);
    // Wait for connection to establish
    delay(100);
    LCDprint("   [OK]    ");
    
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
    
    LCDprint(" Staring Up the Debug Dialog ");

        // Start a Rx/Tx line from PC to send various types of data
        // and to view the status of the device
    
    LCDprint("   [OK]    ");

}

/* --------------------------------------------------------- */

void initEEPROM(){
    LCDprint("***** INIT EEPROM *****");
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
        LCDprint("***** DEBUG MODE *****");    
    }
    else if(readSessionID != SessionID){
        EEPROMwriteSessionID(SessionID);
    }
    LCDprint("   [OK]    ");
    
    delay(1000);
}

/* --------------------------------------------------------- */

void initLEDPins(void){
    
    // Setting IR and RED LED Pin modes and original values
    //  -> IR = Output, LOW
    //  -> Red = Output, high
    
    LCDprint("Init LED Pins");
    
    pinMode(IrLED, OUTPUT); digitalWrite(IrLED, LOW);
    pinMode(RedLED, OUTPUT); digitalWrite(RedLED, LOW);
    
    LCDprint("  [OK]    ");

    
}

/* --------------------------------------------------------- */

void initDigitalPins(void){
    
    // init buttons as inputs and INT
    
    LCDprint("Init Digital Pins");
    
    pinMode(Left_Arrow_button, INPUT);
    pinMode(Select_OK_button, INPUT);
    pinMode(Right_Arrow_button, INPUT);
    
    // "turn on" the internal pullup resistors
    digitalWrite(Left_Arrow_button, HIGH);
    digitalWrite(Select_OK_button, HIGH);
    digitalWrite(Right_Arrow_button, HIGH);
    
    // the following pins are used by the thermocouple
    // to read in a grey code like temperature
    
    pinMode(VCC, OUTPUT); digitalWrite(VCC, HIGH);
    pinMode(GND, OUTPUT); digitalWrite(GND, LOW);
    
    pinMode(PulseOx, INPUT);
    
    LCDprint("  [OK]    ");
    
}

/* --------------------------------------------------------- */


void initSensors(void){
    int sensorVoltageReading = 0;
    
    LCDprint("Init Digital Pins");

    sensorVoltageReading = DigitalRead(Check_Sensors);
    
    if(sensorVoltageReading == HIGH){
        LCDprint("  [OK]    "); 
    }
    else{
        return;
    }
}
