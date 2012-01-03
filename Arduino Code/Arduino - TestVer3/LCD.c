//
//  LCD.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//

/*________________________________________________________________________________*/

void toggleSplashScreen(void){
    
    // print the sprite, the version ID and the session ID
    // Also print the authors and the company name
    
}

/*________________________________________________________________________________*/

void LCDprint(string var){
    
    // print a given string to the LCD
    
}

/*________________________________________________________________________________*/

void LCDprintln(string var){
    
    // print a given string but append a '\n' character
    
}

/*________________________________________________________________________________*/

void LCDdisplayConnectedIcon(int choice){
    
    // display special characters for:
    // -> Xbee 'X'
    // -> PC 'P'
    // -> Debug 'D'
    // -> Storage 'S'
    // case statement
    
}

/*________________________________________________________________________________*/

void turnOffBacklight(void){
    
    // Turn Off the LCD Display
    HOSTLCD.print(0x00);
    HOSTLCD.print(0x02);
}

/*________________________________________________________________________________*/


/*________________________________________________________________________________*/


/*________________________________________________________________________________*/





