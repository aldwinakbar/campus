import java.util.*;

/**
 * Class DatabasePesanan menyimpan seluruh pesanan yang akan berinteraksi dengan Ojek dan Pelanggan di simpan pada sebuah array
 *
 * @author  Aldwin Akbar Hermanudin
 * @version UAS
 * @since   02-06-2016
 */
public class DatabasePesanan
{
    //
    private static ArrayList<Pesanan> list_pesanan = new ArrayList<Pesanan>();

    /**
     * Method addPesanan untuk menambahkan list pesanan ke sistem
     *
     * @param pesan suatu objek Pesanan
     */
    public static boolean addPesanan(Pesanan pesan){
        for(Pesanan search : list_pesanan){
            if(search.getPelanggan().getID() == pesan.getPelanggan().getID()){
                DebugMessage.print("Add pesanan failed");
                return false;
            }

        }

        list_pesanan.add(pesan);
        DebugMessage.print("Add pesanan success");
        return true;
    }

    /**
     * Method hapusPesanan untuk menghapus suatu pesanan dari list, sesuai dengan id pelanggan yang memesan
     *
     * @param pengguna ialah suatu objek Pelanggan
     */
    public static boolean hapusPesanan(Pelanggan pengguna){

        for(Pesanan search : list_pesanan){
            if(search.getPelanggan().getID() == pengguna.getID()){
                if (search.getOjek() != null){
                    search.getOjek().pekerjaanSelesai();
                }
                list_pesanan.remove(search);
                return true;
            }   
        }
        return false;
    }
    
    
    /**
     * Method hapusPesanan untuk menghapus suatu pesanan dari list, sesuai dengan objek pesanan-nya
     *
     * @param pengguna ialah suatu objek Pelanggan
     */
    public static boolean hapusPesanan(Pesanan pesan){

        for(Pesanan search : list_pesanan){
            if(search == pesan){
                if (search.getOjek() != null){
                    search.getOjek().pekerjaanSelesai();
                }
                list_pesanan.remove(search);
                return true;
            }

        }
        return false;
    }

    
    /**
     * Method getPesanan untuk menerima objek pesanan dari yang melakukan pemesanan
     *
     * @param pengguna ialah objek yang menjadi referensi yang melakukan pemesanan untuk pencarian
     * @return dapat berupa null jika tidak ditemukan
     */
    public static Pesanan getPesanan(Pelanggan pengguna){
        for(Pesanan search : list_pesanan){
            if(search.getPelanggan().getID() == pengguna.getID()){
                return search;
            }
        }

        return null;
    }

    /**
     * Method getDatabase untuk me-return seluruh list database pemesanan dalam bentuk array.
     *
     * @return berbentuk array dengan tipe objek Pesanan
     */
    public static ArrayList<Pesanan> getDatabase(){
        return list_pesanan;
    }

    /**
     * Method pesananDibatalkan akan membatalkan pemesanan dengan me-unlink pesan ke ojek 
     *
     * @param pesan ialah referensi pencarian saat me-unlink objek
     */
    public static void pesananDibatalkan(Pesanan pesan){ 
        for (Pesanan search : list_pesanan){
            if(search == pesan){
                search.pesananDibatalkan();
            }
        }

    }

     /**
     * Method pesananDibatalkan akan membatalkan pemesanan dengan me-unlink pesan ke ojek 
     *
     * @param pesan ialah referensi pencarian saat me-unlink objek
     */
    public static void pesananDibatalkan(Pelanggan pengguna){ 
        for (Pesanan search : list_pesanan){

            if(search.getPelanggan().getID() == pengguna.getID()){
                search.pesananDibatalkan();
            }
        }

    }
}
