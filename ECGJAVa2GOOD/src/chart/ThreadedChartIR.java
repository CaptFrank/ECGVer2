/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package chart;

/**
 *
 * @author francispapineau
 */
public class ThreadedChartIR extends Thread{

    ThreadedChartIR(){}
    
    public static void main(String[] args){
        ChartIR Chart = new ChartIR();
        Chart.run();
    }

}
