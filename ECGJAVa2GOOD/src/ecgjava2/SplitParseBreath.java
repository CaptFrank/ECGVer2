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

    /*________________________________________________________________________________*/

    private static String REGEX1 = "[%|r:,]";
    static public int i = 0;
    static public String value = "", percentage = "";
    static public double valuenum = 0.00, percentagenum = 0.00;

    static public void splitVal(String Val) throws IOException{
        //Dialog_box.update(Val);

        Pattern p = Pattern.compile(REGEX1);
        String[] items = p.split(Val);
        for(String s : items) {
            System.out.println(s);
            
            System.out.println(s + " " + i);
            if (i == 2){
                valuenum = Float.parseFloat(s);
                ECGJAVa2View.BreathVal.setText(s);
                System.out.println("% =" + ECGJAVa2View.value);
            }
            else if (i == 6){
                percentagenum = ((float) (Float.parseFloat(s)));
                ECGJAVa2View.BreathPer.setText(s);
                System.out.println("% =" + ECGJAVa2View.percentage);
            }
            
            i++;
        }
        if (valuenum != 0 && percentagenum != 0){
            String x = valuenum + "," + percentagenum + "\n";
            LogFiles.WriteLogFilesB.Writetofile(x);
        }
        i = 0;
    }
}
