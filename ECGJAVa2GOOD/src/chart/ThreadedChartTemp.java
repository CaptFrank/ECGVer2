/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package chart;

/**
 *
 * @author francispapineau
 */
public class ThreadedChartTemp extends Thread{

    ThreadedChartTemp(){}
    
    public static void main(String[] args){
        ChartTemp Chart = new ChartTemp();
        Chart.run();
    }

}
