import java.util.*;

/**
 * Class DatabaseUsser menyimpan seluruh User Pelanggan dan Ojek dalam bentuk array
 *
 * @author  Aldwin Akbar Hermanudin
 * @version UAS
 * @since   02-06-2016
 */
public class DatabaseUser
{
    private static ArrayList<Pelanggan> pelanggan_database = new ArrayList<Pelanggan>(); 
    private static ArrayList<Ojek> ojek_database = new ArrayList<Ojek>();
    private static int id_ojek_terakhir = 1;
    private static int id_pelanggan_terakhir = 1;

    private static boolean debug_message = false;

    public static boolean addPelanggan(Pelanggan baru){
        for (Pelanggan search : pelanggan_database){

            if (search.getID() == baru.getID()){
                DebugMessage.println("Add pelanggan Failed");
                return false;
            }
        }

        pelanggan_database.add(baru);
        id_pelanggan_terakhir++;
        DebugMessage.println("Add pelanggan Success");
        return true;
    }

    public static boolean removePelanggan(int id){
        for (Pelanggan search : pelanggan_database){

            if (search.getID() == id){
                pelanggan_database.remove(search);
                return true;
            }
        }    
        return false;
    }

    public static boolean addOjek(Ojek baru){
        for (Ojek search : ojek_database){

            if (search.getID() == baru.getID()){
                DebugMessage.println("Add ojek Failed");
                return false;}
        }

        ojek_database.add(baru);
        id_ojek_terakhir++;
        DebugMessage.println("Add ojek success");
        return true;
    }

    public static boolean removeOjek(int id){
        for (Ojek search : ojek_database){

            if (search.getID() == id){
                ojek_database.remove(search);
                return true;
            }

        }

        return false;
    }

    /**
     * Method getIDOjekTerakhir untuk menentukan ID yang akan digunakan jika ada user baru yang akan me-registerasi
     *
     * @return The return value id ojek terakhir yang dapat digunakan
     */
    public static int getIDOjekTerakhir(){
        return id_ojek_terakhir;
    }

    /**
     * Method getIDPelangganTerakhir untuk menentukan ID yang akan digunakan jika ada user baru yang akan me-registerasi
     *
     * @return The return value id pelanggan terakhir yang dapat digunakan
     */
    public static int getIDPelangganTerakhir(){
        return id_pelanggan_terakhir;
    }

    /**
     * Method getUserOjek, me-search array ojek_database yang memiliki id sesuai dengan argumen.
     *
     * @param id dari ojek
     * @return Sebuah objek Ojek
     */
    public static Ojek getUserOjek(int id){
        for (Ojek search : ojek_database){
            if (search.getID() == id){
                return search;
            }
        }

        return null;
    }

    /**
     * Method getOjekDatabase untuk mengambil database ojeks 
     *
     * @return database tersebut diambil dalam bentuk array
     */
    public static ArrayList<Ojek> getOjekDatabase(){
        return ojek_database;
    }

    /**
     * Method getUserPelanggan, me-search array pelanggan_database yang memiliki id sesuai dengan argumen.
     *
     * @param id dari pelanggan
     * @return Sebuah objek Pelanggan
     */
    public static Pelanggan getUserPelanggan(int id){

        for (Pelanggan search : pelanggan_database){
            if (search.getID() == id){
                return search;
            }
        }

        return null;
    }

    /**
     * Method getPelangganDatabase untuk mengambil database pelanggan 
     *
     * @return database tersebut diambil dalam bentuk array
     */
    public static ArrayList<Pelanggan> getPelangganDatabase(){
        return pelanggan_database;
    }

}
