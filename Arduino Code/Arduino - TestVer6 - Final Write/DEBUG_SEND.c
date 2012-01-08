//
//  **** COMPLETE ****
//
//  DEBUG_SEND.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//
//  To functions to Start and send bogus data to the PC Terminal
//  this helps the client debug and test hes terminal equipment
//  with a random noise generator.


/*________________________________________________________________________________*/

void startDebugSend(void){
    
    // setting a flag to start the pseudorandom
    // generator 1 = Go, 0 = Stop;
    
    DEBUGsendRandom = 1; 
}

/*________________________________________________________________________________*/

// Using the following protocol defined by Francis Papineau in conjunction with Thai Nguyen:

//  -> "!Lig:00.00Tem:00.00ECG:00.00POT:00.00BAT:00.00IRL:00.00LOW:00.00RES:00.00ArT:00.00ErB:00.00ECP00.00\n"

// The system then generated random values to send via the Serial port defined.
// this allows the user to test out the connection and the workings of the 
// server and client apps.

// this function gets a random seed from AnalogPin 13
// and then gets a number from 0-100 to then send through
// the Serial port specified.

void sendPseudoRandom(void){
    
    // Setting a random seed from Analog port 13
    randomSeed(analogRead(13));
    
    // The header for the receiving end of the Serial Network
    HOSTXbee.print("!");
    
    // The Light value
    HOSTXbee.print("Lig:");
    HOSTXbee.print((double)random(1000));
    
    // The tympanic temperature
    HOSTXbee.print("Tem:");
    HOSTXbee.print((double)random(1000));
    
    // The ECG Voltage Level
    HOSTXbee.print("ECG:");
    HOSTXbee.print((double)random(1000));
    
    // The SPO2 Base Measurement using Red Light (approx. 620nm)
    HOSTXbee.print("POT:");
    HOSTXbee.print((double)random(1000));
    
    // The Battery Voltage Level
    HOSTXbee.print("BAT:");
    HOSTXbee.print((double)random(1000));
    
    // The SPO2 Measurment using IR Light (approx. 960nm)
    HOSTXbee.print("IRL:");
    HOSTXbee.print((double)random(1000));
    
    // The SPO2 Measurement using Ambient Light
        // -> this is used in a proprietary algorithm to cancel
        // the effect of ambient light in the SPO2 measurement
    HOSTXbee.print("LOW:");
    HOSTXbee.print((double)random(1000));
    
    // The Respiration sensor measurments
    HOSTXbee.print("RES:");
    HOSTXbee.print((double)random(1000));
    
    // The Ambient Temperature Reading
    HOSTXbee.print("ArT:");
    HOSTXbee.print((double)random(1000));
    
    // The ECG Batt Reading
    HOSTXbee.print("ErB:");
    HOSTXbee.print((double)random(1000));
    
    HOSTXbee.print("ECP:");
    HOSTXbee.print((double)random(1000));
    
    // The Checksum Character.
    HOSTXbee.print("\n");
    
    // Make sure the signals got sent
    delay(10);
}

/*________________________________________________________________________________*/
/*________________________________________________________________________________*/
/*________________________________________________________________________________*/
