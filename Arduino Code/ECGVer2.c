//
//  ECGVer2.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//

/* --------------------------------------------------------- */

void setup(){
    
    // A visual Queue that the System is in
    // Setup Mode.
        // Pin 14 -> LED ON
    
    digitalWrite(SetupLED, HIGH);
    
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
    
    attachInterrupts();

    

// ----- COMMS STARTUP PROCEDURES ------
    
//    -> init Keyboard  
//    -> init serial Connection to XBee
//    -> init serial Connection to PC
    
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
    
//    -> init EEPROM
//      -> +1 to session ID
//      -> Verify Version ID
//    -> init Menu System
//    -> Startup
    
    initEEPROM();
    initMenus();
    
    // A visual Queue that the System is now past
    // the Setup Mode.
    // Pin 14 -> LED OFF
    
    digitalWrite(SetupLED, LOW);
}

/* --------------------------------------------------------- */

void loop(void){
    
    // A Visual Queue that the System is in a Rolling State
    // Pin 13 -> Lights up a Status LED
    
    digitalWrite(StartupLED, HIGH);

#ifDEf DEBUG
    if(DEBUGsendRandom == 1){
        sendPseudoRandom();
    }
#endif
    
#ifdef MEGA
    
    // Process any commands from the host Terminal ONLY
    // IF THE BOARD IS CONNETED TO A CPU
    
    processTerminalCommands();
    
    sendSensorValues();
    FillUSBBuffers();
    
#endif
}

/* --------------------------------------------------------- */

void startDebugSequence(void){
    
    initDebugDialog();
    startDebugSend();
    
    Connection = 'D';
    
}

/* --------------------------------------------------------- */

void attachInterrupts(void){

// ----- ISR #1 STARTUP PROCEDURES ------
    
    // Installing Power Supply ISR
    // NEEDED TO DETERMINE IF A POWER
    // FAILURE HAS OCCURED
    
#ifdef PWRFailDetect
    // Interrupt triggered by falling voltage on power supply input
    LCDprint(" * Attaching powerfail ISR      ");
    attachInterrupt(0, powerFail, FALLING);
    LCDprint("   [OK]    ");
#endif
 
// ----- ISR #2 STARTUP PROCEDURES ------
    
    // Installing Loggin On/Off ISR
    // NEEDED TO START OR STOP THE LOGGING
    // ON THE VDIP.
    
#ifdef EnableLogging
    LCDprint(" * Attaching logging ISR        ");
    // Interrupt triggered by pressing "log on/off" button
    attachInterrupt(2, LoggingChange, FALLING);
    LCDprint("  [OK]    ");
#endif
    LCDprint("Start. Complete!");    
}


/* --------------------------------------------------------- */

/* --------------------------------------------------------- */

/* --------------------------------------------------------- */
