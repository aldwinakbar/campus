#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int x,y;
int matrix_A[10][10], matrix_B[10][10], matrix_C[10][10];
void isi_array(int array[10][10]);
void *perkalianMatrix(void *hasil);

int main(int argc, char *argv[]) {
	srand(time(NULL));
	isi_array(matrix_A);
	isi_array(matrix_B);
	pthread_t matrix[10][10];
	
   for(x = 0; x < 10; x++) {
      for(y = 0; y < 10; y++) { 
         pthread_create(&matrix[x][y],NULL,perkalianMatrix, &matrix_C[x][y]);         
      }
   }
   
   for(x = 0; x < 10; x++) {
      for(y = 0; y < 10; y++) { 
		pthread_join(matrix[x][y], NULL);
      }
   }
   
   printf("\n\n");
   printf("Matrix A \n\n");
   for(x = 0; x < 10; x++) {
      for(y = 0; y < 10; y++) {
         printf("%d ", matrix_A[x][y]);
      }
      printf("\n");
   }
   printf("\n\n");
    
   printf("Matrix B \n\n");
   for(x = 0; x < 10; x++) {
      for(y = 0; y < 10; y++) {
         printf("%d ", matrix_B[x][y]);
      }
      printf("\n");
   }
   printf("\n\n");
   
   printf("Matrix A x Matrix B =  Matrix C \n\n");
   for(x = 0; x < 10; x++) {
      for(y = 0; y < 10; y++) {
         printf("%d ", matrix_C[x][y]);
      }
      printf("\n");
   }
   printf("\n\n");
   
   return 0;
}

void isi_array(int array[10][10])
{
  int i, n;
  for (i = 0; i<10; i++)
  {
    for (n = 0; n<10; n++)
    {
      array[i][n] = rand()%10;
    }
  }
}

void *perkalianMatrix(void *hasil) {
   int *total = (int *)hasil;
   int a = x;
   int b = y;
   int c;
		
   for(c = 0; c<10; c++){
      *total += matrix_A[a][c]*matrix_B[c][b];
   }
 
   pthread_exit(0);
}
