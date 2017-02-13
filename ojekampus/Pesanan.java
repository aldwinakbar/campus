
/**
 * Class Pesanan, merupakan blueprint dari informasi pesanan yang akan dilakukan. Terdapat informasi detail mengenai pesanan tersebut, beserta ojek siapa yang akan mengambilnya
 *
 * @author  Aldwin Akbar Hermanudin
 * @version UAS
 * @since   02-06-2016
 */

public class Pesanan
{
    private Ojek pelayan = null;
    private Pelanggan pengguna;
    private String pelanggan_awal;
    private String pelanggan_akhir;
    private double biaya;
    private TipeLayanan layanan;
    private Lokasi lokasi_awal;
    private Lokasi lokasi_akhir;
    private boolean diproses = false;
    private boolean dibatalkan = false;
    /**
     * Constructor for objects of class Pesanan
     */
    public Pesanan(Pelanggan pengguna,TipeLayanan layanan,Lokasi lokasi_awal, Lokasi lokasi_akhir, String pelanggan_awal)
    {
        this.pengguna = pengguna;
        this.layanan = layanan;
        this.lokasi_awal = lokasi_awal;
        this.lokasi_akhir = lokasi_akhir;
        this.pelanggan_awal = pelanggan_awal;
    }

    public Pesanan(Pelanggan pengguna,TipeLayanan layanan,Lokasi lokasi_awal, Lokasi lokasi_akhir, String pelanggan_awal, String pelanggan_akhir)
    {
        this.pengguna = pengguna;
        this.layanan = layanan;
        this.lokasi_awal = lokasi_awal;
        this.lokasi_akhir = lokasi_akhir;
        this.pelanggan_awal = pelanggan_awal;
        this.pelanggan_akhir = pelanggan_akhir;
    }

    public Pesanan(Pelanggan pengguna,TipeLayanan layanan,Lokasi lokasi_awal, Lokasi lokasi_akhir, String pelanggan_awal, String pelanggan_akhir, double biaya)
    {
        this.pengguna = pengguna;
        this.layanan = layanan;
        this.lokasi_awal = lokasi_awal;
        this.lokasi_akhir = lokasi_akhir;
        this.pelanggan_awal = pelanggan_awal;
        this.pelanggan_akhir = pelanggan_akhir;
        this.biaya = biaya;
    }

    /**
     * Method getStatusPesanan utuk me-cek status pesanan sudah diproses (diambil oleh seorang ojek) atau belum
     *
     * @return suatu nilai false jika belum ada ojek yang mengambil, true jika sudah diambil.
     */
    public boolean getStatusPesanan(){
        return diproses;
    }

    /**
     * Method pesananDiambil untuk menentukan bahwa pesanan ini sudah diambil oleh seorang ojek, dan me-set ojek itu sehingga ter-link ke pesanan ini
     *
     * @param pelayan ialah objek dari ojek yang akan mengambil pesanan ini
     */
    public void pesananDiambil(Ojek pelayan){
        diproses = true;
        dibatalkan = false;
        this.pelayan = pelayan;
        pelayan.setPekerjaan(this);
    }

    /**
     * Method getPelanggan untuk mengambil informasi dalam bentuk objek mengenai pelanggan yang me-request pesanan
     *
     * @return dalam bentuk objek Pelanggan
     */
    public Pelanggan getPelanggan(){

        return pengguna;
    }

    /**
     * Method getOjek untuk mengambil informasi dalam bentuk objek mengenai ojek yang melayani pesanan
     *
     * @return dalam bentuk objek ojek
     */
    public Ojek getOjek(){

        return pelayan;
    }

    /**
     * Method pesananDibatalakan untuk membatalkan pesanan jika dari kedua belah pihak tidak sesuai
     *
     */
    public void pesananDibatalkan(){
        dibatalkan = true;
        diproses = false;
        pelayan.pekerjaanSelesai();
        pelayan = null;
    }

    /**
     * Method getLokasiAwal untuk mengambil lokasi awal dari pesanan
     *
     * @return dalam bentuk objek Lokasi X,Y
     */
    public Lokasi getLokasiAwal(){

        return lokasi_awal;
    }

     /**
     * Method getLokasiAkhir untuk mengambil lokasi akhir dari pesanan
     *
     * @return dalam bentuk objek Lokasi X,Y
     */
    public Lokasi getLokasiAkhir(){

        return lokasi_akhir;
    }

    /**
     * Method getTipeLayanan untuk mendapatka informasi dari tipe layanan pesanan tersebut
     *
     * @return dalam bentuk enum TipeLayanan
     */
    public TipeLayanan getTipeLayanan(){

        return layanan;
    }

    /**
     * Method getPenggunaAwal untuk menerima nama yang akan pertama kali bertemu dengan ojek
     *
     * @return dalam bentuk string
     */
    public String getPenggunaAwal(){
        
        return pelanggan_awal;
    }

    /**
     * Method getPenggunaAakhir untuk menerima nama yang akan terakhir kali bertemu dengan ojek
     *
     * @return dalam bentuk string
     */
    public String getPenggunaAakhir(){
        
        return pelanggan_akhir;
    }

    /**
     * Method getBiaya untuk mengambil biaya yang diperlukan untuk melakukan pembelian barang
     *
     * @return dalam bentuk double
     */
    public double getBiaya(){

        return biaya;
    }

    public String toString(){

        if (pelayan == null){
            return pengguna.getNama() + " " + "null" + " " + layanan + " " + lokasi_awal.getX() + "," + lokasi_awal.getY() + " " + diproses;
        }
        else if (layanan == TipeLayanan.AntarBarang) {
            return pengguna.getNama() + " " + pelayan.getNama() + " " + layanan + " " + lokasi_awal.getX() + "," + lokasi_awal.getY() + " " + diproses + " " + pelanggan_awal + " " + pelanggan_akhir;
        }
        else if (layanan == TipeLayanan.BeliBarang) {
            return pengguna.getNama() + " " + pelayan.getNama() + " " + layanan + " " + lokasi_awal.getX() + "," + lokasi_awal.getY() + " " + diproses + " " + pelanggan_awal + " " + pelanggan_akhir + " " + biaya;
        }
        else {
            return pengguna.getNama() + " " + pelayan.getNama() + " " + layanan + " " + lokasi_awal.getX() + "," + lokasi_awal.getY() + " " + diproses + " " + pelanggan_awal;
        }
    }
}
