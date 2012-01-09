//
//  ****** Verison #1 COMPLETE MUST BE TESTED *******
//  
//
//  LCD.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//
//  A compilation of utilitie functions for writting different
//  things to the 128x64 serial LCD.
//


/*________________________________________________________________________________*/

void LCDprint(char* var){
    
    // print a given string to the LCD
    // print to USB if USBConnected but not when XBeeConnected
    
    HOSTLCD.print(var);
}

/*________________________________________________________________________________*/

void LCDprintConst(const char* var){
    
    // print a given string to the LCD
    // print to USB if USBConnected but not when XBeeConnected
    
    HOSTLCD.print(var);
}
/*________________________________________________________________________________*/

void LCDprintChar(char var){
    
    // print a given string to the LCD
    // print to USB if USBConnected but not when XBeeConnected
    
    HOSTLCD.print(var);
}

/*________________________________________________________________________________*/

void showConnectionICON(void){
    
    // display special characters for:
    // -> Xbee 'X'
    // -> PC 'P'
    // -> Debug 'D'
    // -> Storage 'S'
    // case statement
    
    switch (Connection) {
        case 'X':
            // print the xbe symbol to the lcd
            printXbeeSymbol();
            break;
        case 'P':
            // print the usb symbol
            printPCSymbol();
            break;
        case 'D':
            // print a big d for debug
            printDebugSymbol();
            break;
        default:
            // print nothing
            printNull();
            break;
    }
    switch (Store) {
        case 'S':
            // print the storing icon
            printUSBSTORE();
            break;
        default:
            // print nothing
            printNull();
            break;
    } 
}

/*________________________________________________________________________________*/

void clearLCD(void){
    
    // proprietary clear screen command
    HOSTLCD.print(0x7C,BYTE);
    HOSTLCD.print(0x00,BYTE);
}

/*________________________________________________________________________________*/


void printNull(void){
    
    // Print NULL
    LCDprint(" ");
}

/*________________________________________________________________________________*/

void printPCSymbol(void){
    
    // Print the PC symbol
    goToPosition(117,1);
    LCDprintConst(Connected_PC_Symbol);
}

/*________________________________________________________________________________*/

void printXbeeSymbol(void){
    // Print the XBee symbol
    goToPosition(117,1);
    LCDprintConst(Connected_XBee_Symbol);
}

/*________________________________________________________________________________*/

void printUSBSTORE(void){
    goToPosition(111,1);
    LCDprintConst(USB_Store_Symbol);
}

/*________________________________________________________________________________*/

void printDebugSymbol(void){
    
    // Print the Debug Symbol
    goToPosition(117,1);
    LCDprintConst(Debug);
}

/*________________________________________________________________________________*/

void printBattLevel(void){
    
    // go to x=123, y=1 and print the battery level sprite
    goToPosition(123,1);
    
    if((tempBat/9.0)*100.00 < 10.0){
        LCDprintConst(Batt10);
    }else if((tempBat/9.0)*100.00 >= 10.0 ||(tempBat/9.0)*100.00 <30.0){
        LCDprintConst(Batt30);
    }else if((tempBat/9.0)*100.00 >= 30.0 ||(tempBat/9.0)*100.00 <45.0){
        LCDprintConst(Batt45);
    }else if((tempBat/9.0)*100.00 >= 45.0 ||(tempBat/9.0)*100.00 <60.0){
        LCDprintConst(Batt60);
    }else if((tempBat/9.0)*100.00 >= 60.0 ||(tempBat/9.0)*100.00 <75.0){
        LCDprintConst(Batt75);
    }else if((tempBat/9.0)*100.00 >= 75.0){
        LCDprintConst(FullBatt);  
    }
    
}

/*________________________________________________________________________________*/

void turnOffBacklight(void){
    
    // Turn Off the LCD Display
    HOSTLCD.print(0x7C, BYTE);
    HOSTLCD.print(0x02, BYTE);
    HOSTLCD.print(0x00, BYTE);
}

/*________________________________________________________________________________*/

