/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ecgjava2;

/**
 *
 * @author SimMan3G
 */
import java.io.*;
import java.net.*;
import java.sql.SQLException;
import java.util.regex.Pattern;
import javax.swing.JOptionPane;

class GPSComm extends Thread{
    
       //define stuff
	public static ServerSocket providerSocket;
	public static Socket connection = null;
	static ObjectOutputStream out;
	static String message = "";
	public void run(){
            try{
		//1. creating a server socket
		providerSocket = new ServerSocket();
			
		//2. Wait for connection
		providerSocket.bind(new InetSocketAddress("localhost", 4444));
		System.out.println("Waiting for connection on localhost:4444");
			
		//2.2 connect to the SQL server
			
		connection = providerSocket.accept();
		System.out.println("Connection received from " + connection.getInetAddress().getHostName());
		JOptionPane.showMessageDialog(null, "Handshake accepted", "Initialize connection", JOptionPane.INFORMATION_MESSAGE);
			
		//3. get Input and Output streams
		out = new ObjectOutputStream(connection.getOutputStream());
		out.flush();
		sendMessage("Connection successful");
			
		//4. The two parts communicate via the input and output streams
		do{
                    sendMessage(message);
                    Dialog_box.update("GPS OUT -> " + message);
                    if (connection.isClosed()){
                        break;
                    }
		}while(true);
            }
            catch(IOException ioException){}
            finally{
		//4: Closing connection
                try{
                    out.close();
                    providerSocket.close();
                }
                catch(IOException ioException){} 
            }
	}
        
        //sned messages
    public static void sendMessage(String msg){
        try{
            out.writeChars(msg + "\n");
            out.flush();
            System.out.println("server>" + msg);
        }
        catch(IOException ioException){}
    }
    
        //close ports
    
    public static void closeSocket() throws IOException{
        Thread.currentThread().destroy();
    }
        //make a new thread
    public static void main(String args[]){
        GPSComm server = new GPSComm();
        while(true){
            server.start();
        }
    }
        //set new message to be sent
    public static void setMessage(String val){
        message = val;
    }
}
