//
//  Sensors.c
//  ECGVer2
//
//  Created by FRANCIS PAPINEAU on 12-01-01.
//  Copyright 2012 carleton university. All rights reserved.
//

/*________________________________________________________________________________*/


void sendSensorValues(){
#ifdef SensorsOK
    
    // Using the following protocol defined by Francis Papineau in conjunction with Thai Nguyen:
    
    //  -> "!Lig:00.00Tem:00.00ECG:00.00POT:00.00BAT:00.00IRL:00.00LOW:00.00RES:00.00ArT:00.00\n"
    
    // The system then reads values to send via the Serial port defined.
    
    // The header for the receiving end of the Serial Network
    HOSTXbee.print("!");
    
    // The Light value
    HOSTXbee.print("Lig:");
    tempLight = analogRead(Light);
    HOSTXbee.print(tempLight);
    
    // The tympanic temperature
    HOSTXbee.print("Tem:");
    temp = getTermocoupleValue();
    HOSTXbee.print(temp);
    
    // The ECG Voltage Level
    HOSTXbee.print("ECG:");
    tempECG = analogRead(ECG);
    HOSTXbee.print(tempECG);
    
    // The SPO2 Base Measurement using Red Light (approx. 620nm)
    // The measurment is done between a flikr of the LED
    HOSTXbee.print("POT:");
    
    // LED ON
    digitalWrite(redLED, HIGH);
    tempRed = pulseIn(PulseOx, HIGH);
    HOSTXbee.print(tempRed);
    
    // LED OFF
    digitalWrite(redLED, LOW);
    
    // The Battery Voltage Level
    HOSTXbee.print("BAT:");
    tempBat = analogRead(Battery);
    HOSTXbee.print(tempBat);
    
    // The SPO2 Measurment using IR Light (approx. 960nm)
    // The measurment is done between a flikr of the LED
    HOSTXbee.print("IRL:");
    
    // LED ON
    digitalWrite(irLED, HIGH);
    tempIr = pulseIn(PulseOx, HIGH);
    HOSTXbee.print(tempIr);
    
    // LED OFF
    digitalWrite(irLED, LOW);
    
    // The SPO2 Measurement using Ambient Light
    // -> this is used in a proprietary algorithm to cancel
    // the effect of ambient light in the SPO2 measurement
    HOSTXbee.print("LOW:");
    tempError = pulseIn(PulseOx, HIGH);
    HOSTXbee.print(tempError);
    
    // The Respiration sensor measurments
    HOSTXbee.print("RES:");
    tempRESP = analogRead(Resp);
    HOSTXbee.print(tempRESP);
    
    // The Ambient Temperature Reading
    HOSTXbee.print("ArT:");
    AmbientTemp = Thermistor(analogRead(AmbTemp));
    HOSTXbee.print(AmbientTemp);
    
    // The Checksum Character.
    HOSTXbee.print("\n");
    
    // Make sure the signals got sent
    delay(10);
    
#endif
}

/*________________________________________________________________________________*/


/*________________________________________________________________________________*/


/*________________________________________________________________________________*/

