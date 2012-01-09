//
//  **** COMPLETE *****
//
//  Init.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//
//  This is used as a initialization function set for the Arduino
//  in order for the I/O and the LCDs and storage to work these 
//  functions must be ran no more than one time.
//
//


/* --------------------------------------------------------- */

void initLCD(void){
    
    /* Uploads a sprite to the backpack, data must be 32 BYTEs long. 8 sprites can be stored (0-7).
    The sparkfun logo is number 0, can be overwritten but reverts when power is removed. 
    All uploaded sprites will be erased upon removal of power
    Consult with firmware README for more info
     Example: BYTE logo[] = {
         0x80,0xc0,0x40,0x0c,0x3e,0xfe,0xf2,0xe0,0xf0,0xe0,
         0xff,0x7f,0x3f,0x1f,0x1f,0x1f,0x1f,0x0f,0x07,0x03,
         0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
         0x00,0x00};
     lcd.uploadSprite(7,10,16,logo); // Uploads the sparkfun logo as sprite number 7
    */
    
        Serial1.print(0x7C,BYTE);
        Serial1.print(0x0D,BYTE);
        Serial1.print(0x01,BYTE);
        Serial1.print(0x80,BYTE);
        Serial1.print(0x40,BYTE);;
        for(int x = 0; x < 32;x++)
        {
            Serial1.print(Sprite[x],BYTE);
        }

    // Start The Serial Connection
    HOSTLCD.begin(HOSTLCD_BAUD_Rate);
    // Wait for connection to establish
    delay(1000);
}

/* --------------------------------------------------------- */

void initXBee(void){
    clearLCD();
    goToLine(1);
    LCDprint("** INIT XBEE Rx/Tx **");
    // Start The Serial Connection
    HOSTXbee.begin(HOSTXbee_BAUD_Rate);
    // Wait for connection to establish
    delay(100);
    
    goToLine(2);
    LCDprint("   [OK]    ");
    
    Connection = 'X';
    delay(1000);
}

/* --------------------------------------------------------- */

void initVDIP(void){
    clearLCD();
    
    goToLine(1);
    LCDprint("** INIT VDIP Rx/Tx **");
    
    // set to default BAUD Rate (9600)
    HOSTUSB.begin(SLOW_HOSTUSB_BAUD_Rate);
    
    // set Baud RATE at 115200
    HOSTUSB.print("SBD ");
    HOSTUSB.print(0x1A, BYTE);
    HOSTUSB.print(0x00, BYTE);
    HOSTUSB.print(0x00, BYTE);
    
    // stop the serial connection at 9600
    HOSTUSB.end();
    
    // Start The Serial Connection at 115200
    HOSTUSB.begin(FAST_HOSTUSB_BAUD_Rate);
    // Wait for connection to establish
    delay(100); 
    
    goToLine(2);
    LCDprint("   [OK]    ");
    
    Store = 'S';
    delay(1000);

}

/* --------------------------------------------------------- */

void initUSB(void){
    clearLCD();
    
    goToLine(1);
    LCDprint("** INIT PC/USB Rx/Tx **");
    // Start The Serial Connection
    HOSTXbee.begin(HOSTXbee_BAUD_Rate);
    // Wait for connection to establish
    delay(100);
    
    goToLine(2);
    LCDprint("   [OK]    ");
    
    Connection = 'P';
    delay(1000);

}

/* --------------------------------------------------------- */

void initMenus(void){
    
    // Start && Install the Menu system to the Memory
    initMenusThroughMenus();
}

/* --------------------------------------------------------- */

