/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package chart;

/**
 *
 * @author francispapineau
 */
public class ThreadedChartLight extends Thread{

    ThreadedChartLight(){}
    
    public static void main(String[] args){
        ChartLight Chart = new ChartLight();
        Chart.run();
    }

}
