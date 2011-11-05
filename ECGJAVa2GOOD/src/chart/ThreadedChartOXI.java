/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package chart;

/**
 *
 * @author francispapineau
 */
public class ThreadedChartOXI extends Thread{

    ThreadedChartOXI(){}
    
    public static void main(String[] args){
        ChartOXI Chart = new ChartOXI();
        Chart.run();
    }

}
