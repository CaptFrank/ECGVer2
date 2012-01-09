//
//  ***** COMPLETE *****
//
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

  HOSTUSB.print("CLF TempData");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  HOSTUSB.print("CLF Vitals");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  HOSTUSB.print("CLF Others");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  HOSTUSB.print("CLF System");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".txt");
  HOSTUSB.print(13, BYTE);
  delay(100);

  HOSTUSB.print("CLF Acknowledge");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".txt");
  HOSTUSB.print(13, BYTE);
  delay(100);

  goToLine(1);
  LCDprint("Files Closed");
  delay(1000);
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
  // to print the titles of the files, and the folders

  // make dir;
  // ‘MKD’<sp><name><cr>

  HOSTUSB.print("MKD ");
  HOSTUSB.print(SessionFolder);
  HOSTUSB.print(SessionID);
  HOSTUSB.print(13, BYTE);
  delay(100);

  HOSTUSB.print("CD ");
  HOSTUSB.print(SessionFolder);
  HOSTUSB.print(SessionID);
  HOSTUSB.print(13, BYTE);
  delay(100);

  // command for USB FTDI: OTW<sp>NAME<cr>
  // Creating files

  HOSTUSB.print("OPW TempData");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  HOSTUSB.print("OPW Vitals");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  HOSTUSB.print("OPW Others");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  HOSTUSB.print("OPW System");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".txt");
  HOSTUSB.print(13, BYTE);
  delay(100);

  HOSTUSB.print("OPW Acknowledge");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".txt");
  HOSTUSB.print(13, BYTE);
  delay(100);

  // sending through USB the new File System
  goToLine(1);
  LCDprint("New files opened");
  delay(1000);

}

/* --------------------------------------------------------- */

void deleteFiles(void){

  // delete the specific files written in the root directory

  // command for FTDI : DLF<sp>NAME<cr>
  // deleting files

  HOSTUSB.print("DLF TempData");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  HOSTUSB.print("DLF Vitals");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  HOSTUSB.print("DLF Others");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  HOSTUSB.print("DLF System");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".txt");
  HOSTUSB.print(13, BYTE);
  delay(100);

  HOSTUSB.print("DLF Acknowledge");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".txt");
  HOSTUSB.print(13, BYTE);
  delay(100);

  // go back to root
  HOSTUSB.print("CD ..");
  HOSTUSB.print(13, BYTE);
  delay(100);

  // delete dir
  HOSTUSB.print("DLD "+SessionFolder);
  HOSTUSB.print(13, BYTE);
  delay(100);

  // sending through USB the new File System
  goToLine(1);
  LCDprint("Files/Dir Deleted");
  delay(1000);

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
  BYTE incomingBYTE;

  while(HOSTUSB.available()>0){
    // read the RX buffer
    incomingBYTE = HOSTUSB.read();
    // if the incoming value is 13 printline
    if(incomingBYTE == 13) {
    }
    LCDprintChar((char)incomingBYTE);
  }
}

/* --------------------------------------------------------- */

