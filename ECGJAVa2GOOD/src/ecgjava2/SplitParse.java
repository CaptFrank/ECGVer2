
        /*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package ecgjava2;

import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 *
 * @author francispapineau
 */
public class SplitParse {

    SplitParse(){}
    
    /*________________________________________________________________________________*/

    private static String REGEX1 = "[!Lig:TemECGPOBAIRWS]";
   
    /*  ADD THE REGEX FOR PARSING */
    
    
    private static String REGEX2 = "";
    
    
    
    
    
    protected static int ArrayIndex1 = 0, ArrayIndex2 = 0;
    protected static double GlobalTime;
    protected static String GPSSentence = "", ECGSentence ="";
    protected static String Light = "", Temp = "", ECG = "", Pot = "", Bat = "", IR = "", Low = "", RESP = "";
    protected static double Lightnum = 0.00, Tempnum = 0.00, ECGnum = 0.00, Potnum = 0.00, Battery = 0.00, IRnum = 0.00, LowNum = 0.00, RESPnum = 0.00;
    protected static double [][] SPO2Array = new double [40][2];
    protected static boolean full = false;
    protected static getBPM BPM = new getBPM();
    protected static long InitialTime = 0;

   /*________________________________________________________________________________*/

    /*
     * 
     * This method splits the message acquired by the connection to 2 sentences
     * one GPS sentence with basic info and one on the vital data monitoring data
     * 
     */
    
    
    static public void splitGPS_Val(String Val) throws IOException{
        
        Pattern p1 = Pattern.compile(REGEX2);
        String[] items = p1.split(Val);
        for (String s : items){
            // get values
            
            // GPSSentence = ...
            
            // ECGSentence = ...
            
            // Send_GPS(GPSSentence);
            //Send to the Server Socket Thread using a mehtod based
            //on interrupts
            
            // splitVal(ECGSentence);
            //Split the values from the ECG vital Signs 
        }  
    }
    static public void splitVal(String Val) throws IOException{
        if (ArrayIndex2 == 0){
           InitialTime = System.currentTimeMillis();
        }
        Pattern p = Pattern.compile(REGEX1);
        String[] items = p.split(Val);
        for(String s : items) {
            if (ArrayIndex1 == 5){
                Light = items[5];
                if (Light != null && !Light.isEmpty()){
                    Lightnum = Double.parseDouble(Light);
                    ECGJAVa2View.LightValue.setText(Light);
                }
                ECGJAVa2View.LightValue.repaint();
            }
            else if (ArrayIndex1 == 9){
                Temp = items[9];
                if (Temp != null && !Temp.isEmpty()){
                    Tempnum = Double.parseDouble(Temp);
                    ECGJAVa2View.TympTempValue.setText(Temp);
                }
                ECGJAVa2View.TympTempValue.repaint();
            }
            else if (ArrayIndex1 == 13){
                ECG = items[13];
                if (ECG != null && !ECG.isEmpty()){
                    ECGnum = Double.parseDouble(ECG);
                    ECGJAVa2View.ECGValue.setText(ECG);
                }
                ECGJAVa2View.ECGValue.repaint();
            }
            else if (ArrayIndex1 == 17){
                Pot = items[17];
                if (Pot != null && !Pot.isEmpty()){
                    Potnum = Double.parseDouble(Pot);
                    if (ArrayIndex2 < SPO2Array.length){
                        SPO2Array[ArrayIndex2][0] = InitialTime;
                        SPO2Array[ArrayIndex2][1] = Potnum;
                        ArrayIndex2++;
                    }
                    if (ArrayIndex2 == SPO2Array.length){
                        ArrayIndex2 = 0;
                        full = true;
                        if (full){
                            BPM.run();
                        }
                    }
                    ECGJAVa2View.REDLED.setText(Pot);
                }
                ECGJAVa2View.REDLED.repaint();
            }
            else if (ArrayIndex1 == 21){
                Bat = items[21];
                if (Bat != null && !Bat.isEmpty()){
                    Battery = Double.parseDouble(Bat)/100.00;
                    ECGJAVa2View.Batt.setText(Battery + "V");
                }
                ECGJAVa2View.Batt.repaint();
            }
            else if (ArrayIndex1 == 25){
                IR = items[25];
                if (IR != null && !IR.isEmpty()){
                    IRnum = Double.parseDouble(IR);
                    ECGJAVa2View.IRLED.setText(Double.toString(IRnum));
                }
                ECGJAVa2View.IRLED.repaint();
            }
            else if (ArrayIndex1 == 29){
                Low = items[29];
                if (Low != null && !Low.isEmpty()){
                    LowNum = Double.parseDouble(Low);
                    System.out.println(LowNum);
                }
            }
            else if (ArrayIndex1 == 33){
                RESP = items[33];
                if (RESP != null && !RESP.isEmpty()){
                    RESPnum = Double.parseDouble(RESP);
                    System.out.println(RESPnum);
                }
                ECGJAVa2View.RESP.repaint();
            }
            ArrayIndex1++;
            if (getSPO2.getGuard()){
                getSPO2.getSPO2();
            }
        }
        if (Light != null && ECG != null && Temp != null && Pot != null && !Light.isEmpty() && !ECG.isEmpty() && !Temp.isEmpty() && !Pot.isEmpty() && Bat != null && !Bat.isEmpty()
                && IR != null && !IR.isEmpty() && Low != null && !Low.isEmpty() && RESP != null && !RESP.isEmpty()){
            GlobalTime = System.currentTimeMillis() - ECGJAVa2View.InitialTime;
            String x = (System.currentTimeMillis() - ECGJAVa2View.InitialTime) + "," + Lightnum + "," + ECGnum + "," + Tempnum + "," + Potnum + "," + Bat + "," + IRnum + "," + LowNum + "," + RESPnum + "\n";
            LogFiles.WriteLogFiles.Writetofile(x);
        }

        ArrayIndex1 = 0;
    }

       /*________________________________________________________________________________*/

    public static boolean parsable(String val){
        
        Pattern p = Pattern.compile("(!?)(Lig:)(\\d+)(.)(\\d+)(Tem:)(\\d+)(.)(\\d+)(ECG:)(\\d+)(.)(\\d+)(POT:)(\\d+)(.)(\\d+)(BAT:)(\\d+)(.)(\\d+)(IRL:)(\\d+)(.)(\\d+)(LOW:)(\\d+)(.)(\\d+)(RES:)(\\d+)(.)(\\d+)");
        Matcher m = p.matcher(val);

        if (m.find()){
            return true;
        }
        else{
            return false;
        }
    }
    public static double getPotnum(){
        return Potnum;
    }
    public static double[][] getArray(){
        return SPO2Array;
    }
    public static double getLowNum(){
        return LowNum;
    }
    public static double getIRValue(){
        return IRnum;
    }
    public static boolean getFull(){
        return full;
    }
    public static double getTempNum(){
        return Tempnum;
    }
    public static double getLightNum(){
        return Lightnum;
    }
    public static double getECGNum(){
        return ECGnum;
    }
    public static double getBattery(){
        return Battery;
    }
    public static double getIRNum(){
        return IRnum;
    }
    public static double getRESPNum(){
        return RESPnum;
    }
    
}
