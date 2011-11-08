/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ecgjava2;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.IOException;
import java.util.regex.Pattern;

/**
 *
 * @author francispapineau
 */
public class SplitParseBreath {

    SplitParseBreath(){}
    
    /*________________________________________________________________________________*/

    private static String REGEX1 = "[%|r:,]";
    protected static int MatcherArrayIndex1 = 0;
    protected static String value = "", percentage = "";
    protected static double valuenum = 0.00, percentagenum = 0.00;

    static public void splitVal(String Val) throws IOException{
        //Dialog_box.update(Val);

        Pattern p = Pattern.compile(REGEX1);
        String[] items = p.split(Val);
        for(String s : items) {
            System.out.println(s);
            
            System.out.println(s + " " + MatcherArrayIndex1);
            if (MatcherArrayIndex1 == 2){
                valuenum = Float.parseFloat(s);
                ECGJAVa2View.BreathVal.setText(s);
            }
            else if (MatcherArrayIndex1 == 6){
                percentagenum = ((Float.parseFloat(s)));
                ECGJAVa2View.BreathPer.setText(s);
            }
            
            MatcherArrayIndex1++;
        }
        if (valuenum != 0 && percentagenum != 0){
            String x = valuenum + "," + percentagenum + "\n";
            LogFiles.WriteLogFilesB.Writetofile(x);
        }
        MatcherArrayIndex1 = 0;
    }
    public static double getPerNum(){
        return percentagenum;
    }
    public static double getValueNum(){
        return valuenum;
    }
}