int askforOutput(void){
    int continueFlag = 0, choice = 0;
    
    clearLCD(); 
    
    // print the prompt
    goToLine(1);
    LCDprint("***************");
    
    goToLine(2);
    LCDprint("What output?");
    
    goToLine(3);
    LCDprint("-> Xbee [Left]");
    
    goToLine(4);
    LCDprint("-> USB  [Right]");
    
    goToLine(5);
    LCDprint("-> N/A  [Center]");
    
    goToLine(6);
    LCDprint("***************");
    
    //resetting the buttons to up position
    reset_buttons();
    
    do{
        // if left is pushed
        if(LEFT_BUTTON_PRESSED){ 
            // XBEE is the choice
            choice = 1;
            continueFlag = 1;
        // if the right is pushed
        }else if(RIGHT_BUTTON_PRESSED){
            // USB Connection is the choice
            choice = 2;
            continueFlag = 1;
        // if the middle is pushed
        }else if(MIDDLE_BUTTON_PRESSED){
            // No output is the choice
            choice = 3;
            continueFlag = 1;
        }
        //do while an input is noticed
    }while(continueFlag == 0);
    
    // reset the buttons again
    reset_buttons();
    
    // return the choice
    return choice;
}

/*________________________________________________________________________________*/

int askforUSB(void){
    int continueFlag = 0, choice = 0;
    
    clearLCD();
    
    // print the prompt
    goToLine(1);
    LCDprint("***************");
    
    goToLine(2);
    LCDprint("Record?");
    
    goToLine(3);
    LCDprint("-> YES  [Left]");
    
    goToLine(4);
    LCDprint("-> NO   [Right]");
    
    goToLine(5);
    LCDprint("***************");
    
    //resetting the buttons to up position
    reset_buttons();
    
    do{
        // if left is pushed
        if(LEFT_BUTTON_PRESSED){ 
            // Yes record
            choice = 1;
            continueFlag = 1;
            // if the right is pushed
        }else if(RIGHT_BUTTON_PRESSED){
            // no do not record
            choice = 0;
            continueFlag = 1;
            // if the middle is pushed
        }
        //do while an input is noticed
    }while(continueFlag == 0);
    
    // reset the buttons again
    reset_buttons();
    
    // return the choice
    return choice;
}

/*________________________________________________________________________________*/

void goToPosition(int x, int y){
    /* Sets the x and y offsets, text written after this command will start from x,y.
	 Example: lcd.gotoPosition(40,40);
	 */
    
    HOSTLCD.print(0x7C,BYTE);
	HOSTLCD.print(0x18,BYTE);
	HOSTLCD.print(x,BYTE);
	HOSTLCD.print(0x7C,BYTE);
	HOSTLCD.print(0x19,BYTE);
	HOSTLCD.print(y,BYTE);
}

/*________________________________________________________________________________*/

void goToLine(int line){
    
    /* Uses the gotoPosition function to select "line" 1-8 on the display. 
	 Text can be written between these lines using gotoPosition. This function makes it simpler.
	 Example: lcd.gotoLine(2);
	 */
	int y;
	if(line > 8) {
		line = 8;
	}
	else if(line < 1) {
		line = 1;
	}
	else {
		y = -8 + line * 8;
		goToPosition(1,y);
	}

}
/*________________________________________________________________________________*/

void drawFilledBox(int x1, int y1, int x2, int y2, BYTE fill)
{	/* Same as drawBox, but accepts a fill BYTE. 0xFF for black, 0x00 for white. 
	 Other values can be used to create patterns (like 0x55). 
	 Example: drawFilledBox(10,10,20,20,0xFF);
	 */
	HOSTLCD.print(0x7C,BYTE);
	HOSTLCD.print(0x12,BYTE);
	HOSTLCD.print(x1,BYTE);
	HOSTLCD.print(y1,BYTE);
	HOSTLCD.print(x2,BYTE);
	HOSTLCD.print(y2,BYTE);
	HOSTLCD.print(fill,BYTE);
	
}

/*________________________________________________________________________________*/

void drawBox(int x1, int y1, int x2, int y2, int z) 
{	/* Draws a rectangle starting from x1,y1 to x2,y2. z=1 for draw, z=0 for erase.
	 Example: lcd.drawBox(10,10,20,20,1);
	 */
	HOSTLCD.print(0x7C,BYTE);
	HOSTLCD.print(0x0F,BYTE);
	HOSTLCD.print(x1,BYTE);
	HOSTLCD.print(y1,BYTE);
	HOSTLCD.print(x2,BYTE);
	HOSTLCD.print(y2,BYTE);
	HOSTLCD.print(z,BYTE);
}

/*________________________________________________________________________________*/
/*________________________________________________________________________________*/
/*________________________________________________________________________________*/

