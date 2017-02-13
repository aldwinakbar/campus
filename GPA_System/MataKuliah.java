
/**
 * Write a description of class MataKuliah here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class MataKuliah
{
    // instance variables - replace the example below with your own
    private String namaMK;
    private int sks;
    private int semester;
    private Nilai nilai;

    /**
     * Constructor for objects of class MataKuliah
     */
    public MataKuliah(String namaMataKuliah, int sksMK, int semesterMK)
    {
        namaMK =  namaMataKuliah;
        sks = sksMK;
        semester =semesterMK;
    }

    public String getNamaMK()
    {
        return namaMK;
    }
    
    public void setNamaMK(String namaMK)
    {
        this.namaMK = namaMK;
    }
    
    public int getSKS()
    {
        return sks;
    }
        
    public void setSKS(int sks)
    {
        if( sks > 0 && sks < 9){
            this.sks = sks;
        }
    }    
    
    public int getSemester()
    {
        return semester;
    }
    
    public void setSemester(int semester)
    {
        if( semester > 0 && semester < 13){
            this.semester = semester;
        }
    }
    
    public String getNilai()
    {
        return nilai.getHuruf();
    }
    
    public void setNilai(String nilai) 
    {
          this.nilai = Nilai.parseString(nilai);
    }
    
    public double hitungBobot()
    {
        double hasil;
        hasil = nilai.getValue() * sks;        
        return hasil;        
    }
    
}
