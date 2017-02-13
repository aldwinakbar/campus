
/**
* Class Posisi menyimpan data mengenai lokasi suatu tempat dalam x dan y
*
* @author  Aldwin Akbar Hermanudin
* @version UAS
* @since   02-06-2016
*/
public class Lokasi
{
    // instance variables - replace the example below with your own
    private double x;
    private double y;
    private String nama_lokasi;

    /**
     * Constructor for objects of class Posisi
     */
    public Lokasi(String nama_lokasi,double x, double y)
    {
        this.x = x;
        this.y = y;
        this.nama_lokasi = nama_lokasi;
    }
    
    /**
     * Method getX ialah untuk mengambil koordinat X dari ojek
     *
     * @return dalam bentuk cartesian
     */
    public double getX(){
        return x;
    }
    
    /**
     * Method getY ialah untuk mengambil koordinat Y dari ojek
     *
     * @return dalam bentuk cartesian
     */
    public double getY(){
        return y;
    }
    
    /**
     * Method getNama untuk mengambil nama dari lokasi tersebut
     *
     * @return dalam bentuk string
     */
    public String getNama(){
        return nama_lokasi;
    }
}
