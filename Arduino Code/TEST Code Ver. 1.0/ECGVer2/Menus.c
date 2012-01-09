//
//  Menus.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-02.
//  Copyright 2012 carleton university. All rights reserved.
//
//  Menu System:
//  
//  -- Init. menu ask for connection type
//      |
//  -- Ask for USB storage
//      |
//  -- Real Time OS Screen (Dialog)
//      --> Invoke a Key
//          --> Submenu 1 - System Comms
//          --> Submenu 2 - Battery Levels
//          --> Submenu 3 - Connection ICONS
//          --> Submenu 4 - Credits
//          --> Submenu 5 - View Heart Beat
//      --> Back to Real Time OS Dialog
//
//


void initMenusThroughMenus(void){
    clearLCD();
    goToLine(1);
    // install the menus in memory
    LCDprint("Menus init(); OK");
    delay(100);
}

/*________________________________________________________________________________*/

void toggleSplashScreen(void){
    clearLCD();
    
    /* Draws a sprite saved in the backpack. x and y sets the upper left corner, 
	 n is the number of the stored sprite, n sets the mode (same modes ad text).
	 sprite 0 is the sparkfun logo, other uploaded sprites will be deleted if power is removed.
	 Example: lcd.drawSprite(10,10,0,7); // Draws the sparkfun logo
	 */
	HOSTLCD.print(0x7C,BYTE);
	HOSTLCD.print(0x0B,BYTE);
	HOSTLCD.print(0x00,BYTE);
	HOSTLCD.print(0x00,BYTE);
	HOSTLCD.print(0x01,BYTE);
	HOSTLCD.print(0x07,BYTE); // override mode
    
    // go to position 1, 7
    goToLine(7);
    HOSTLCD.print("Session ID: " + SessionID);
    
    // go to position 1, 8
    // print Version ID
    goToLine(8);
    HOSTLCD.print("Version ID: " + VersionID);
    
    // print the sprite, the version ID and the session ID
    // Also print the authors and the company name
    
}

/*________________________________________________________________________________*/

void toggleDEBUGSplashScreen(void){
    clearLCD();
    // go to position 1, 4
    // print 'DEBUG MODE'
    goToLine(4);    
    HOSTLCD.print("DEBUG MODE ENABLED");
}

/*________________________________________________________________________________*/

void viewBatteryLevels(void){
  char Buffer[11];
  PString printable_string(Buffer, sizeof(Buffer));  
  clearLCD();
    
    // display only battery voltage
    goToLine(2);
    LCDprint("Battery Voltages:");
    
    do{
        
        goToLine(3);
        printable_string = "- Board: ";
        printable_string += tempBat;
        printable_string += "V";
        
        LCDprintConst(printable_string);
        
        goToLine(4);
        printable_string = "- ECG: ";
        printable_string += tempECGBat;
        printable_string += "V";
        
        LCDprintConst(printable_string);
        
        if(LEFT_BUTTON_PRESSED){
            break;
        }
        
        #ifdef ConnectedUSB
        // Echo data from the VDIP back to the host if conected to a PC
        processVdipBuffer();
        #endif
        
        // test buttons
        test_buttons();
        
        sendSensorValues();
        
        #ifdef EnableLogging
        FillUSBBuffers();
        
        if(BuffersFull == 1){
            printUSBBUffer();  
        }   
        #endif
        
    }while(1);
}

/*________________________________________________________________________________*/

void viewHeartBeat(void){
    clearLCD();

    // display the signal strenght ICONS
    
    do{
        if(pulse == 0){
            clearLCD();
            
            //p1 = (44, 22)
            //p2 = (44, 42)
            //p3 = (84, 22)
            //p4 = (82, 42)
            
            
            // p1-------------p3
            //  |              |
            //  |   NO FILL    |
            //  |              |
            //  |              |
            // p2-------------p4
            
            //draw the above box
            drawBox(44, 22, 82, 42, 0);
        }else if( pulse == 0){
            clearLCD();
            
            //p1 = (44, 22)
            //p2 = (44, 42)
            //p3 = (84, 22)
            //p4 = (82, 42)
            
            
            // p1-------------p3
            //  |              |
            //  |    FILL      |
            //  |              |
            //  |              |
            // p2-------------p4
            
            // draw the above filled box
            drawFilledBox(44, 22, 82, 42, 0xFF); 
        }
        
        if(LEFT_BUTTON_PRESSED){
            break;
        }
        
        #ifdef ConnectedUSB
        // Echo data from the VDIP back to the host if conected to a PC
        processVdipBuffer();
        #endif
        
        // test buttons
        test_buttons();
        
        sendSensorValues();
        
        #ifdef EnableLogging
        FillUSBBuffers();
        
        if(BuffersFull == 1){
            printUSBBUffer();  
        }   
        #endif
    }while(1);
}

/*________________________________________________________________________________*/

void showSystemCom(void){
    
    clearLCD();
    
    // Show the Comms On the system that are activated
    goToLine(2);
    LCDprint("Comms Init():");
    
    do{
        
        // display special characters for:
        // -> Xbee 'X'
        // -> PC 'P'
        // -> Debug 'D'
        // -> Storage 'S'
        // case statement
        
        switch (Connection) {
            case 'X':
                goToLine(3);
                LCDprint("-> XBee");
                break;
            case 'P':
                goToLine(3);
                LCDprint("-> PC-USB");
                break;
                
            default:
                goToLine(3);
                LCDprint("          ");
                break;
        }
        switch (Store) {
            case 'S':
                goToLine(4);
                LCDprint("-> Recording to USB");
                break;
            default:
                goToLine(4);
                LCDprint("-> Not Recording");
                break;
        } 
        
        if(LEFT_BUTTON_PRESSED){
            break;
        }
        
        #ifdef ConnectedUSB
        // Echo data from the VDIP back to the host if conected to a PC
        processVdipBuffer();
        #endif
        
        // test buttons
        test_buttons();
        
        sendSensorValues();
        
        #ifdef EnableLogging
        FillUSBBuffers();
        
        if(BuffersFull == 1){
            printUSBBUffer();  
        }   
        #endif
        
    }while(1);
    
}

/*________________________________________________________________________________*/

void showCredits(void){
    clearLCD();
    // go to position 1, 1
    // print 'Credits:'
    goToLine(1);
    LCDprint("Credits: ");
    
    goToLine(2);
    LCDprint("-Francis Papienau");
    
    goToLine(3);
    LCDprint("-Thai Nguyen");
}


