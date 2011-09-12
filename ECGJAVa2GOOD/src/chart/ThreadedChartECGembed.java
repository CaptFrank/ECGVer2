/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package chart;

/**
 *
 * @author francispapineau
 */
public class ThreadedChartECGembed extends Thread{

    public static void main(String[] args){
        ChartECGembed Chart = new ChartECGembed();
        Chart.run();
    }

}
