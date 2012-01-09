//
//  **** COMPLETE ****
//
//  USB_Host.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//
//  
//

/* --------------------------------------------------------- */

void processTerminalCommands(void){
    clearLCD();
   
    // if the user decided to Store info
    // to the USB drive.
    
    #ifdef StoreUSB
    // Check the logging flag,
    // if the logging flag is 1
    if(LoggingState && !ON){
        LoggingState = 0;
        
        //Stop Logging
        closeAllFiles();
        
        //Print to LCD
        goToLine(1);
        LCDprint("Stop logging");
    }
    
    // if the logging flag is 0
    if(!LoggingState && ON){
        LoggingState = 1;
        
        //Start Logging
        openNewFiles();
        
        //Print to LCD
        goToLine(1);
        LCDprint("Start logging");
    } 
    #endif
    
    #ifdef USB
    
    if(HOSTXbee.available() > 0){
        
        char readChar = HOSTXbee.read();
        
        // Options from Terminal:
        //  1 -> start Logging
        //  2 -> stop Logging
        //  3 -> silent Mode
        //       lights off but logging ON
        //  4 -> display files
        //  5 -> delete files
        //  6 -> directory listing
        //  7 -> suspend the VDIP
        //  8 -> set the VDIP to ASCII mode
        //  else -> Error in the input,
        //  Not a recognized input
        
        if(readChar == '1'){
            
            // Start Logging to USB
            goToLine(1);
            LCDprint("Started Logging");
            LoggingState = 1;
            ON = 1;
            
            openNewFiles();
            goToLine(2);
            LCDprint(">");
            
        }else if(readChar == '2'){
            
            // Stop Logging to USB
            goToLine(1);
            LCDprint("Stopped Logging");
            LoggingState = 0;
            ON = 0;
            
            closeAllFiles();
            
            goToLine(2);
            LCDprint(">");
            
        }else if(readChar == '3'){
            
            // Put in silent mode
            goToLine(1);
            LCDprint("Silent mode");
            turnOffBacklight();
            
            goToLine(2);
            LCDprint(">");
            
        }else if(readChar == '4'){
            
            goToLine(1);
            // Print File System
            LCDprint("Files are written to:");
           
            goToLine(2);
            LCDprint("~\\");        
            
            goToLine(3);
            LCDprint("TempData.CSV");
            
            goToLine(4);
            LCDprint("Vitals.CSV");
            
            goToLine(5);
            LCDprint("Others.CSV");
            
            goToLine(6);
            LCDprint("System.txt");
            
            goToLine(7);
            LCDprint("Acknowledge.txt");
            
            goToLine(8);
            LCDprint(">");
            
        }else if(readChar == '5'){
            
            // Delete files
            goToLine(1);
            LCDprint("Deleting files");
            deleteFiles();
            
            goToLine(2);
            LCDprint(">");
            
        }else if(readChar == '6'){
            
            // Show the directory
            goToLine(1);
            LCDprint("DIR:");
            
            goToLine(2);
            readLineFromVDIP();
            
            goToLine(3);
            LCDprint(">");

        }else if(readChar == '7'){
            
            // Suspend the VDIP
            goToLine(1);
            LCDprint("Suspending:");
            putInSuspendMode();
            
            goToLine(2);
            LCDprint(">");            
            
        }else if(readChar == '8'){

            // Set ASCII mode
            setToASCIIMode();
            
            goToLine(1);
            LCDprint("[OK]");
            
            goToLine(2);
            LCDprint("> ");
            
        }else{
            
            // Print Help Menu
            goToLine(1);
            LCDprint("Unrecognised command '");
            LCDprintChar(readChar);
            LCDprint("'");
            
            delay(1000);
            
            goToLine(1);
            LCDprint("1 - Start logging");
            
            goToLine(2);
            LCDprint("2 - Stop logging");
            
            goToLine(3);
            LCDprint("3 - Silent Mode");
            
            goToLine(4);
            LCDprint("4 - Display Logfiles");
            
            goToLine(5);
            LCDprint("5 - Delete Logfiles");
            
            goToLine(6);
            LCDprint("6 - Directory listing");
            
            goToLine(7);
            LCDprint("7 - Suspend VDIP");
            
            goToLine(8);
            LCDprint("8 - Set to ASCII mode");
            
            delay(1000);
            
            goToLine(1);
            LCDprint("> ");
        }
    }
    #else
    
    // Can't print to Serial since we are using the
    // XBee layer, and we can only send AT Commands.
    // Unless the XBee is in API mode we cannot send
    // Serial Commands directly to the Board...
    
    clearLCD();
    
    goToLine(1);
    LCDprint("***ERROR***");
    #endif
}

/* --------------------------------------------------------- */

void readLineFromVDIP(void){
    
    // Reads the character buffer from the serial line
    int i=0;
    char commandbuffer[21];
    
    if(HOSTUSB.available()){
        delay(100);
        while(HOSTUSB.available() && i < 20) {
            commandbuffer[i++] = HOSTUSB.read();
        }
        commandbuffer[i++]='\0';
    }
    
    if(i>0) // print the data if the buffer is not null
        HOSTLCD.print((char*)commandbuffer);
}

/* --------------------------------------------------------- */
/* --------------------------------------------------------- */
/* --------------------------------------------------------- */

