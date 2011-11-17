/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package ecgjava2;
    /*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Administrator
 */

import javax.swing.*;

public final class Dialog_boxGPS extends JFrame{
   /*________________________________________________________________________________*/

    public Dialog_boxGPS(){
        initComponents();
        this.setTitle("GPS COMM");
    }

   /*________________________________________________________________________________*/


  @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">
    public void initComponents() {

        jLabel1 = new javax.swing.JLabel();
        jScrollPane1 = new javax.swing.JScrollPane();
        outputArea = new javax.swing.JTextArea();

        setDefaultCloseOperation(javax.swing.WindowConstants.HIDE_ON_CLOSE);

        jLabel1.setText("DEBUG CONSOLE");
        outputArea.setColumns(40);
        outputArea.setRows(100);
        jScrollPane1.setViewportView(outputArea);

        jScrollPane1.setName("DEBUG CONSOLE");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 384, Short.MAX_VALUE)
                    .addComponent(jLabel1))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel1)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 268, Short.MAX_VALUE)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>

   /*________________________________________________________________________________*/


      static public void update(String x) {
          if (ECGJAVa2View.getDialogConnected()){
                outputArea.append(x + "\n");
          }
      }

   /*________________________________________________________________________________*/

  // Variables declaration - do not modify
    private javax.swing.JLabel jLabel1;
    private javax.swing.JScrollPane jScrollPane1;
    static public javax.swing.JTextArea outputArea;
    // End of variables declaration
}
