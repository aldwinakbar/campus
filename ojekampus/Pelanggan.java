
/**
 * Class Pelanggan menyimpan seluruh informasi mengenai Pelanggan
 *
 * @author  Aldwin Akbar Hermanudin
 * @version UAS
 * @since   02-06-2016
 */
public class Pelanggan extends User
{
    public Pelanggan(int id, String nama)
    {
        super(id,nama);
    }

    public String toString() { 
        return id + " " + nama;
    } 

}
