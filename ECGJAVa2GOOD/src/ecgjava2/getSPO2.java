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
    
    getSPO2(){}
    
    protected static double averageSPO2 = 100.00;
    protected static boolean guard = false;

    public static void getSPO2(){
        double error = SplitParse.getLowNum();
        double tempSPO2 = (((SplitParse.getPotnum() - error) / (SplitParse.getIRValue() - error))*100.00);
        averageSPO2 += tempSPO2;
        averageSPO2 = averageSPO2 / 2.0;
        ECGJAVa2View.SPO2Value.setText(Integer.toString((int)averageSPO2));
    }

    public static void reset(){
        averageSPO2 = 0.00;
    }
    static void setSPO2Guard(boolean val){
        guard = val;
    }
    public static boolean getGuard(){
        return guard;
    }
}
