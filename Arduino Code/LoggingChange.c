//
//  LoggingChange.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//

void LoggingChange(void){
#ifdef HOSTUSB
    
    // this changes the State of the logging flag to
    // ~logging flag.
    // if logging flag = 1 -> 0
    // if logging flag = 0 -> 1
    
    // this mitigates the logging on the USB Stick
    
    loggingState = !loggingState;
#endif
}
