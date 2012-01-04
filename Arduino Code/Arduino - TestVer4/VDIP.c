//
//  ***** COMPLETE *****
//  VDIP.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//
//  A couple of USB Interface functions that print to the USB
//  directly. The follwoing file system is put in place to
//  arganize the files into a system.
//
//  FileSystem:
//      -> Folder#session (From EEPROM)
//          -> TempData.csv 
//          -> Vitals.csv
//          -> Others.csv
//          -> System.txt
//          -> Acknowledge.txt

/* --------------------------------------------------------- */

void closeAllFiles(void){

    // Close all files for writting
    
    // command for USB FTDI: CLF<sp>NAME<cr>
    
    HOSTUSB.print("CLF TempData"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    HOSTUSB.print("CLF Vitals"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);

    HOSTUSB.print("CLF Others"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);

    HOSTUSB.print("CLF System"+SessionID+".txt");
    HOSTUSB.print(13, BYTE);
    delay(100);

    HOSTUSB.print("CLF Acknowledge"+SessionID+".txt");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    LCDprintln("Files Closed");
    
}

/* --------------------------------------------------------- */

void putInSuspendMode(void){
    
    // Put in suspend mode to save power
    HOSTUSB.print("SUD");
    HOSTUSB.print(13, BYTE);
    delay(100);
}

/* --------------------------------------------------------- */

void openNewFiles(void){
    
    // open new files to store values in. Using the EEPROM
    // to write the titles of the files, and the folders
    
    // make dir;
    // ‘MKD’<sp> <name><cr>
    
    HOSTUSB.print("MKD " + SessionFolder);
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    HOSTUSB.print("CD " + SessionFolder);
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    // command for USB FTDI: OTW<sp>NAME<cr>
    // Creating files
    
    HOSTUSB.print("OPW TempData"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    HOSTUSB.print("OPW Vitals"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    HOSTUSB.print("OPW Others"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    HOSTUSB.print("OPW System"+SessionID+".txt");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    HOSTUSB.print("OPW Acknowledge"+SessionID+".txt");
    HOSTUSB.print(13, BYTE);
    dealy(100);
    
    // sending through USB the new File System
    
    LCDprintln("New files opened in the New Folder");
    
}

/* --------------------------------------------------------- */

void deleteFiles(void){
    
    // delete the specific files written in the root directory
    
    // command for FTDI : DLF<sp>NAME<cr>
    // deleting files
    
    HOSTUSB.print("DLF TempData"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    HOSTUSB.print("DLF Vitals"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    HOSTUSB.print("DLF Others"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    HOSTUSB.print("DLF System"+SessionID+".txt");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    HOSTUSB.print("DLF Acknowledge"+SessionID+".txt");
    HOSTUSB.print(13, BYTE);
    dealy(100);
    
    // go back to root
    HOSTUSB.print("CD ..");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    // delete dir
    HOSTUSB.print("DLD "+SessionFolder);
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    // sending through USB the new File System
    
    LCDprintln("Files and Directory Deleted");
    
}

/* --------------------------------------------------------- */

void setToASCIIMode(void){
    
    // Sets the VDIP to ASCII mode
    
    HOSTUSB.print("IPA");  
    HOSTUSB.print(13, BYTE);
    delay(100);
}

/* --------------------------------------------------------- */

void processVdipBuffer(){
    
    // echo what is going on on the screen
    byte incomingByte;
    
    while(HOSTUSB.available()>0){
        // read the RX buffer
        incomingByte = HOSTUSB.read();
        // if the incoming value is 13 printline
        if(incomingByte == 13) {
            LCDprintln(NULL);
        }
        LCDprint(incomingByte);
    }
}

/* --------------------------------------------------------- */

void printHeaders(void){
    
    // print the headers for the CSV files
    
    // 1. open the file, 
    // 2. send the write command
    // 3. send the length 
    // 4. send data to be written
    // 5. close the file
    
    // ========== Temperature File =============
   
    //1.
    HOSTUSB.print("OPW TempData"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    //2.
    HOSTUSB.print("WRF ");
    
    //3.
    HOSTUSB.print(TempHeader.lenghth());
    HOSTUSB.print(13, BYTE);
    
    //4.
    HOSTUSB.print(TempHeader);
    HOSTUSB.print(13, BYTE);
    
    //6.
    HOSTUSB.print("CLF TempData"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    // ========== Vital Signs File =============
    
    //1.
    HOSTUSB.print("OPW Vitals"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    //2.
    HOSTUSB.print("WRF ");
    
    //3.
    HOSTUSB.print(VitalsHeader.lenghth());
    HOSTUSB.print(13, BYTE);
    
    //4.
    HOSTUSB.print(VitalsHeader);
    HOSTUSB.print(13, BYTE);
    
    //5.
    HOSTUSB.print("CLF Vitals"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    // ========== Other Parameters File =============

    //1.
    HOSTUSB.print("OPW Others"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    //2.
    HOSTUSB.print("WRF ");

    //3.
    HOSTUSB.print(OthersHeader.lenghth());
    HOSTUSB.print(13, BYTE);
    
    //4.
    HOSTUSB.print(OthersHeader);
    HOSTUSB.print(13, BYTE);
    
    //5.
    HOSTUSB.print("CLF Others"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    LCDprintln("Headers Printed!");
    
}

/* --------------------------------------------------------- */

void printACK_Sys_files(void){
    
    // ========== Print ACK FILE =============
    
    // print an acknoledgment that the system is OK
    // and running with no issues.
    
    // OPEN ACK FILE
    HOSTUSB.print("OPW Acknowledge.txt");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    // SEND WRITE COMMAND
    HOSTUSB.print("WRF ");
    
    // SEND THE LENGTH OF THE STRING
    HOSTUSB.print(ACK.lenghth());
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    // SEND DATA
    HOSTUSB.print(ACK);
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    // CLOSE FILE
    HOSTUSB.print("CLF Acknowledge.txt");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    // ========== Print SYSTEM INFO File =============

    // Print the system file with:
    //  -> Fimware Ver.
    //  -> Drive Info
    //  -> Drive Info Extended
    //  -> Free Mem.
    //  -> Current DIR
    
    HOSTUSB.print("OPW System.txt");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    // ========== frimware version =============
    
    //get
    HOSTUSB.print("FWV");
    HOSTUSB.print(13, BYTE);
    
    string buffer, writeString;
    while(HOSTUSB.available() > 0){
        buffer = buffer + HOSTUSB.read();
    }
    
    writeString = "This is the system file. It is used to allow for\n
                    Debugging perposes. It shows the follwing:\n
                    \t-> firmware version: "+ buffer + "\n\n";

    HOSTUSB.print("WRF ");
    HOSTUSB.print(writestring.length());
    HOSTUSB.print(13, BYTE);
    
    // write
    HOSTUSB.print(writeString);
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    // ========== free space =============
    
    //get
    HOSTUSB.print("FSE");
    HOSTUSB.print(13, BYTE);
    
    buffer = NULL;
    writeString =NULL;
    
    while(HOSTUSB.available() > 0){
        buffer = buffer + HOSTUSB.read();
    }

    writeString = "\t-> free space on USB: " + buffer + "\n\n";
    
    HOSTUSB.print("WRF ");
    HOSTUSB.print(writestring.length());
    HOSTUSB.print(13, BYTE);
    
    // write
    HOSTUSB.print(writeString);
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    // ========== current directory =============
    
    // get
    HOSTUSB.print("DIR");
    HOSTUSB.print(13, BYTE);
    
    buffer = NULL;
    writeString =NULL;
    
    while(HOSTUSB.available() > 0){
        buffer = buffer + HOSTUSB.read();
    }
    
    writeString = "\t-> Current Directory: " + buffer + "\n\n";
    
    HOSTUSB.print("WRF ");
    HOSTUSB.print(writestring.length());
    HOSTUSB.print(13, BYTE);
    
    // write
    HOSTUSB.print(writeString);
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    // ========== device information =============
    
    //get
    HOSTUSB.print("IDDE");
    HOSTUSB.print(13, BYTE);
    
    buffer = NULL;
    writeString =NULL;
    
    while(HOSTUSB.available() > 0){
        buffer = buffer + HOSTUSB.read();
    }
    
    writeString = "\t-> Additionnal Info: \n" + buffer + "\n\n 
                    *********************************************\n
                    This file is for debugging purposes only and\n
                    should not be taken as the end all of all.\n
                    *********************************************\n
                    This process took approximetly: " + millis() + "\n";
    
    HOSTUSB.print("WRF ");
    HOSTUSB.print(writestring.length());
    HOSTUSB.print(13, BYTE);
    
    // write
    HOSTUSB.print(writeString);
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    // LCD ACK of printing done!
    LCDprintln("System and ACK msgs printed!!!");
    
}

/* --------------------------------------------------------- */

void FillUSBBuffers(void){
    
    // fill buffers with values
    
    // generate a BuffersFull flag when the buffers are full
    // and need to be written to the USB Stick...
    // WE are using the BLOCK memory mode this way and less
    // time is taken to write to the files
    
    if(logEntryTemp.length() == 140 || logEntryVitals.lenght() == 220||
       logEntryOthers.length() == 100){
        BuffersFull = 1;
    }
    
    if(BuffersFull == 0){
        
        // Creating the Temperature record
        logEntryTemp += millis();
        logEntryTemp += ",";
        logEntryTemp += temp;
        logEntryTemp += ",";
        logEntryTemp += AmbientTemp;
        logEntryTemp += ",";
        logEntryTemp += (AmbientTemp - temp);
        logEntryTemp += "\n";
        
        //creating the other system data record
        logEntryOthers += millis();
        logEntryOthers += ",";
        logEntryOthers += tempBat;
        logEntryOthers += ",";
        logEntryOthers += tempLight;
        logEntryOthers += "\n";
        
        //creating Vital data record
        logEntryVitals += millis();
        logEntryVitals += ",";
        logEntryVitals += tempECG;
        logEntryVitals += ",";
        logEntryVitals += tempRed;
        logEntryVitals += ",";
        logEntryVitals += tempIr;
        logEntryVitals += ",";
        logEntryVitals += tempError;
        logEntryVitals += ",";
        logEntryVitals += tempRESP;
        logEntryVitals += "\n";
        
        // DONE CREATING ONE BUFFER CYCLE
        // THIS Procedure will go and fill the buffers
        // 20 times before dumping them in the USB.
        
    }
    else{
        //Start Over
        logEntryVitals = NULL;
        logEntryTemp = NULL;
        logEntryOthers = NULL;
    } 
}

/* --------------------------------------------------------- */

void writeUSBBUffer(void){
    
    // print the buffers for the CSV files
    
    // 1. open the file, 
    // 2. send the write command
    // 3. send the length 
    // 4. send data to be written
    // 5. close the file
    
    // ========== Temperature File =============
    
    //1.
    HOSTUSB.print("OPW TempData"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    //2.
    HOSTUSB.print("WRF ");
    
    //3.
    HOSTUSB.print(logEntryTemp.lenghth());
    HOSTUSB.print(13, BYTE);
    
    //4.
    HOSTUSB.print(logEntryTemp);
    HOSTUSB.print(13, BYTE);
    
    //6.
    HOSTUSB.print("CLF TempData"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    // ========== Vital Signs File =============
    
    //1.
    HOSTUSB.print("OPW Vitals"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    //2.
    HOSTUSB.print("WRF ");
    
    //3.
    HOSTUSB.print(logEntryVitals.lenghth());
    HOSTUSB.print(13, BYTE);
    
    //4.
    HOSTUSB.print(logEntryVitals);
    HOSTUSB.print(13, BYTE);
    
    //5.
    HOSTUSB.print("CLF Vitals"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    // ========== Other Parameters File =============
    
    //1.
    HOSTUSB.print("OPW Others"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
    //2.
    HOSTUSB.print("WRF ");
    
    //3.
    HOSTUSB.print(logEntryOthers.lenghth());
    HOSTUSB.print(13, BYTE);
    
    //4.
    HOSTUSB.print(logEntryOthers);
    HOSTUSB.print(13, BYTE);
    
    //5.
    HOSTUSB.print("CLF Others"+SessionID+".CSV");
    HOSTUSB.print(13, BYTE);
    delay(100);
    
}

/* --------------------------------------------------------- */
/* --------------------------------------------------------- */
/* --------------------------------------------------------- */

