//
//  ******* COMPLETE *******
//
//  PwrFailDetect.pde
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//
//  This is the powerfail ISR attached to DIGITAL Pin 2
//  It closes all files that are currently wirtting 
//  and puts the HOSTUSB device in Suspend mode
//  until the User resets the device
//
//  FileSystem:
//      -> Folder#session (From EEPROM)
//          -> TempData.csv 
//          -> Vitals.csv
//          -> Others.csv
//          -> System.txt
//          -> Acknowledge.txt
//

#ifdef PWRFailDetect

void powerFail(void){
    
#ifdef HOSTLCD
    
    // Turn Off the backlight
    turnOffBacklight();
    
#endif
    
#ifdef HOSTUSB
    
    // Close Files and put in suspend mode
    
    closeAllFiles();
    putInSuspendMode();
#endif
    
}