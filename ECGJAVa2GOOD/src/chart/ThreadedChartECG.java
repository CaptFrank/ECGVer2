/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package chart;

/**
 *
 * @author francispapineau
 */
public class ThreadedChartECG extends Thread{

    ThreadedChartECG(){}
    
    public static void main(String[] args){
        ChartECG Chart = new ChartECG();
        Chart.run();
    }

}
