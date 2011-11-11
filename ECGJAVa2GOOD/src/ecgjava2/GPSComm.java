package ecgjava2;

import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.net.*;

/**
 * The GPSComm class does 
 * @author Francis Papineau
 */

public class GPSComm extends Thread {

    private static int port = 2004;
    private static ServerSocket hostServer = null;
    private static Socket socket = null;
    private static PrintWriter out = null;
    static String tesString = "null\n";
    
    static public void main(String[] args) throws IOException{
        // Initialize stuff
        initialize_Socket();
        GPSComm comm = new GPSComm();
        comm.start();
    }

    private static void initialize_Socket() throws IOException {
        hostServer = new ServerSocket(port);
        socket = hostServer.accept();
        out = new PrintWriter(socket.getOutputStream(), true);
    }
    
    /**
     * Initializes and prints tessstring
     */
    public void start() {
        try {
            initialize_Socket();
        } catch (IOException ex) {
            Logger.getLogger(GPSComm.class.getName()).log(Level.SEVERE, null, ex);
        }
        while(socket.isConnected()){
            out.print(tesString);
        }
    }
    public void disconnect() throws IOException{

        socket.close();
    }
}
