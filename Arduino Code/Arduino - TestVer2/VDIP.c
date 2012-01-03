//
//  VDIP.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//

/* --------------------------------------------------------- */

void closeAllFiles(void){

    // Close all files for writting
    
    HOSTUSB.print("CLF TempData.CSV");
    HOSTUSB.print(13, BYTE);
    
    HOSTUSB.print("CLF Vitals.CSV");
    HOSTUSB.print(13, BYTE);
    
    HOSTUSB.print("CLF Others.CSV");
    HOSTUSB.print(13, BYTE);
    
    HOSTUSB.print("CLF System.txt");
    HOSTUSB.print(13, BYTE);
    
    HOSTUSB.print("CLF Acknowledge.txt");
    HOSTUSB.print(13, BYTE);
}

/* --------------------------------------------------------- */

void putInSuspendMode(void){
    
    // Put in suspend mode to save power
    HOSTUSB.print("SUD");
    HOSTUSB.print(13, BYTE);
}

/* --------------------------------------------------------- */

void openNewFiles(void){
    
    // open new files to store values in. Using the EEPROM
    // to write the titles of the files, and the folders
    
}

/* --------------------------------------------------------- */

void moveOldFilesToOldFolder(void){
    
    // move the written files to a folder with the Session ID
    
}

/* --------------------------------------------------------- */

void deleteFiles(void){
    
    // delete the specific files written in the root directory
    
}

/* --------------------------------------------------------- */

void setToASCIIMode(void){
    
    delay(100);
    HOSTUSB.print("IPA");  // Sets the VDIP to ASCII mode
    HOSTUSB.print(13, BYTE);
}

/* --------------------------------------------------------- */

void processVdipBuffer(){
    
    // echo what is going on on the screen
    byte incomingByte;
    
    while(HOSTUSB.available()>0){
        incomingByte = HOSTUSB.read();
        if(incomingByte == 13) {
            LCDprintln(NULL);
        }
        LCDprint(incomingByte);
    }
}

void FillUSBBuffers(void){
    
    // fill buffers with values
    
    // generate a BuffersFull flag when the buffers are full
    // and need to be written to the USB Stick...
    // WE are using the BLOCK memory mode this way and less
    // time is taken to write to the files
    
    
}

void printHeaders(void){
    
    // print the headers for the CSV files
    
}

void printACK_Sys_files(void){
    
    // print an acknoledgment that the system is OK
    // and running with no issues.
    
    // print the system file with:
    //  -> Free memory
    //  -> Memory allocation
    //  -> USB File System
    //  -> USB speed
    //  -> USB DIAGS
    //  -> USB Files and sizes
    
}


/* --------------------------------------------------------- */


/* --------------------------------------------------------- */


/* --------------------------------------------------------- */

