//
//  ***** COMPLETE *****
// 
//  Buttons.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-02.
//  Copyright 2012 carleton university. All rights reserved.
//

/* --------------------------------------------------------- */

void test_buttons(void){
#ifdef MEGA
    // middle + right = Battery Levels
    if(MIDDLE_BUTTON_PRESSED && RIGHT_BUTTON_PRESSED){
        showCredits();
    }
    
    // left + right = Reset Board
    else if(LEFT_BUTTON_PRESSED && RIGHT_BUTTON_PRESSED){
        //software reset
        showSystemCom();
    }
    
    // left is go back to real time OS Output
    else if(LEFT_BUTTON_PRESSED){
        // back to real time 
        // goBackToRealTime();
        // break the loop
    }
    
    // right is show Credits
    else if(RIGHT_BUTTON_PRESSED){
        // credits
        viewBatteryLevels();
    }
    
    // middle is go to config menu
    else if(MIDDLE_BUTTON_PRESSED){
        // config
        viewHeartBeat();
    }
    
    // reset buttons state
    if(buttonState!=buttonsUp){
        buttonState = buttonsUp;
    }
#endif
}

void reset_buttons(void){
    buttonState = buttonsUp;
}
/* --------------------------------------------------------- */
/* --------------------------------------------------------- */
/* --------------------------------------------------------- */