void askForConnectionTypes(void){
    clearLCD();

    // ========== Ouput Selection ===============
    int choice = askforOutput();
        
    if(choice == 1){
        
        goToLine(8);
        LCDprint("Chosen XBEE");
        delay(1000);
            
        // connect to XBee?
        // Warning no connection to PC
            
        #define XBeeConnected
        #define USB
            
    }else if(choice == 2){
        
        goToLine(8);
        LCDprint("Chosen USB-PC");
        delay(1000);
    
        // connect to PC-USB
        // Make sure that they know to be on the D1 
        // select switch in order to send commands,
        // the xbee cannot be transparent, it will only
        // process AT commands preceeded by '+++'
            
        #define USBConnected 
        #define USB
    }
    // else nothing is outputted appart from the recording
    // of the files.
    else{
        goToLine(8);
        LCDprint("Chosen N/A");
        delay(1000);
    }
      
    // ========== Record Selection ===============
    
    int store = askforUSB();
        
    if(store == 1){
        goToLine(7);
        LCDprint("Chosen RECORD");
        delay(1000);
        
        // Store Data?
        #define StoreUSB   
    }else if(store == 0){
        goToLine(7);
        LCDprint("Chosen NO");
        delay(1000);
    }
    delay(100);

}

/* --------------------------------------------------------- */

void initDebugDialog(void){
    clearLCD();
    
    goToLine(1);
    LCDprint("** Init Debug Dialog **");

        // Start a Rx/Tx line from PC to send various types of data
        // and to view the status of the device
    goToLine(2);
    LCDprint("Starting Rx/Tx ");
    
    goToLine(3);
    LCDprint("In DEBUG mode ");
    
    goToLine(4);
    LCDprint("   [OK]    ");
    delay(1000);

}

/* --------------------------------------------------------- */

void initEEPROM(){
    clearLCD();

    goToLine(1);
    LCDprint("** INIT EEPROM **");
    int readVersionID, readSessionID;
    
    // Check the Version ID
    //  If not VersionID -> print the proper ID
    
    readVersionID = EEPROMcheckRevision();
    
    if(readVersionID != VersionID){
        EEPROMprintRevision(VersionID);
    }
    
    // Check the Session ID
    //  If not SessionID or DEBUG -> print the proper ID (usually +1)
    readSessionID = EEPROMcheckSessionID();
    
    if(readSessionID == DeBugSession){
        goToLine(2);
        LCDprint("** DEBUG MODE **");    
    }
    else if(readSessionID != SessionID){
        EEPROMprintSessionID(SessionID);
    }
    goToLine(3);
    LCDprint("   [OK]    ");
    
    delay(1000);
}

/* --------------------------------------------------------- */

void initLEDPins(void){
    clearLCD();
    
    // Setting IR and RED LED Pin modes and original values
    //  -> IR = Output, LOW
    //  -> Red = Output, high
    
    goToLine(1);
    LCDprint("** Init LED **");
    
    pinMode(IrLED, OUTPUT); digitalWrite(IrLED, LOW);
    pinMode(RedLED, OUTPUT); digitalWrite(RedLED, LOW);
    
    goToLine(2);
    LCDprint("  [OK]    ");
    
    delay(1000);

}

/* --------------------------------------------------------- */

void initDigitalPins(void){
    clearLCD();
    
    // init buttons as inputs and INT
    goToLine(1);

    LCDprint("** Init Digi **");
    
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
    
    goToLine(2);
    LCDprint("  [OK]    ");
    delay(1000);

}

/* --------------------------------------------------------- */


void initSensors(void){
    clearLCD();
    
    // check if the sensors have power if so go on 
    // to the mroe interesting stuff
    
    int sensorVoltageReading = 0;
    
    goToLine(1);
    LCDprint("** Init Sensors **");

    sensorVoltageReading = digitalRead(CheckSensors);
    
    if(sensorVoltageReading == HIGH){

        #define SensorsOK
        goToLine(2);
        LCDprint("  [OK]    "); 
        delay(1000);

    }
    else{
        return;
        delay(1000);

    }
}

/* --------------------------------------------------------- */

void initbuttons(void){
    
    clearLCD();
    
    goToLine(1);
    LCDprint("** Init buttons **");
    reset_buttons();
    
    goToLine(2);
    LCDprint("  [OK]    ");
    delay(1000);
}

/* --------------------------------------------------------- */
/* --------------------------------------------------------- */
/* --------------------------------------------------------- */


