/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package ecgjava2;

import java.io.IOException;

/**
 *
 * @author francispapineau
 */
public class getSignalStrength {

    public static String Broadcast_Power;
    public static String SignalStrength;
    public static String DestinationAddressHigh, DestinationAddressLow, PANID, VersionID, ChannelID, NodeID;

    public static void getSignalStrength() throws IOException{
        CommPortOpen.os.print("ATDB\r");
        SignalStrength = CommPortOpen.is.readLine();
        int value = Integer.parseInt(SignalStrength, 16);
        System.out.print(value);
        SignalAnalysis.SignalStrength.setText("-" + Integer.toString(value));

        if(value >= 100){
            SignalAnalysis.SignalStrengthProg.setValue(100);
            ECGJAVa2View.label40.setVisible(true);
            ECGJAVa2View.label30.setVisible(true);
            ECGJAVa2View.label20.setVisible(true);
            ECGJAVa2View.label10.setVisible(true);
                        ECGJAVa2View.SignalStrength.updateUI();

        }
        else if(value > 70 && value <= 90)
        {
            SignalAnalysis.SignalStrengthProg.setValue(90);
            ECGJAVa2View.label30.setVisible(true);
            ECGJAVa2View.label20.setVisible(true);
            ECGJAVa2View.label10.setVisible(true);
                        ECGJAVa2View.SignalStrength.updateUI();


        }
        else if(value > 50 && value <= 70){
            SignalAnalysis.SignalStrengthProg.setValue(70);
            ECGJAVa2View.label20.setVisible(true);
            ECGJAVa2View.label10.setVisible(true);
                        ECGJAVa2View.SignalStrength.updateUI();

        }
        else if(value > 30 && value <= 50){
            SignalAnalysis.SignalStrengthProg.setValue(50);
            ECGJAVa2View.label10.setVisible(true);
                        ECGJAVa2View.SignalStrength.updateUI();

        }
        else if(value < 30){
            SignalAnalysis.SignalStrengthProg.setValue(30);
            ECGJAVa2View.label10.setVisible(true);
                        ECGJAVa2View.SignalStrength.updateUI();
        }
    }

    public static void getSignalPower() throws IOException{
       CommPortOpen.os.print("ATPL\r");
       Broadcast_Power = CommPortOpen.is.readLine();
       SignalAnalysis.Broadcastpower.setText("-" + Broadcast_Power);
    }

    public static void getDestinationAddressHigh() throws IOException{
        CommPortOpen.os.print("ATDH\r");
        DestinationAddressHigh = CommPortOpen.is.readLine();
        SignalAnalysis.DestinationAddressHigh.setText(DestinationAddressHigh);
    }

    public static void getDestinationAddressLow() throws IOException{
        CommPortOpen.os.print("ATDL\r");
        DestinationAddressLow = CommPortOpen.is.readLine();
        SignalAnalysis.DestinationAddressLow.setText(DestinationAddressLow);
    }

    public static void getPANID() throws IOException{
        CommPortOpen.os.print("ATID\r");
        PANID = CommPortOpen.is.readLine();
        SignalAnalysis.PANID.setText(PANID);
    }

    public static void getVersionID() throws IOException{
        CommPortOpen.os.print("ATVR\r");
        VersionID = CommPortOpen.is.readLine();
        SignalAnalysis.FirmwareID.setText(VersionID); 
    }


    public static void getChannelID() throws IOException{
        CommPortOpen.os.print("ATCH\r");
        ChannelID = CommPortOpen.is.readLine();
        SignalAnalysis.ChannelID.setText(ChannelID);
    }

    public static boolean ACK() throws IOException{
        CommPortOpen.os.print("+++");
        while(true){
            String Test = CommPortOpen.is.readLine();
            int True = Test.indexOf("OK");
            if (True >= 0){
                return true;
            }
        }
    }

    public static void getAll() throws IOException{
        getSignalStrength();
        getSignalPower();
        getDestinationAddressHigh();
        getDestinationAddressLow();
        getPANID();
        getVersionID();
        getChannelID();
    }

    public static boolean finishUp(){
        CommPortOpen.os.print("ATCN\r");
        return true;
    }
}
