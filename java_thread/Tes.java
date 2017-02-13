
public class Tes {
  public static void main(String args[]) {
      int flag = 1;
      int bendera = 1;
      LombaHitung R1 = new LombaHitung( "Tomi");
      LombaHitung R2 = new LombaHitung( "Tomo");
      LombaHitung R3 = new LombaHitung( "Toma");
      
      R1.start();
      R2.start();
      R3.start();

          while(R1.getThread().isAlive() || R2.getThread().isAlive() || R3.getThread().isAlive()){
              
              if(R1.getCount() > R2.getCount() && flag == 1){
                  R1.suspend();          
                  flag = 0;
              }
              
              else if (R1.getCount() < R2.getCount() && flag == 0){
                  R1.resume();
                  flag = 1;
                }
                
              if(R2.getCount() > R3.getCount() && bendera == 1){
                  R2.suspend();          
                  bendera = 0;
              }
              
              else if (R2.getCount() < R3.getCount() && bendera == 0){
                  R2.resume();
                  bendera = 1;
                }
          }

      System.out.println("Main thread exiting.");
   }
      
}   
