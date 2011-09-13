/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package ecgjava2;

/**
 *
 * @author francispapineau
 */
public class getSPO2 {
    
    static double averageSPO2 = 0.00;
    static boolean guard = false;

    public static void getSPO2(){
        double tempSPO2 = (SplitParse.Potnum / SplitParse.IRnum);
        averageSPO2 += tempSPO2;
        averageSPO2 = averageSPO2 / 2.0;
        ECGJAVa2View.SPO2Value.setText(Integer.toString((int) (averageSPO2 * 100)));
    }

    public static void reset(){
        averageSPO2 = 0.00;
    }
}
