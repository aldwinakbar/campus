/**
* Class Enum TipeLayanan sebagai penentu Layanan-layanan yang ada
*
* @author  Aldwin Akbar Hermanudin
* @version UAS
* @since   02-06-2016
*/

public enum StatusOjek
{
    Idle ("Idle"),
    Jemput ("Menjemput"),
    Antar ("Mengantar");
    
    private final String deskripsi;
 
    /**
     * TipeLayanan Constructor
     *
     * @param deskripsi ialah deskripsi mengenai TipeLayanan tersebut
     */
    StatusOjek(String deskripsi) {
        this.deskripsi=deskripsi;
    }
     
    public String toString() {
        return deskripsi;
    }
}