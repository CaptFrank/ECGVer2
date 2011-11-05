/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package LogFiles;

/**
 *
 * @author francispapineau
 */
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Date;
import javax.swing.JOptionPane;


public class WriteLogFiles {
    public static FileOutputStream outputFileStream = null;
    static File aFile;
    private static BufferedWriter output;
    public static Date date;
    public static FileReader in;
    public static FileWriter fout;

    WriteLogFiles(){}
    
    private final static java.text.SimpleDateFormat dateFormat = new java.text.SimpleDateFormat("yyyy.MMMM.dd");

  public static void main(String[] args) throws IOException {
    FileWriter fout = null;

    date = new Date();
    aFile = new File("Data" + dateFormat.format(date) + ".csv");
    if (aFile.exists()){
       aFile.renameTo(new File("Data-" + dateFormat.format(date) + "-1.csv"));
       if (ecgjava2.ECGJAVa2View.Dialogconnected){
        ecgjava2.Dialog_box.update("\nThe following File exists: Data-" + dateFormat.format(date) + ".csv\nIt has been renamed to:" + "Data-" + dateFormat.format(date) + "-1.csv");
       }
    }
    try {
      outputFileStream = new FileOutputStream(aFile, true);
      System.out.println("File stream created successfully.");
      if (ecgjava2.ECGJAVa2View.Dialogconnected){
        ecgjava2.Dialog_box.update("*******************************************" + "\nFile stream created successfully.\n" +"*******************************************" );
      }
    } catch (FileNotFoundException e) {
      e.printStackTrace(System.err);
    }

    fout = new FileWriter(aFile);
    fout.write("Time,Light,ECG,Temp,OXI,Battery Voltage (mV), IR Value, SPO2, Fail safe, RESP Value\n");
    fout.close();
    System.out.println("Header Written Successfully");
      if (ecgjava2.ECGJAVa2View.Dialogconnected){
        ecgjava2.Dialog_box.update("*******************************************" + "\nHeader Written Successfully.\n" +"*******************************************" );
      }
  }
  public static void Writetofile(String x) throws IOException{
        fout = null;
        in = null;
        File inputFile = null;
        File outputFile = null;
        File f = null;
            try {
                inputFile = new File("Data" + dateFormat.format(date) + ".csv");
                f = inputFile;
                outputFile = new File("DataTemp.csv");
                try {
                    in = new FileReader(inputFile);
                } catch (FileNotFoundException ex) {

                }
                fout = new FileWriter(outputFile);

                int c;

                while ((c = in.read()) != -1) {
                    fout.write(c);
                }
                fout.write(x);
            } catch (IOException ex) {
            } finally {
                try {
                    fout.close();
                    in.close();
                } catch (IOException ex) {
                    JOptionPane.showMessageDialog(null, "Error closing the I/O streams", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
            inputFile.delete();
            outputFile.renameTo(f);
        }
  public static void closeWriteFile() throws IOException{
            fout.close();
            in.close();
        }
  }
