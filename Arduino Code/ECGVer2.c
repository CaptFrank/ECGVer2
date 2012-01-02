//
//  ECGVer2.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//

/* --------------------------------------------------------- */

void setup(){
 
// ----- PRELIMINARY PROCEDURES ------

//    -> init serial Connection to LCD
    
    initLCD();
    LCDprint("***** Starting Up *****");
    delay(100);
    LCDprint("  [OK]    ");

    
// ----- SPLASH SCREEN PROCEDURES ------
    
//    -> splash Screen
//      -> ask for connections 
//      -> Store USB?
    
#ifdef MEGA
    toggleSplashScreen();
    delay(1000);

    askForConnectionTypes();
    askToStoreData();
#endif
    
// ----- DEBUG STARTUP PROCEDURES ------
    
#ifdef DEBUG
    toggleSplashScreen();
    delay(1000);
    
    LCDprint("***** DEBUG MODE *****");
    
    startDebugSequence();
#endif  

// ----- PINS // INT // ISR PROCEDURES ------    
    
    //    -> init buttons
    //    -> init LED pins
    //    -> init Digital pins
    //    -> init Sensors
    
    //    -> attach interrupts
    
#ifdef MEGA
    initbuttons();
#else
    LCDprint("In DEBUG mode no input required");
#endif
    
#ifdef MEGA
    initLEDPins();
    initDigitalPins();
    initSensors();
#else
    LCDprint("No need for inputs random numbers\n
             sent to the PC/XBee.");
#endif
    

// ----- COMMS STARTUP PROCEDURES ------
    
//    -> init Keyboard  
//    -> init serial Connection to XBee
//    -> init serial Connection to PC
//    -> init EEPROM
//      -> +1 to session ID
//      -> Verify Version ID
    
#ifdef XBeeConnected
    initXbee();
    LCDdisplayConnectedIcon(Connection);
#endif

#ifdef USBConnected
    initUSB();
    LCDdisplayConnectedIcon(Connection);
#endif
    
#ifdef StoreUSB
    initVDIP();
    LCDdisplayConnectedIcon(Connection);
#endif

// ----- MEM. & MENUS STARTUP PROCEDURES ------
    
    initEEPROM();
    
//    -> init Menu System
//    -> Startup
    initMenus();
}

/* --------------------------------------------------------- */

void loop(void){
    
    
}

/* --------------------------------------------------------- */

void startDebugSequence(void){
    
    initDebugDialog();
    startDebugSend();
    
    Connection = 'D';
    
}