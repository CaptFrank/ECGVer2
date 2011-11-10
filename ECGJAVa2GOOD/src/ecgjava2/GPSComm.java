package ecgjava2;

import java.lang.*;
import java.util.*;
import java.io.*;
import java.awt.*;
import java.awt.event.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.*;
import java.net.*;

public class GPSComm extends Thread {

    private static int port = 2004;
    private static ServerSocket hostServer = null;
    private static Socket socket = null;
    private static PrintWriter out = null;
    static String tesstring = "null\n";
    
    static public void main(String[] args) throws IOException{
        initialize_Socket();
        GPSComm comm = new GPSComm();
        comm.start();
    }

    private static void initialize_Socket() throws IOException {
        hostServer = new ServerSocket(port);
        socket = hostServer.accept();
        out = new PrintWriter(socket.getOutputStream(), true);
    }
        
    public void start() {
        try {
            initialize_Socket();
        } catch (IOException ex) {
            Logger.getLogger(GPSComm.class.getName()).log(Level.SEVERE, null, ex);
        }
        while(socket.isConnected()){
            out.print(tesstring);
        }
    }
}
