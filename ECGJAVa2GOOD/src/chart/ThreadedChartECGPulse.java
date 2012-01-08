/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package chart;

/**
 *
 * @author francispapineau
 */
public class ThreadedChartECGPulse extends Thread{

    ThreadedChartECGPulse(){}
    
    public static void main(String[] args){
        ChartECGPulse Chart = new ChartECGPulse();
        Chart.run();
    }

}
