/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package chart;

/**
 *
 * @author francispapineau
 */
public class ThreadedChartAmbTemp extends Thread{

    ThreadedChartAmbTemp(){}
    
    public static void main(String[] args){
        ChartAmbTemp Chart = new ChartAmbTemp();
        Chart.run();
    }

}
