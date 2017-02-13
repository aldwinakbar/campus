/**
 *  Class yang menjadi simulasi untuk penggunaan aplikasi OjeKampus
 *
 * @author  Aldwin Akbar Hermanudin
 * @version UAS
 * @since   02-06-2016
 */

public class OjeKampus
{
    public static SistemPengawas sistem;

    public static void main(String args[]){
        DebugMessage.on();  // untuk memunculkan debug message
        startSistemPengawas();

        registerasiOjek();
        registerasiPengguna();

        pembelianBarang();
        antarBarang();
        antarOrang();

        DebugMessage.println("Melakukan Pemesanan");
        DebugMessage.printAllDatabase();

        menungguSistem(6000);

        DebugMessage.println("Sistem menentukan Ojek");
        DebugMessage.printAllDatabase();
          
        penggunaMembatalkan();
        ojekMembatalkan();
        
        DebugMessage.println("Melakukan Pembatalan");
        DebugMessage.printAllDatabase();
        
        menungguSistem(6000);
        
        ojekMerubahStatus();
        DebugMessage.println("Melakukan perubahan status dan update sistem");
        DebugMessage.printAllDatabase();
        penggunaMenyelesaikanPesanan();
        
        DebugMessage.println("Melakukan Penyelesaian Pesanan");
        DebugMessage.printAllDatabase();
    
        sistem.exit();

    }

    /**
     * Method startSistemPengawas untuk memulai sistem pengawasn terhadap Pesanan dan User, digunakan untuk me-sync antara kedua database tersebut
     *
     */
    public static void startSistemPengawas(){

        sistem = new SistemPengawas("Sistem Monitor");
        sistem.start();
    }

    public static void registerasiOjek(){

        Ojek ojek_satu = new Ojek(DatabaseUser.getIDOjekTerakhir(), "Aldwin", new Lokasi("FT",54,100));
        DatabaseUser.addOjek(ojek_satu);

        Ojek ojek_dua = new Ojek(DatabaseUser.getIDOjekTerakhir(), "Iddad", new Lokasi("TRUI",200,12)); 
        DatabaseUser.addOjek(ojek_dua);

        Ojek ojek_tiga = new Ojek(DatabaseUser.getIDOjekTerakhir(), "Roni", new Lokasi("Jakarta",231,12)); 
        DatabaseUser.addOjek(ojek_tiga);

    }

    public static void registerasiPengguna(){
        Pelanggan p_satu = new Pelanggan(DatabaseUser.getIDPelangganTerakhir(), "Hermanudin");
        DatabaseUser.addPelanggan(p_satu);

        Pelanggan p_dua = new Pelanggan(DatabaseUser.getIDPelangganTerakhir(), "Dean");
        DatabaseUser.addPelanggan(p_dua);

        Pelanggan p_tiga = new Pelanggan(DatabaseUser.getIDPelangganTerakhir(), "Mahdi");
        DatabaseUser.addPelanggan(p_tiga);
    }

    public static void pembelianBarang(){
        Lokasi pes_satu_awal = new Lokasi("FT", 5,3);
        Lokasi pes_satu_akhir = new Lokasi("FK", 10,21);
        Pesanan pes_satu = new Pesanan(DatabaseUser.getUserPelanggan(1), TipeLayanan.BeliBarang, pes_satu_awal, pes_satu_akhir, "Ricky", "Bonbon", 15000);
        DatabasePesanan.addPesanan(pes_satu);

    }

    public static void antarBarang(){
        Lokasi pes_satu_awal = new Lokasi("FIK", 50,41);
        Lokasi pes_satu_akhir = new Lokasi("FE", 123,21);
        Pesanan pes_satu = new Pesanan(DatabaseUser.getUserPelanggan(2), TipeLayanan.AntarBarang, pes_satu_awal, pes_satu_akhir, "Akbar", "Adriel");
        DatabasePesanan.addPesanan(pes_satu);

    }

    public static void antarOrang(){
        Lokasi pes_satu_awal = new Lokasi("FT", 3,5);
        Lokasi pes_satu_akhir = new Lokasi("FH", 31,51);
        Pesanan pes_satu = new Pesanan(DatabaseUser.getUserPelanggan(3), TipeLayanan.AntarOrang, pes_satu_awal, pes_satu_akhir, "Mahdi");
        DatabasePesanan.addPesanan(pes_satu);

    }

    public static void penggunaMembatalkan(){

        DatabasePesanan.pesananDibatalkan(DatabaseUser.getUserPelanggan(3));
    }

    public static void ojekMembatalkan(){

        DatabasePesanan.pesananDibatalkan(DatabaseUser.getUserOjek(2).getPesanan());
    }

    public static void ojekMerubahStatus(){
        
        DatabaseUser.getUserOjek(1).setStatus(StatusOjek.Antar);
    }
    
    public static void penggunaMenyelesaikanPesanan(){
        
        DatabasePesanan.hapusPesanan(DatabaseUser.getUserPelanggan(1));
    }
    
    public static void menungguSistem(int a){

        try {
            Thread.sleep(a);                 //1000 milliseconds is one second.
        } catch(InterruptedException ex) {
            Thread.currentThread().interrupt();
        }
    }
}
