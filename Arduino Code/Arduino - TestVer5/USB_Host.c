//
//  **** COMPLETE ****
//
//  USB_Host.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//

/* --------------------------------------------------------- */

void processTerminalCommands(void){
   
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
        LCDprint("Stop logging");
    }
    
    // if the logging flag is 0
    if(!LoggingState && ON){
        loggingState = 1;
        
        //Start Logging
        openNewFiles();
        
        //Print to LCD
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
            LCDprintln("Started Logging");
            LoggingState = 1;
            ON = 1;
            
            openNewFiles();
            LCDprint(">");
            
        }else if(readChar == '2'){
            
            // Stop Logging to USB
            LCDprintln("Stopped Logging");
            LoggingState = 0;
            ON = 0;
            
            closeAllFiles();
            moveOldFilesToOldFolder();
            
            LCDprint(">");
            
        }else if(readChar == '3'){
            
            // Put in silent mode
            LCDprintln("Silent mode");
            turnOffBacklight();
            
            LCDprint(">");
            
        }else if(readChar == '4'){
            
            // Print File System
            LCDprintln("Files are written to:");
            LCDprintln("~\\");
            LCDprintln("TempData.CSV");
            LCDprintln("CLF Vitals.CSV");
            LCDprintln("CLF Others.CSV");
            LCDprintln("CLF System.txt");
            LCDprintln("Acknowledge.txt");
            
            LCDprint(">");
            
        }else if(readChar == '5'){
            
            // Delete files
            LCDprintln("Deleting files");
            deleteFiles();
            LCDprint(">");
            
        }else if(readChar == '6'){
            
            // Show the directory
            LCDprintln("DIR:");
            LCDprintln(readLineFromVDIP());
            LCDprint(">");

        }else if(readCahr == '7'){
            
            // Suspend the VDIP
            LCDprintln("Suspending:");
            putInSuspendMode();
            LCDprint(">");            
            
        }else if(readChar == '8'){

            // Set ASCII mode
            setToASCIIMode();
            LCDprintln("[OK]");
            LCDprint("> ");
            
        }else{
            
            // Print Help Menu
            LCDprint("Unrecognised command '");
            LCDprint(readChar);
            LCDprintln("'");
            LCDprintln("1 - Start logging");
            LCDprintln("2 - Stop logging");
            LCDprintln("3 - Silent Mode");
            LCDprintln("4 - Display Logfiles");
            LCDprintln("5 - Delete Logfiles");
            LCDprintln("6 - Directory listing");
            LCDprintln("7 - Suspend VDIP");
            LCDprintln("8 - Set to ASCII mode");
            
            LCDprint("> ");
        }
    }
    #else
    
    // Can't write to Serial since we are using the
    // XBee layer, and we can only send AT Commands.
    // Unless the XBee is in API mode we cannot send
    // Serial Commands directly to the Board...
    
    LCDprintln("***ERROR***");
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
