/**
* Class User ialah class abstract yang menyimpan informasi umum untuk pelanggan maupun ojek
*
* @author  Aldwin Akbar Hermanudin
* @version UAS
* @since   02-06-2016
*/
public abstract class User
{
    protected int id;
    protected String nama;

    public User(int id, String nama){

        this.id = id;
        this.nama = nama;
    }

    public int getID(){
        // put your code here
        return id;
    }

    public String getNama(){

        return nama;
    }

    public void setID(int id){
        this.id = id;
    }

    public void setNama(String nama){
        this.nama = nama;
    }
}
