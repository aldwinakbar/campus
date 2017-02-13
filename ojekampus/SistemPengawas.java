
/**
 * Class SistemPengawas ialah class yang bekerja di thread lain, yang mengawasi setiap perubahan pada DatabasePesanan.
 * class ini juga yang berfungsi sebagai dispatcher, yang menentukan ojek yang mana yang mendapatkan pesanan tertentu
 *
 * @author  Aldwin Akbar Hermanudin
 * @version UAS
 * @since   02-06-2016
 */

class SistemPengawas implements Runnable {
    private Thread t;
    private String threadName;
    private boolean program_run = true;

    SistemPengawas( String name){
        threadName = name;
        DebugMessage.println("Creating " +  threadName );
    }

    /**
     * Method run ialah method utama dari SistemPengawas, akan melakukan pengecekan terhadap DatabasePesanan setiap 5 menit untuk mencari pesanan yang kosong
     * lalu akan me-daftarkan pesanan yang kosong tersebut ke suatu Ojek
     *
     */
    public void run() {
        DebugMessage.println("Running " +  threadName );
        while (program_run){
            try {
                // jangan lupa ubah jadi 1 menit aja = 1*60*1000
                int waktu_cek = 1000;
                Thread.sleep(waktu_cek);
                for (Pesanan search : DatabasePesanan.getDatabase()) {
                    if (!search.getStatusPesanan()){
                        Ojek pelayan = temukanOjekTerdekat(search);
                        if (pelayan != null){
                            search.pesananDiambil(pelayan);
                        }
                    }
                }

            } catch (InterruptedException e) {
                DebugMessage.println("Thread " +  threadName + " interrupted.");
            }
        }
        DebugMessage.println("Thread " +  threadName + " exiting.");
    }

    /**
     * Method start akan memulai proses SistemPengawasan
     *
     */
    public void start (){
        DebugMessage.println("Starting " +  threadName );
        if (t == null)
        {
            t = new Thread (this, threadName);
            t.start ();
        }
    }

    public void join(){
        try {
            t.join();
        } catch (InterruptedException e) {
            DebugMessage.println("Interrupted.");
        }

    }

    /**
     * Method exit akan me-exit thread SistemPengawas
     *
     */
    public void exit(){
        program_run = false;
    }

    /**
     * Method temukanOjekTerdekat mencari ojek terdekat yang idle sesuai dengan lokasi_awal dari pesanan.
     * Disini akan terimplementasi algoritma untuk mencari lokasi terdekat
     *
     * @return suatu objek ojek
     */
    private Ojek temukanOjekTerdekat(Pesanan pesan){
        Lokasi pemesanan = pesan.getLokasiAwal();
        double shortest_distance = Double.MAX_VALUE;
        Ojek terdekat   = null;
        
        for (Ojek search : DatabaseUser.getOjekDatabase()){
            if (search.getStatus().equals(StatusOjek.Idle)){
                double dx = pemesanan.getX() - search.getPosisi().getX();
                double dy = pemesanan.getY() - search.getPosisi().getY();
                double distance = Math.sqrt(dx*dx + dy*dy);
                
                if (distance < shortest_distance){
                    shortest_distance = distance;
                    terdekat = search;
                }
            }
        }

        return terdekat;
    }
}