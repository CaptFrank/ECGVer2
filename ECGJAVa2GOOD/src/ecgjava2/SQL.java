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
  protected static Connection Connection = null;

    public static void main(String args[]){
        SQL Server = new SQL();
        Server.start();
    }

    static void connectArduinoData() throws IOException, InstantiationException, IllegalAccessException, SQLException, ClassNotFoundException {
      Class.forName("org.gjt.mm.mysql.Driver");
      Connection = DriverManager.getConnection("jdbc:mysql://192.168.2.10:3306/arduino_data", "DataUser", "data");
      System.out.println("Connection successful!");
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
      Connection = DriverManager.getConnection("jdbc:mysql://192.168.2.10:3306/trends", "DataUser", "data");
      System.out.println("Connection successful!");
      connected = true;

      if (Connection != null) {
        try {
          Connection.close();
        } catch (SQLException e) {
          e.printStackTrace();
        }
      }
    }
    static void connectHistory() throws IOException, InstantiationException, IllegalAccessException, SQLException, ClassNotFoundException {
      Class.forName("org.gjt.mm.mysql.Driver");
      Connection = DriverManager.getConnection("jdbc:mysql://192.168.2.10:3306/history_data", "DataUser", "data");
      System.out.println("Connection successful!");
      connected = true;

      if (Connection != null) {
        try {
          Connection.close();
        } catch (SQLException e) {
          e.printStackTrace();
        }
      }
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


