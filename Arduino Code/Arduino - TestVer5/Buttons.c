//
//  Buttons.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-02.
//  Copyright 2012 carleton university. All rights reserved.
//

/* --------------------------------------------------------- */

void test_buttons(void){
    // middle + left = 
    if(MIDDLE_BUTTON_PRESSED && LEFT_BUTTON_PRESSED){
        viewSignalStrenght();
    }
    // middle + right = 
    else if(MIDDLE_BUTTON_PRESSED && RIGHT_BUTTON_PRESSED){
        viewBatteryLevels();
    }
    // left + right = 
    else if(LEFT_BUTTON_PRESSED && RIGHT_BUTTON_PRESSED){

    }
    // left is cycle through active screen
    else if(LEFT_BUTTON_PRESSED){
        
        // back to real time 
        
    }
    // right is cycle through brightness settings
    else if(RIGHT_BUTTON_PRESSED){
        
        // credits

    }
    // middle is go into menu
    else if(MIDDLE_BUTTON_PRESSED){
        
        // config 

    }
    
    // reset buttons state
    if(buttonState!=buttonsUp){
        buttonState = buttonsUp;
    }
}
/* --------------------------------------------------------- */
/* --------------------------------------------------------- */
/* --------------------------------------------------------- */

