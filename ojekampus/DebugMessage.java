
/**
 * Class yang digunakan sebagai pengganti System.out.print agar dapat melakukan peng-controlan lebih, supaya dapat me-disable atau me-enable debug message
 * 
 * @author  Aldwin Akbar Hermanudin
 * @version UAS
 * @since   02-06-2016
 */
public class DebugMessage
{
    private static boolean debug_status = false;

    public static void print(String debug){
        if (debug_status){
            System.out.print(debug);
        }
    }

    public static void println(String debug){
        if (debug_status){
            System.out.println(debug);
        }
    }
    
    public static void on(){
        debug_status = true;
    }
    
    public static void off(){
        debug_status = false;
    }
    
      
    public static void printOjekDatabase(){
        DebugMessage.println("\nPrinting Ojek Database");
        for (Ojek search : DatabaseUser.getOjekDatabase()){
            DebugMessage.println(search.toString());
        }
        DebugMessage.print("\n");
        
    }
    
    public static void printPelangganDatabase(){
        DebugMessage.println("\nPrinting Pelanggan Database");
        for (Pelanggan search : DatabaseUser.getPelangganDatabase()){
            DebugMessage.println(search.toString());
        }
        DebugMessage.print("\n");
    }
    
    public static void printPesananDatabase(){
        DebugMessage.println("\nPrinting Pesanan Database");
        for (Pesanan search : DatabasePesanan.getDatabase()){
            DebugMessage.println(search.toString());
        }
        DebugMessage.print("\n");
    }
    
    public static void printAllDatabase(){
        
        print("\n########################################\n");
        printOjekDatabase();
        printPelangganDatabase();
        printPesananDatabase();
         print("########################################\n\n");
    }
}
