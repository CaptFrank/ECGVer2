/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package ecgjava2;

/**
 *
 * @author francispapineau
 */

import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.*;

public class FileChooser extends Thread{
    
    FileChooser(){}

    public static void main(String[] args) {
        final JFrame frame = new JFrame("Open Log Files");


        final JFileChooser fc = new JFileChooser();
        fc.setMultiSelectionEnabled(true);
                int retVal = fc.showOpenDialog(frame);
                if (retVal == JFileChooser.APPROVE_OPTION) {
                    File selectedfile = fc.getSelectedFile();
                    StringBuilder sb = new StringBuilder();
                    System.out.println(fc.getSelectedFile());

                    // Execute a command without arguments
                    String command = "open " + fc.getSelectedFile();
                    try {
                        Process child = Runtime.getRuntime().exec(command);
                    } catch (IOException ex) {
                        Logger.getLogger(FileChooser.class.getName()).log(Level.SEVERE, null, ex);
                    }
                }
    }
}