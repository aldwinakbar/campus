#include <unistd.h>    
#include <sys/types.h>  
#include <errno.h>     
#include <stdio.h>      
#include <stdlib.h>    
#include <pthread.h>    
#include <string.h>    
#include <time.h>     
#include <semaphore.h> 


void antrianPKM ( void *ptr );
void kerjaDokter(void *ptr);
void printWaktu();

sem_t mutex;
sem_t checkKursi;
int counter;
int docterExit = 0, docterAvailable = 1;
int sisaAntrian;

int main()
{
	srand(time(NULL));
    int x;
    pthread_t mahasiswa[16];	// thread mahasiswa
    pthread_t dokter;			// thread dokter
    int mahasiswaID[16];
    
    for (x = 0; x<10; x++){mahasiswaID[x] = x+1;}	// generate ID mahasiswa
    
    sem_init(&checkKursi, 0, 4); 	// semaphore untuk antrian kursi
    sem_init(&mutex, 0, 1);     	// semaphore untuk pengobatan di dalem kantor dokter
    
                           
    // Create thread dokter dan mahasiswa     
    for(x = 0 ; x < 10; x++){ pthread_create (&mahasiswa[x], NULL, (void *) &antrianPKM, (void *) &mahasiswaID[x]);}
    pthread_create (&dokter, NULL, (void *) &kerjaDokter, NULL);
    
	for(x = 0 ; x < 10; x++){ pthread_join(mahasiswa[x], NULL);}
	
	docterExit = 1;
	pthread_join(dokter, NULL);
    sem_destroy(&mutex); 
    sem_destroy(&checkKursi); 
 
    exit(0);
}

void antrianPKM ( void *ptr )
{
     
    int x; 
    x = *((int *) ptr);
   
   
	int waitCritical = rand()%10000000;		// random waktu pengobatan
	int waitOffPKM 	 = rand()%100000000;	// random keluar pkm
		   
	while(1){
			
			if (!sem_trywait(&checkKursi)) {  		/* 		Check Kursi Penuh atau Tidak		*/  
				printf("Mahasiswa %d: Masuk Antrian Kursi...\n", x);
				
				while(!docterAvailable); // menunggu dikursi hingga dokter kembali
				
				/* 		ANTRIAN KURSI DISINI		*/   
				sem_wait(&mutex);
				/* START CRITICAL REGION */
				printf("Mahasiswa %d: Dalam Pengobatan...\n", x);
				printf("Mahasiswa %d: Periksa selama %d useconds...\n", x,waitCritical);
				usleep(waitCritical);
				/* END CRITICAL REGION */    
			
				sem_post(&mutex); 
				sem_post(&checkKursi);   
				printf("Mahasiswa %d: Keluar PKM...\n", x);
				
				/* 		ANTRIAN KURSI SELESAI		*/  
				break;
			} 
			else {
				printf("Mahasiswa %d: Antrian Kursi Penuh, keluar selama %d useconds\n", x, waitOffPKM);
				usleep(waitOffPKM);
			}	
			
		}
			
    
    pthread_exit(0); /* exit thread */
}


void kerjaDokter(void *ptr){
	
	int waktuKerja = rand()%10000000;		// random waktu kerja dokter
	int waktuLain  = rand()%10000000;		// random waktu libur
		
	while(docterExit == 0){
		
		docterAvailable = 1;					// saatnya kerja
		printf("\t\t\t\tDokter ada di Kantor. \n");
		usleep(waktuKerja);						// kerja selama random waktu
		
		sem_getvalue(&checkKursi, &sisaAntrian); // cek antrian masih ada atau tidak
		if (sisaAntrian == 4){
			docterAvailable = 0;					// antrian kosong dan saatnya pulang
			printf("\t\t\t\tDokter keluar PKM %d useconds.\n",waktuLain);
			sem_wait(&checkKursi);
			usleep(waktuLain);
			sem_post(&checkKursi);
		}
		
		
	}
	
	pthread_exit(0); 
	
	}
