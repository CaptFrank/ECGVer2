/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package chart;

/**
 *
 * @author francispapineau
 */
public class ThreadedChartBreathvalue extends Thread{

    ThreadedChartBreathvalue(){}
    
    public static void main(String[] args){
        ChartBreathvalue Chart = new ChartBreathvalue();
        Chart.run();
    }

}
