/**
 * Class Ojek menyimpan seluruh informasi mengenai Ojek
 *
 * @author  Aldwin Akbar Hermanudin
 * @version UAS
 * @since   02-06-2016
 */

public class Ojek extends User
{
    private StatusOjek status = StatusOjek.Idle;
    private Lokasi posisi_sekarang;
    private Pesanan pesanan_sekarang = null;

    /**
     * Constructor for objects of class Ojek
     */
    public Ojek(int id, String nama, Lokasi posisi_sekarang)
    {
        super(id, nama);
        this.posisi_sekarang = posisi_sekarang;
    }

    /**
     * Method setPekerjaan menentukan bahwa Ojek tersebut sudah terlink ke suatu pesanan
     *
     * @param pesan ialah pesanannya
     */
    public void setPekerjaan(Pesanan pesan){
        status = StatusOjek.Jemput;
        pesanan_sekarang = pesan;
    }
    
    /**
     * Method getPesanan mengambil objek pesanan yang ter-link ke Ojek
     *
     * @return objek pesanan yang terlink
     */
    public Pesanan getPesanan(){

        return pesanan_sekarang;
    }
    
    /**
     * Method setPosisi untuk me-seet posisi dari ojek
     *
     * @param sekarang ialah lokasi ojek dalam bentuk objek Lokasi
     */
    public void setPosisi(Lokasi sekarang){
        
        posisi_sekarang = sekarang;
    }
    
    /**
     * Method getPosisi untuk mengambil lokasi dari ojek
     *
     * @return posisi ojek dalam bentuk objek Lokasi berisi Nama dan koordinat X,Y
     */
    public Lokasi getPosisi(){

        return posisi_sekarang;
    }
    
    /**
     * Method setStatus untuk mengubah status dari ojek
     *
     * @param status ialah tipe status yang terdapat pada class enum StatusOjek
     */
    public void setStatus(StatusOjek status){

        this.status = status;
    }

    /**
     * Method getStatus untuk me-cek status dari Ojek tersebut
     *
     * @return status yang terdapat ada class enum StatusOjek
     */
    public StatusOjek getStatus(){

        return status;
    }
    
    /**
     * Method pekerjaanSelesai untuk menentukan bahwa Ojek tersebut sudah selesai pekerjaannya
     */
    public void pekerjaanSelesai(){
        pesanan_sekarang = null;
        status  = StatusOjek.Idle;
    }
    
    public String toString() { 
        return id + " " + nama + " " + status + " " + posisi_sekarang.getX() + "," + posisi_sekarang.getY();
    } 
}
