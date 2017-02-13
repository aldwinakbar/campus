/**
 * Enumeration class Nilai - write a description of the enum class here
 * 
 * @author F Astha Ekadiyanto
 * @version 1.0
 */
public enum Nilai
{
    A ("A", 3), 
    AMINUS ("A-",2.7), 
    BPLUS ("B+", 2.3), 
    B ("B", 2), 
    BMINUS ("B-", 1.7), 
    CPLUS ("C+", 1.3), 
    C ("C", 1), 
    D ("D", 0), 
    E ("E", 0), 
    F ("F", 0);
    
    private final String nilaiHuruf;
    private final double nilaiAngka;
 
    /** 
     * Nilai Constructor
     * 
     * @param nilai String - nilai value
     * @param angka double - nilai value untuk konversi
     */
    Nilai(String nilai, double angka) {
        this.nilaiHuruf=nilai;
        this.nilaiAngka=angka;
    }
    
    /**
     * Convert nilai in String into it's corresponding ENUM-Class Nilai
     * 
     * @param nilai String - nilai value in String
     * @return Nilai The ENUM-Class Nilai corresponding to String nilai.
     */
    public static Nilai parseString(String nilai) {
        if (nilai != null) {
            for (Nilai n : Nilai.values()) {
                if (nilai.equalsIgnoreCase(n.nilaiHuruf)) {
                    return n;
                }
            }
        }
        return null;
    }
    
    /**
     * Get the quantitative value of Nilai
     * 
     * @return double The nilai value in quantitative representation
     */
    public double getValue() {
        return nilaiAngka;
    }
    
    public String getHuruf() {
        return nilaiHuruf;
    }
}