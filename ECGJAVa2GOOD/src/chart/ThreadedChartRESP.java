/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package chart;

/**
 *
 * @author francispapineau
 */
public class ThreadedChartRESP extends Thread{

    public static void main(String[] args){
        ChartRESP Chart = new ChartRESP();
        Chart.run();
    }

}
