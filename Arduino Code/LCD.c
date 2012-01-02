//
//  LCD.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//

void toggleSplashScreen(void){
    
}

void LCDprint(string var){
    
    
}

void LCDdisplayConnectedIcon(int choice){
    
    // display special characters for:
    // -> Xbee 'X'
    // -> PC 'P'
    // -> Debug 'D'
    // -> Storage 'S'
    // case statement
    
}

void turnOffBacklight(void){
    
    // Turn Off the LCD Display
    HOSTLCD.print(0x00);
    HOSTLCD.print(0x02);
}




