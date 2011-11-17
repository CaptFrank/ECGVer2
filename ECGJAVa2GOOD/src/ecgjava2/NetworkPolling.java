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
import java.net.*;
import java.util.*;
import static java.lang.System.out;
import java.util.logging.Level;
import java.util.logging.Logger;

public class NetworkPolling 
{    
    static public InetAddress compare;
    public static void main(String args[]) throws SocketException {
        Enumeration<NetworkInterface> nets = NetworkInterface.getNetworkInterfaces();
        for (NetworkInterface netint : Collections.list(nets))
            displayInterfaceInformation(netint);
    }

    static void displayInterfaceInformation(NetworkInterface netint) throws SocketException {
        try {
            InetAddress compare = InetAddress.getLocalHost();
        } catch (UnknownHostException ex) {
            Logger.getLogger(NetworkPolling.class.getName()).log(Level.SEVERE, null, ex);
        }
        out.printf("Display name: %s\n", netint.getDisplayName());
        out.printf("Name: %s\n", netint.getName());
        Enumeration<InetAddress> inetAddresses = netint.getInetAddresses();
        for (InetAddress inetAddress : Collections.list(inetAddresses)) {
            if(inetAddress.getAddress().toString().equals(compare.getAddress().toString())) System.out.println("good!!!");
            System.out.println(inetAddress.getAddress().toString());
            out.printf("InetAddress: %s\n", inetAddress, inetAddress.getAddress().toString());
        }
        out.printf("\n");
     }
}