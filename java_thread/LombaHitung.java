
import java.util.Random;
/**
 * Write a description of class LombaHitung here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */

class LombaHitung implements Runnable {
   private Thread t;
   private String threadName;
   boolean suspended = false;
   private int counting;

   LombaHitung( String name){
       threadName = name;
       System.out.println(threadName +  " hadir" );
   }
   public void run() {
      System.out.println(threadName + " mulai berhitung");
      try {
          
         for(counting = 0; counting < 24; counting++) {
            System.out.println("Kontestan " + threadName + " menghitung, " + counting);
            // Let the thread sleep for a while.
            Thread.sleep(getRandomNumberInRange());
            synchronized(this) {
            while(suspended) {
               wait();
           }
          }
         }
     } catch (InterruptedException e) {
         System.out.println("Kontestan " + threadName + " interrupted");
     }
     System.out.println(threadName + " selesai menghitung");
   }

   public void start ()
   {
      System.out.println(threadName + " bersiap");
      if (t == null)
      {
         t = new Thread (this, threadName);
         t.start ();
      }
   }
   
   public Thread getThread(){
       return t;       
    }
   
   void suspend() {
      suspended = true;
   }
   synchronized void resume() {
      suspended = false;
       notify();
   }

   public int getCount(){
       
       return counting;
    }
    private static int getRandomNumberInRange()  {

        int min = 1;
        int max = 100;
        
        Random r = new Random();
        return r.nextInt((max - min) + 1) + min;
    }

}