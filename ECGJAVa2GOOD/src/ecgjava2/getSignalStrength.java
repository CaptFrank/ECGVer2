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

    protected static String Broadcast_Power;
    protected static String SignalStrength;
    protected static String DestinationAddressHigh, DestinationAddressLow, PANID, VersionID, ChannelID, NodeID;

    void getSignalStrenght(){}
    
    public static void getSignalStrength() throws IOException{
        CommPortOpen.printCommand("ATDB\r");
        SignalStrength = CommPortOpen.readReply();
        int value = Integer.parseInt(SignalStrength, 16);
        value = 100-value;
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
       CommPortOpen.printCommand("ATPL\r");
       Broadcast_Power = CommPortOpen.readReply();
       SignalAnalysis.Broadcastpower.setText("-" + Broadcast_Power);
    }

    public static void getDestinationAddressHigh() throws IOException{
        CommPortOpen.printCommand("ATDH\r");
        DestinationAddressHigh = CommPortOpen.readReply();
        SignalAnalysis.DestinationAddressHigh.setText(DestinationAddressHigh);
    }

    public static void getDestinationAddressLow() throws IOException{
        CommPortOpen.printCommand("ATDL\r");
        DestinationAddressLow = CommPortOpen.readReply();
        SignalAnalysis.DestinationAddressLow.setText(DestinationAddressLow);
    }

    public static void getPANID() throws IOException{
        CommPortOpen.printCommand("ATID\r");
        PANID = CommPortOpen.readReply();
        SignalAnalysis.PANID.setText(PANID);
    }

    public static void getVersionID() throws IOException{
        CommPortOpen.printCommand("ATVR\r");
        VersionID = CommPortOpen.readReply();
        SignalAnalysis.FirmwareID.setText(VersionID); 
    }


    public static void getChannelID() throws IOException{
        CommPortOpen.printCommand("ATCH\r");
        ChannelID = CommPortOpen.readReply();
        SignalAnalysis.ChannelID.setText(ChannelID);
    }

    public static boolean ACK() throws IOException{
        CommPortOpen.printCommand("+++");
        while(true){
            String Test = CommPortOpen.readReply();
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
        CommPortOpen.printCommand("ATCN\r");
        return true;
    }
}
