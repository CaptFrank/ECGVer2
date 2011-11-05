
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
    static public int i = 0, count = 0, j = 0;
    static public double GlobalTime;
    static public String Light = "", Temp = "", ECG = "", Pot = "", Bat = "", IR = "", Low = "", RESP = "";
    static public double Lightnum = 0.00, Tempnum = 0.00, ECGnum = 0.00, Potnum = 0.00, Battery = 0.00, IRnum = 0.00, LowNum = 0.00, RESPnum = 0.00;
    static public double lightTotal = 0.00, ECGTotal = 0.00, potTotal = 0.00, BatteryTotal = 0.00, IRTotal = 0.00;
    static public double lightavrg = 0.00, ECGavrg = 0.00, potavrg = 0.00, Batteryavrg = 0.00, IRavrg = 0.00;
    static public double [][] SPO2Array = new double [40][2];
    static public boolean full = false;
    static public getBPM BPM = new getBPM();
    public static long InitialTime = 0;

   /*________________________________________________________________________________*/


    static public void splitVal(String Val) throws IOException{
        if (j == 0){
           InitialTime = System.currentTimeMillis();
        }
        count++;
        Pattern p = Pattern.compile(REGEX1);
        String[] items = p.split(Val);
        for(String s : items) {
            if (i == 5){
                Light = items[5];
                if (Light != null && !Light.isEmpty()){
                    Lightnum = Double.parseDouble(Light);
                    lightTotal += Lightnum;
                    lightavrg = lightTotal / count*1.0;
                    ECGJAVa2View.LightValue.setText(Light);
                }
                ECGJAVa2View.LightValue.repaint();
            }
            else if (i == 9){
                Temp = items[9];
                if (Temp != null && !Temp.isEmpty()){
                    Tempnum = Double.parseDouble(Temp);
                    ECGJAVa2View.TympTempValue.setText(Temp);
                }
                ECGJAVa2View.TympTempValue.repaint();
            }
            else if (i == 13){
                ECG = items[13];
                if (ECG != null && !ECG.isEmpty()){
                    ECGnum = Double.parseDouble(ECG);
                    ECGTotal += ECGnum;
                    ECGavrg = ECGTotal / count*1.0;
                    ECGJAVa2View.ECGValue.setText(ECG);
                }
                ECGJAVa2View.ECGValue.repaint();
            }
            else if (i == 17){
                Pot = items[17];
                if (Pot != null && !Pot.isEmpty()){
                    Potnum = Double.parseDouble(Pot);
                    if (j < SPO2Array.length){
                        SPO2Array[j][0] = InitialTime;
                        SPO2Array[j][1] = Potnum;
                        j++;
                    }
                    if (j == SPO2Array.length){
                        j = 0;
                        full = true;
                        if (full){
                            BPM.run();
                        }
                    }
                    ECGJAVa2View.REDLED.setText(Pot);
                }
                ECGJAVa2View.REDLED.repaint();
            }
            else if (i == 21){
                Bat = items[21];
                if (Bat != null && !Bat.isEmpty()){
                    Battery = Double.parseDouble(Bat)/100.00;
                    Batteryavrg += Battery / count*1.0;
                    ECGJAVa2View.Batt.setText(Battery + "V");
                }
                ECGJAVa2View.Batt.repaint();
            }
            else if (i == 25){
                IR = items[25];
                if (IR != null && !IR.isEmpty()){
                    IRnum = Double.parseDouble(IR);
                    ECGJAVa2View.IRLED.setText(Double.toString(IRnum));
                }
                ECGJAVa2View.IRLED.repaint();
            }
            else if (i == 29){
                Low = items[29];
                if (Low != null && !Low.isEmpty()){
                    LowNum = Double.parseDouble(Low);
                    System.out.println(LowNum);
                }
            }
            else if (i == 33){
                RESP = items[33];
                if (RESP != null && !RESP.isEmpty()){
                    RESPnum = Double.parseDouble(RESP);
                    System.out.println(RESPnum);
                }
                ECGJAVa2View.RESP.repaint();
            }
            i++;
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

        i = 0;
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
    static double getIRValue(){
        return IRnum;
    }
    static boolean getFull(){
        return full;
    }
}
