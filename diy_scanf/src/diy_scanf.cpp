#include<stdio.h>
void inputData(char *output_char, int max_input);

int main(){

char name[20]; // variable to store the input data (only in char)

printf("\nEnter the Name : "); 

inputData(name, 20);

printf("\nYour name is : %s\n", name); 

return 0;
}

// re-create scanf
void inputData(char *output_char, int max_input){

	int word_count = 0;

		// keep reading every word until "enter" is pressed
        while((output_char[word_count] = getchar()) != '\n'){ 
			word_count++;
		} 
		output_char[word_count]='\0';   // set an "end string" to tell the char array that it is the end of that string.    
		
		// recursive until input data is below the max_input
		if (word_count+1 > max_input){ 
			printf("\n	Please input below %d word.", max_input-1);
			printf("\n	Type in the data : ");
			inputData(output_char, max_input); 
		}
}
