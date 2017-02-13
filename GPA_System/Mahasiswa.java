import java.util.ArrayList;

/**
 * Write a description of class Mahasiswa here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Mahasiswa
{
    // instance variables - replace the example below with your own
    private String nama;
    private String npm;
    private ArrayList<MataKuliah> mkAmbil;
    private ArrayList<MataKuliah> mkAmbilTerakhir;
    private ArrayList<MataKuliah> mkAmbilTerbaik;
    
    public static void main(String[] args)
    {
        Mahasiswa new_mahasiswa = new Mahasiswa("Aldwin Akbar Hermanudin", "1306368495");
        MataKuliah[] list_mata_kuliah = new MataKuliah[7];
        list_mata_kuliah[0] = new MataKuliah("Dasar Teknik Komputer",3,1);
        list_mata_kuliah[0].setNilai("A");
        list_mata_kuliah[1] = new MataKuliah("MPKT A",6,2);
        list_mata_kuliah[1].setNilai("B+");
        list_mata_kuliah[2] = new MataKuliah("Pemrograman Berorientasi Objek",3,5);
        list_mata_kuliah[2].setNilai("A-");
        list_mata_kuliah[3] = new MataKuliah("Dasar Sistem Digital",2,3);
        list_mata_kuliah[3].setNilai("C+");
        list_mata_kuliah[4] = new MataKuliah("Dasar Elektronika",4,4);
        list_mata_kuliah[4].setNilai("B-");
        list_mata_kuliah[5] = new MataKuliah("Matematika 1",3,2);
        list_mata_kuliah[5].setNilai("B");
        list_mata_kuliah[6] = new MataKuliah("Fisika Dasar 1",4,2);
        list_mata_kuliah[6].setNilai("B+");
        for(int i = 0; i < 7; i++){
            new_mahasiswa.ambilMK(list_mata_kuliah[i]);
        }
        
        System.out.println("Data Prestasi Mahasiswa");
        System.out.println("Nama  : " + new_mahasiswa.getNama());
        System.out.println("NPM   : " + new_mahasiswa.getNpm());
        System.out.println("Bobot : " + new_mahasiswa.getTotalBobot());
        System.out.println("SKS   : " + new_mahasiswa.getTotalSKS());
        System.out.println("IPK   : " + new_mahasiswa.hitungIPK("semu"));
        
        MataKuliah matakuliah_ulangan = new MataKuliah("Dasar Sistem Digital",2,3);
        matakuliah_ulangan.setNilai("A");
        new_mahasiswa.ambilMK(matakuliah_ulangan);
        
        System.out.println("\n\nData Prestasi Mahasiswa Setelah Mengulang Dasar Sistem Digital");
        System.out.println("Nama          : " + new_mahasiswa.getNama());
        System.out.println("NPM           : " + new_mahasiswa.getNpm());
        System.out.println("Bobot         : " + new_mahasiswa.getTotalBobot());
        System.out.println("SKS           : " + new_mahasiswa.getTotalSKS());
        System.out.println("IPK Semu      : " + new_mahasiswa.hitungIPK("semu"));
        System.out.println("IPK Terbaik   : " + new_mahasiswa.hitungIPK("terbaik"));
        System.out.println("IPK Terakhir  : " + new_mahasiswa.hitungIPK("terakhir"));
        
    }

    /**
     * Constructor for objects of class Mahasiswa
     */
    public Mahasiswa(String namaMhs, String npmMhs)
    {
        // initialise instance variables
        nama = namaMhs;
        npm = npmMhs;
        mkAmbil = new ArrayList<MataKuliah>();
        mkAmbilTerbaik= new ArrayList<MataKuliah>();
        mkAmbilTerakhir= new ArrayList<MataKuliah>();
    }
    
    public String getNama()
    {
        return nama;
    }
    
    public void setNama(String namaMhs)
    {
        nama = namaMhs;
    }
    
    public String getNpm() 
    {
        return npm;
    }
    
    public void setNpm(String npmMhs)
    {
        npm = npmMhs;
    }
    
    public void ambilMK(MataKuliah mk)
    {
        // Untuk fitur tambahan no.6
        boolean status_matakuliah = true;
        for (int i = 0; i < mkAmbil.size(); i++) {
            if(mk.getNamaMK().equals(mkAmbil.get(i).getNamaMK()) && mk.getSemester() > mkAmbil.get(i).getSemester()){
                mkAmbilTerakhir.add(mk);
                status_matakuliah = false;
                
                if(Nilai.parseString(mk.getNilai()).getValue() > Nilai.parseString(mkAmbil.get(i).getNilai()).getValue()){
                    mkAmbilTerbaik.add(mk);
                }
            
            }            
        }
                        
        if(status_matakuliah){
            mkAmbil.add(mk);
        }
    }
    
    public double getTotalBobot(){
        double totalBobot = 0;
        for (int i = 0; i < mkAmbil.size(); i++) {
            totalBobot = totalBobot + mkAmbil.get(i).hitungBobot();
        }
        return totalBobot;
    }
    
    public int getTotalSKS(){
        int totalSKS = 0;
        for (int i = 0; i < mkAmbil.size(); i++) {
            totalSKS = totalSKS +mkAmbil.get(i).getSKS();
        }
        return totalSKS;
    }
    
    public double hitungIPK(String input_metode){
        
        if (input_metode.equalsIgnoreCase("semu")){
            return hitungIPKSemu();
        }
        
        else if (input_metode.equalsIgnoreCase("terakhir")){
            return hitungIPKLain(mkAmbilTerakhir);
        }
        
        else if (input_metode.equalsIgnoreCase("terbaik")){
             return hitungIPKLain(mkAmbilTerbaik);
        }
        
        else {
            return 0;
        }

        
    }
    
    private double hitungIPKSemu(){
        double totalBobot = 0;
        int totalSKS = 0;
        
        for (MataKuliah n : mkAmbil) {
            totalBobot = totalBobot + n.hitungBobot();
            totalSKS = totalSKS +n.getSKS();
        }
        
        
        for (MataKuliah n : mkAmbilTerakhir) {
                totalBobot = totalBobot + n.hitungBobot();
                totalSKS = totalSKS +n.getSKS();
        }
        
        return totalBobot/totalSKS;
               
    }
    
    private double hitungIPKLain(ArrayList<MataKuliah> tipe_matakuliah){
        
        double totalBobot = 0;
        int totalSKS = 0;
        
        for (MataKuliah n : mkAmbil) {
            
            boolean flag = false;
            
            for (MataKuliah o : tipe_matakuliah) {
                if(n.getNamaMK().equals(o.getNamaMK())){
                    
                    totalBobot = totalBobot + o.hitungBobot();
                    totalSKS = totalSKS + o.getSKS();
                    flag = true;
                }            
            }
            
            if (!flag){
                totalBobot = totalBobot + n.hitungBobot();
                totalSKS = totalSKS +n.getSKS();
            }
        }
        
        return totalBobot/totalSKS;
    }
}
