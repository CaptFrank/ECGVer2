//
//  VDIP.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//

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

void putInSuspendMode(void){
    
    // Put in suspend mode to save power
    
    HOSTUSB.print("SUD");
    HOSTUSB.print(13, BYTE);
}