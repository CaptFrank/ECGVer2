/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 *
 *
 * CHANGE TO FIT SQL SERVER
 *
 *
 *
 */
package ecgjava2;

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

/**
 *
 * @author Administrator
 */
public class SQL extends Thread{
    
    SQL(){}

  protected static String Message = "";
  protected static String copy = "";
  protected static boolean connected = false;
  protected static Connection Connection = null, Connection1 = null, Connection2 = null, Connection3 = null;

    public static void main(String args[]){
        SQL Server = new SQL();
        Server.start();
    }

    static void connectArduinoData() throws IOException, InstantiationException, IllegalAccessException, SQLException, ClassNotFoundException {
      Class.forName("org.gjt.mm.mysql.Driver");
      Connection = DriverManager.getConnection("jdbc:mysql://192.168.2.10:3306/arduino_data", "DataUser", "data");
      System.out.println("Connection successful to Arduino Data Database!");
      Dialog_box.update("Connection successful to Arduino Data Database!\n");

      connected = true;

      if (Connection != null) {
        try {
          Connection.close();
        } catch (SQLException e) {
          e.printStackTrace();
        }
      }
    }
    static void connectTrends() throws IOException, InstantiationException, IllegalAccessException, SQLException, ClassNotFoundException {
      Class.forName("org.gjt.mm.mysql.Driver");
      Connection1 = DriverManager.getConnection("jdbc:mysql://192.168.2.10:3306/trends", "DataUser", "data");
      System.out.println("Connection successful to Trend Data Database!");
      Dialog_box.update("Connection successful to Trend Data Database!\n");

      connected = true;

      if (Connection1 != null) {
        try {
          Connection1.close();
        } catch (SQLException e) {
        }
      }
    }
    static void connectHistory() throws IOException, InstantiationException, IllegalAccessException, SQLException, ClassNotFoundException {
      Class.forName("org.gjt.mm.mysql.Driver");
      Connection2 = DriverManager.getConnection("jdbc:mysql://192.168.2.10:3306/history_data", "DataUser", "data");
      System.out.println("Connection successful to History Database!");
      Dialog_box.update("Connection successful to History Database!\n");
      connected = true;

      if (Connection2 != null) {
        try {
          Connection2.close();
        } catch (SQLException e) {
        }
      }
    }
    static void connectGPS() throws IOException, InstantiationException, IllegalAccessException, SQLException, ClassNotFoundException {
      Class.forName("org.gjt.mm.mysql.Driver");
      Connection3 = DriverManager.getConnection("jdbc:mysql://192.168.2.10:3306/gps_data", "DataUser", "data");
      System.out.println("Connection successful to GPS Database!");
      Dialog_box.update("Connection successful to GPS Database!\n");
      connected = true;

      if (Connection3 != null) {
        try {
          Connection3.close();
        } catch (SQLException e) {
        }
      }
    }
    
    static void disconnectSQL() throws SQLException{
        Connection.close();
        System.out.println("Disconnection successful to Arduino Data Database!");
        Dialog_box.update("Disconnection successful to Arduino Data Database!\n");
        Connection1.close();
        System.out.println("Disconnection successful to Arduino Data Database!");
        Dialog_box.update("Disconnection successful to Arduino Data Database!\n");
        Connection2.close();
        System.out.println("Disconnection successful to Arduino Data Database!");
        Dialog_box.update("Disconnection successful to Arduino Data Database!\n");
        Connection3.close();
        System.out.println("Disconnection successful to Arduino Data Database!");
        Dialog_box.update("Disconnection successful to Arduino Data Database!\n");
    }
    
    static boolean getConnectedSQL(){
    
        return connected;
    }
    
    static void insertItems(String instance, String Command){

        // To Do
        
    }

    static void getItems(String instance, String Command){

        // To Do
        
    }
    
    static void PostResults(){
        
        // To Do
        
    }
    
    static void requestQuery(){
     
        // To Do
        
    }
  }