void printHeaders(void){

  // print the headers for the CSV files

  // 1. open the file, 
  // 2. send the print command
  // 3. send the length 
  // 4. send data to be written
  // 5. close the file

  // ========== Temperature File =============

  //1.
  HOSTUSB.print("OPW TempData");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  //2.
  HOSTUSB.print("WRF ");

  //3.
  HOSTUSB.print(TempHeader.length());
  HOSTUSB.print(13, BYTE);

  //4.
  HOSTUSB.print(TempHeader);
  HOSTUSB.print(13, BYTE);

  //6.
  HOSTUSB.print("CLF TempData");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  // ========== Vital Signs File =============

  //1.
  HOSTUSB.print("OPW Vitals");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  //2.
  HOSTUSB.print("WRF ");

  //3.
  HOSTUSB.print(VitalsHeader.length());
  HOSTUSB.print(13, BYTE);

  //4.
  HOSTUSB.print(VitalsHeader);
  HOSTUSB.print(13, BYTE);

  //5.
  HOSTUSB.print("CLF Vitals");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  // ========== Other Parameters File =============

  //1.
  HOSTUSB.print("OPW Others");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  //2.
  HOSTUSB.print("WRF ");

  //3.
  HOSTUSB.print(OthersHeader.length());
  HOSTUSB.print(13, BYTE);

  //4.
  HOSTUSB.print(OthersHeader);
  HOSTUSB.print(13, BYTE);

  //5.
  HOSTUSB.print("CLF Others");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  goToLine(1);
  LCDprint("Headers Printed!");
  delay(1000);

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

  // SEND print COMMAND
  HOSTUSB.print("WRF ");

  // SEND THE LENGTH OF THE STRING
  StartTime = millis();

  HOSTUSB.print(ACK.length());
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

  String buffer, printString;
  while(HOSTUSB.available() > 0){
    buffer = buffer + HOSTUSB.read();
  }

  printString = "This is the system file. It is used to allow for\n"
    "Debugging perposes. It shows the follwing:\n"
    "\t-> firmware version: "+ buffer + "\n\n";

  HOSTUSB.print("WRF ");
  HOSTUSB.print(printString.length());
  HOSTUSB.print(13, BYTE);

  // print
  HOSTUSB.print(printString);
  HOSTUSB.print(13, BYTE);
  delay(100);

  // ========== free space =============

  //get
  HOSTUSB.print("FSE");
  HOSTUSB.print(13, BYTE);

  buffer = NULL;
  printString =NULL;

  while(HOSTUSB.available() > 0){
    buffer = buffer + HOSTUSB.read();
  }

  printString = "\t-> free space on USB: " + buffer + "\n\n";

  HOSTUSB.print("WRF ");
  HOSTUSB.print(printString.length());
  HOSTUSB.print(13, BYTE);

  // print
  HOSTUSB.print(printString);
  HOSTUSB.print(13, BYTE);
  delay(100);

  // ========== current directory =============

  // get
  HOSTUSB.print("DIR");
  HOSTUSB.print(13, BYTE);

  buffer = NULL;
  printString =NULL;

  while(HOSTUSB.available() > 0){
    buffer = buffer + HOSTUSB.read();
  }

  printString = "\t-> Current Directory: " + buffer + "\n\n";

  HOSTUSB.print("WRF ");
  HOSTUSB.print(printString.length());
  HOSTUSB.print(13, BYTE);

  // print
  HOSTUSB.print(printString);
  HOSTUSB.print(13, BYTE);
  delay(100);

  // ========== device information =============

  //get
  HOSTUSB.print("IDDE");
  HOSTUSB.print(13, BYTE);

  buffer = NULL;
  printString =NULL;

  while(HOSTUSB.available() > 0){
    buffer = buffer + HOSTUSB.read();
  }

  printString = "\t-> Additionnal Info: \n" + buffer + "\n\n" +
    "*********************************************\n" +
    "This file is for debugging purposes only and\n" +
    "should not be taken as the end all of all.\n" +
    "*********************************************\n" +
    "This process took approximetly: " + millis() + "\n";

  HOSTUSB.print("WRF ");
  HOSTUSB.print(printString.length());
  HOSTUSB.print(13, BYTE);

  // print
  HOSTUSB.print(printString);
  HOSTUSB.print(13, BYTE);
  delay(100);

  // LCD ACK of printing done!
  goToLine(1);
  LCDprint("System/ACK printed!!!");
  delay(1000);

}

/* --------------------------------------------------------- */

void FillUSBBuffers(void){

  // fill buffers with values

  // generate a BuffersFull flag when the buffers are full
  // and need to be written to the USB Stick...
  // WE are using the BLOCK memory mode this way and less
  // time is taken to print to the files

  if(logEntryTemp.length() == 140 || logEntryVitals.length() == 260||
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
    logEntryOthers += tempECGBat;
    logEntryOthers += ",";
    logEntryOthers += tempLight;
    logEntryOthers += "\n";

    //creating Vital data record
    logEntryVitals += millis();
    logEntryVitals += ",";
    logEntryVitals += tempECG;
    logEntryVitals += ",";
    logEntryVitals += ECGPulseTemp ;
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

void printUSBBUffer(void){

  // print the buffers for the CSV files

  // 1. open the file, 
  // 2. send the print command
  // 3. send the length 
  // 4. send data to be written
  // 5. close the file

  // ========== Temperature File =============

  //1.
  HOSTUSB.print("OPW TempData");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  //2.
  HOSTUSB.print("WRF ");

  //3.
  HOSTUSB.print(logEntryTemp.length());
  HOSTUSB.print(13, BYTE);

  //4.
  HOSTUSB.print(logEntryTemp);
  HOSTUSB.print(13, BYTE);

  //6.
  HOSTUSB.print("CLF TempData");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  // ========== Vital Signs File =============

  //1.
  HOSTUSB.print("OPW Vitals");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  //2.
  HOSTUSB.print("WRF ");

  //3.
  HOSTUSB.print(logEntryVitals.length());
  HOSTUSB.print(13, BYTE);

  //4.
  HOSTUSB.print(logEntryVitals);
  HOSTUSB.print(13, BYTE);

  //5.
  HOSTUSB.print("CLF Vitals");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  // ========== Other Parameters File =============

  //1.
  HOSTUSB.print("OPW Others");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

  //2.
  HOSTUSB.print("WRF ");

  //3.
  HOSTUSB.print(logEntryOthers.length());
  HOSTUSB.print(13, BYTE);

  //4.
  HOSTUSB.print(logEntryOthers);
  HOSTUSB.print(13, BYTE);

  //5.
  HOSTUSB.print("CLF Others");
  HOSTUSB.print(SessionID);
  HOSTUSB.print(".CSV");
  HOSTUSB.print(13, BYTE);
  delay(100);

}

/* --------------------------------------------------------- */
/* --------------------------------------------------------- */
/* --------------------------------------------------------- */



