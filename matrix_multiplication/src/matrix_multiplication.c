#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int x,y;
int matrix_a[10][10], matrix_b[10][10], matrix_c[10][10];
void fill_array(int array[10][10]);
void *computeMatrix(void *result);

int main(int argc, char *argv[]) {
	srand(time(NULL));
	fill_array(matrix_a);
	fill_array(matrix_b);
	pthread_t matrix[10][10];
	
   for(x = 0; x < 10; x++) {
      for(y = 0; y < 10; y++) { 
         pthread_create(&matrix[x][y],NULL,computeMatrix, &matrix_c[x][y]);         
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
         printf("%d ", matrix_a[x][y]);
      }
      printf("\n");
   }
   printf("\n\n");
    
   printf("Matrix B \n\n");
   for(x = 0; x < 10; x++) {
      for(y = 0; y < 10; y++) {
         printf("%d ", matrix_b[x][y]);
      }
      printf("\n");
   }
   printf("\n\n");
   
   printf("Matrix A x Matrix B =  Matrix C \n\n");
   for(x = 0; x < 10; x++) {
      for(y = 0; y < 10; y++) {
         printf("%d ", matrix_c[x][y]);
      }
      printf("\n");
   }
   printf("\n\n");
   
   return 0;
}

void fill_array(int array[10][10])
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

void *computeMatrix(void *result) {
   int *total = (int *)result;
   int a = x;
   int b = y;
   int c;
		
   for(c = 0; c<10; c++){
      *total += matrix_a[a][c]*matrix_b[c][b];
   }
 
   pthread_exit(0);
}
