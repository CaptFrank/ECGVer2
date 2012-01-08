//
//  **** COMPLETE ****
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
    
    goToLine(1);
    LCDprint("***** Starting Up *****");
    delay(100);
    
    goToLine(2);
    LCDprint("  [OK]    ");

    
// ----- SPLASH SCREEN PROCEDURES ------
    
//    -> splash Screen
//      -> ask for connections 
//      -> Store USB?
    
    #ifdef MEGA
    toggleSplashScreen();
    delay(1000);

    askForConnectionTypes();
    #endif
    
// ----- DEBUG STARTUP PROCEDURES ------
    
    #ifdef DEBUG
    toggleDEBUGSplashScreen();
    delay(1000);
    
    clearLCD();
    
    goToLine(1);
    LCDprint("***** DEBUG MODE *****");
    
    printDebugSymbol();
    startDebugSequence();
    #endif  
    
// ----- EEPROM CHECK STARTUP PROCEDURES ------
    
    #ifdef MEGA
    
    // init() the EEPROM Memory
    initEEPROM();
    
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
    goToLine(2);
    LCDprint("In DEBUG mode");
    #endif
    
    #ifdef MEGA
    initLEDPins();
    initDigitalPins();
    initSensors();
    #else
    goToLine(3);
    LCDprint("No inputs rand. num");
    
    goToLine(4);
    LCDprint("sent to the PC/XBee.");
    #endif
    
    attachInterrupts();

    

// ----- COMMS STARTUP PROCEDURES ------
    
//    -> init Keyboard  
//    -> init serial Connection to XBee
//    -> init serial Connection to PC
    
    #ifdef XBeeConnected
    initXbee();
    printXbeeSymbol();
    #endif

    #ifdef USBConnected
    initUSB();
    printPCSymbol();
    #endif
    
    #ifdef StoreUSB
    initVDIP();
    openNewFiles();
    printHeaders();
    printUSBSTORE();
    #endif

// ----- MEM. & MENUS STARTUP PROCEDURES ------

//      -> +1 to session ID
//      -> Verify Version ID
//    -> init Menu System
//    -> Startup
    
    // Print the system summary and the Acknoledgement Signal
    // to show the status of the system before starting
    printACK_Sys_files();
    
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
    
    goToLine(2);
    LCDprint("Running...");
    
    goToLine(3);
    LCDprint("Comms are ok...");
    

    #ifdef DEBUG
    if(DEBUGsendRandom == 1){
        sendPseudoRandom();
    }
    #endif
    
    #ifdef MEGA
    
    // Process any commands from the host Terminal ONLY
    // IF THE BOARD IS CONNETED TO A CPU
    processTerminalCommands();
    
    #ifdef ConnectedUSB
    // Echo data from the VDIP back to the host if conected to a PC
    processVdipBuffer();
    #endif
    
    // test buttons
    test_buttons();
    
    #ifdef XBeeConnected
    sendSensorValues();
    printXbeeSymbol();
    #endif
    
    #ifdef USBConnected
    sendSensorValues();
    printPCSymbol();
    #endif
    
    #ifdef EnableLogging
    FillUSBBuffers();
    
    if(BuffersFull == 1){
        writeUSBBUffer();  
    }   
    #endif
    #endif
    
    #ifdef StoreUSB
        printUSBSTORE();
    #endif
    
    printBattLevel();
}

/* --------------------------------------------------------- */

void startDebugSequence(void){
    
    initDebugDialog();
    startDebugSend();
    Connection = 'D';
    
}

/* --------------------------------------------------------- */

void attachInterrupts(void){
    clearLCD();

// ----- ISR #1 STARTUP PROCEDURES ------
    
    // Installing Power Supply ISR
    // NEEDED TO DETERMINE IF A POWER
    // FAILURE HAS OCCURED
    
    #ifdef PWRFailDetect
    goToLine(1);
    // Interrupt triggered by falling voltage on power supply input
    LCDprint(" * Attaching powerfail ISR      ");
    attachInterrupt(0, powerFail, FALLING);
    
    goToLine(2);
    LCDprintln("   [OK]    ");
    #endif
 
// ----- ISR #2 STARTUP PROCEDURES ------
    
    // Installing Loggin On/Off ISR
    // NEEDED TO START OR STOP THE LOGGING
    // ON THE VDIP.
    
    #ifdef EnableLogging
    goToLine(1);
    LCDprint(" * Attaching logging ISR        ");
    // Interrupt triggered by pressing "log on/off" button
    attachInterrupt(2, LoggingChange, FALLING);
    
    goToLine(2);
    LCDprint("  [OK]    ");
    #endif
    
    goToLine(3);
    LCDprintln("Start. Complete!");    
}


// the buttons interrupt
// this is the interrupt handler for button presses
// this has no actual function to call we must use the
// physical layout of the board the hidden interrupt
// vectors to solve the problem

#ifdef MEGA
ISR(PCINT2_vect){
    static unsigned long last_millis = 0;
    unsigned long m = millis();
    
    if (m - last_millis > 20)
    {
        buttonState |= ~PINK;
    }
    //  else ignore interrupt: probably a bounce problem
    last_millis = m;
}
#endif

/* --------------------------------------------------------- */
/* --------------------------------------------------------- */
/* --------------------------------------------------------- */
