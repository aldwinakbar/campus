#include<stdio.h>

int main()
{
int i = 0;
char name[20]; 

printf("\nEnter the Name : "); 

while((name[i] = getchar())!='\n')
        i++ ;

getch(0);
return 0;
}
