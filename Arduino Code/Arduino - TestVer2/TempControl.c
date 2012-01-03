//
//  ******* COMPLETE *******
//
//  TempControl.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//

/* --------------------------------------------------------- */



#ifdef MEGA

MAX6675 thermocouple(CLK, CS, DS);

#endif

double getThermistorValue(int RawADC) {
    
    #ifdef MEGA
    
    long Resistance;  
    double Temp;  // Dual-Purpose variable to save space.
    
    Resistance = ((1024 * pad / RawADC) - pad); 
    Temp = log(Resistance); // Saving the Log(resistance) so not to calculate  it 4 times later
    Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
    Temp = Temp - 273.15;  // Convert Kelvin to Celsius                      
    return Temp;                                      // Return the Temperature
    
    #endif
}

/* --------------------------------------------------------- */

double getTermocoupleValue(void){
    
    #ifdef MEGA
    
    // return the thermocouple value
    return thermocouple.readCelsius();
    
    #endif
}

/* --------------------------------------------------------- */


/* --------------------------------------------------------- */


/* --------------------------------------------------------- */

