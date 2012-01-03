//
//  ******* COMPLETE *******
//
//  EEPROM.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//

/* --------------------------------------------------------- */

int EEPROMcheckRevision(void){
    
    // Read the revision number
    // and return it
    return EEPROM.read(0x01);
}


/* --------------------------------------------------------- */

int EEPROMcheckSessionID(void){
    
    // Read the session id
    // and return it
    return EEPROM.read(0x03);
}

/* --------------------------------------------------------- */

void EEPROMwriteRevision(int version){
    
    // go to address 0x01 in EEPROM
    // and write the new version number
    // defined in this program
    
    EEPROM.write(0x01, version);
}

/* --------------------------------------------------------- */

void EEPROMWriteSessionID(int session){
    
    // go to address 0x03 in EEPROM
    // and write the new session ID
    // if the system is not in DEBUG mode
    // this value is defined in this program
    
    EEPROM.write(0x03, session);
}

/* --------------------------------------------------------- */


/* --------------------------------------------------------- */


/* --------------------------------------------------------- */

