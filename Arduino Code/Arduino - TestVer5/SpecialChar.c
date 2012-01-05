//
//  SpecialChar.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//



/*________________________________________________________________________________*/

// Defining Spceial Characters

//Empty Battery:
const char Empty_Battery[] = {0x0e, 0x0e, 0x1b, 0x11, 0x11, 0x11, 0x11, 0x1f};

//Connected to PC Symbol:
const char Connected_PC_Symbol[] = {0x04, 0x0e, 0x15, 0x04, 0x04, 0x15, 0x0e, 0x04};

//Connected to XBee Symbol
const char Connected_XBee_Symbol[] = {0x00, 0x0e, 0x11, 0x15, 0x0e, 0x1f, 0x04, 0x04};

//USB Storage Symbol
const char USB_Store_Symbol[] = {0x00, 0x0e, 0x0a, 0x1f, 0x15, 0x1f, 0x15, 0x1f};

//Empty Heart Beat:
const char Empty_HB[] = {0x0e, 0x1b, 0x11, 0x11, 0x11, 0x11, 0x1b, 0x0e};

//Full Heart Beat:
const char Full_HB[] = {0x0e, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x0e};

//Sprite Character
const char custom_0[] = {0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00};
const char custom_1[] = {0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x07, 0x07};
const char custom_2[] = {0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1e, 0x1e};
const char custom_3[] = {0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00};
const char custom_4[] = {0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e};
const char custom_5[] = {0x00, 0x03, 0x1f, 0x1f, 0x1f, 0x03, 0x00, 0x00};
const char custom_6[] = {0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07};
const char custom_7[] = {0x1e, 0x1e, 0x1f, 0x1f, 0x1f, 0x1e, 0x1e, 0x1e};

//Diagram
//
//  ===||=== -> 0 0 1 2 0 0 
//     ||=|  -> 6 7 5
//     ||    -> 6 4

/*________________________________________________________________________________*/




