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
    LCDprintln("***** Starting Up *****");
    delay(100);
    LCDprintln("  [OK]    ");

    
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
    
    LCDprintln("***** DEBUG MODE *****");
    
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
    LCDprintln("In DEBUG mode no input required");
#endif
    
#ifdef MEGA
    initLEDPins();
    initDigitalPins();
    initSensors();
#else
    LCDprintln("No need for inputs random numbers\n
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
    printHeaders();
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
    
#ifdef ConnectedUSB
    // Echo data from the VDIP back to the host if conected to a PC
    processVdipBuffer();
#endif
    
#ifdef EnableLogging
    
    // in this one:
    // ambientTemp, TympTemp, DiffTemp (5 characters -> in 100 we get 20 samples/page)
    
    char vdipBuffer1[100];
    PString logEntryTemp(vdipBuffer1, sizeof(vdipBuffer1)); // Create a PString object called logEntry
    
    // in this one:
    // ECG, SPO2 RAW, SPO2 IR, SPO2 ERROR, RESP (9 characters -> in 180 we get 20 samples/page)
    
    char vdipBuffer2[180];
    PString logEntryVitals(vdipBuffer2, sizeof(vdipBuffer2)); // Create a PString object called logEntry
    
    // in this one:
    // Light, Battery (3 characters -> in 60 we get 20 samples/page)
    
    char vdipBuffer3[60];
    PString logEntryOthers(vdipBuffer3, sizeof(vdipBuffer3)); // Create a PString object called logEntry
    
    char valBuffer[15];  // Buffer for converting numbers to strings before appending to vdipBuffer
#endif
    
    // test buttons
    test_buttons();
    
    sendSensorValues();
    
    FillUSBBuffers();
    
    if(BuffersFull){
        writeUSBBUffer();  
    } 
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
    LCDprintln(" * Attaching powerfail ISR      ");
    attachInterrupt(0, powerFail, FALLING);
    LCDprintln("   [OK]    ");
#endif
 
// ----- ISR #2 STARTUP PROCEDURES ------
    
    // Installing Loggin On/Off ISR
    // NEEDED TO START OR STOP THE LOGGING
    // ON THE VDIP.
    
#ifdef EnableLogging
    LCDprintln(" * Attaching logging ISR        ");
    // Interrupt triggered by pressing "log on/off" button
    attachInterrupt(2, LoggingChange, FALLING);
    LCDprint("  [OK]    ");
#endif
    LCDprintln("Start. Complete!");    
}


// the buttons interrupt
// this is the interrupt handler for button presses
// this has no actual function to call we must use the
// physical layout of the board the hidden interrupt
// vectors to solve the problem

#ifdef MEGA
ISR(PCINT2_vect)
{
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
