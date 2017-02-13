/**
* Class Enum TipeLayanan sebagai penentu Layanan-layanan yang ada
*
* @author  Aldwin Akbar Hermanudin
* @version UAS
* @since   02-06-2016
*/

public enum TipeLayanan
{
    AntarOrang ("Antar Orang"),
    AntarBarang ("Antar Barang"),
    BeliBarang ("Beli Barang");
    
    private final String deskripsi;
 
    /**
     * TipeLayanan Constructor
     *
     * @param deskripsi ialah deskripsi mengenai TipeLayanan tersebut
     */
    TipeLayanan(String deskripsi) {
        this.deskripsi=deskripsi;
    }
     
    public String toString() {
        return deskripsi;
    }
}