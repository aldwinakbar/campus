#include <stdio.h>



float konversiKelvin (float a, float c){
   float b;
   if(c == 1){ //Celcius
   b = a - 273.15;
   }
   if(c == 2){ //Fahrenheit
   b =(a*1.8)-459.67;
   }
   if(c == 3){ //Reamur
   	b = (a-273.15) * 0.8;
   }
 
 return b;
 
}

float konversiCelcius(float a, float c){
	float b;
	if(c == 1){ //Kelvin
	b = a + 273.15;
	}
	if(c == 2){ //Fahrenheit
	b = (a*1.8) + 32;
	}
	if(c == 3){ //Reamur
   	b = a * 0.8;
   }
	
 return b;
}


float konversiFahrenheit(float a, float c){
	float b;
	if(c == 1){ //Kelvin
	b = (a+459.67)/1.4;
	}
	if(c == 2){ //Celcius
	b = (a-32) / 1.8;
	}
	if(c == 3){ //Reamur
   	b = (a-32) / 2.25;
   }
	
 return b;
}


float konversiReamur(float a, float c){
	float b;
	if(c == 1){ //Kelvin
	b = (a/0.8) + 273.15;
	}
	if(c == 2){ //Celcius
	b = a / 0.8;
	}
	if(c == 3){ //Fahrenheit
   	b = (a * 2.25)+32;
   }
	
 return b;
}


int main(void) {
	float suhuInput;
	float menuSuhuOutput;
	float suhuOutput;
	int menuPilihan;
	
	printf("#########################\n");
	printf("#                       #\n");
	printf("# Program Konversi Suhu #\n");
	printf("#                       #\n");
	printf("#  Oleh Aldwin Akbar H  #\n");
	printf("#                       #\n");
	printf("#########################\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	
	printf("#########################\n");
	printf("#     1. Kelvin         #\n");
	printf("#     2. Celcius        #\n");
	printf("#     3. Fahrenheit     #\n");
	printf("#     4. Reamur         #\n");
	printf("#########################\n");
	
	printf("\n  Silahkan Pilih Tipe Suhu Anda: ");
	scanf( "%d", &menuPilihan );
	
	if( menuPilihan == 1){
		printf("\n \n \nMasukan Suhu : ");
		scanf( "%f", &suhuInput );
		printf("\n Akan diubah ke suhu apa kawan? \n");
		
     	printf("#########################\n");
		printf("#    1. Celcius         #\n");   
		printf("#    2. Fahrenheit      #\n");
		printf("#    3. Reamur          #\n");
		printf("#########################\n");
		printf("Silahkan Pilih Tipe Suhu Anda: ");
		scanf( "%f", &menuSuhuOutput );
		printf("\n Suhu Anda Ialah : ");
		suhuOutput = konversiKelvin(suhuInput, menuSuhuOutput);
		printf("%f", suhuOutput);
		}
	
	
	
	if( menuPilihan == 2){
		printf("\n \n \nMasukan Suhu :");
		scanf( "%f", &suhuInput );
		printf("\n Akan diubah ke suhu apa kawan? \n");
		
		printf("#########################\n");
		printf("#     1. Kelvin         #\n");
		printf("#     2. Fahrenheit     #\n");
		printf("#     3. Reamur         #\n");
		printf("#########################\n");
		printf("Silahkan Pilih Tipe Suhu Anda: ");
		scanf( "%f", &menuSuhuOutput );
		printf("\n Suhu Anda Ialah : ");
		suhuOutput = konversiCelcius(suhuInput, menuSuhuOutput);
		printf("%f", suhuOutput);
	
	}
	if( menuPilihan == 3){
		printf("\n \n \nMasukan Suhu :");
		scanf( "%f", &suhuInput );
		printf("\n Akan diubah ke suhu apa kawan? \n");
		printf("#########################\n");
		printf("#     1. Kelvin         #\n");
		printf("#     2. Celcius        #\n");
		printf("#     3. Reamur         #\n");
		printf("#########################\n");
		printf("Silahkan Pilih Tipe Suhu Anda: ");
		scanf( "%f", &menuSuhuOutput );
		printf("\n Suhu Anda Ialah : ");
		suhuOutput = konversiFahrenheit(suhuInput, menuSuhuOutput);
		printf("%f", suhuOutput);
		}
	if( menuPilihan == 4){
		printf("\n \n \nMasukan Suhu :");
		scanf( "%f", &suhuInput );
		printf("\n Akan diubah ke suhu apa kawan? \n");
		printf("#########################\n");
		printf("#      1. Kelvin        #\n");
		printf("#      2. Celcius       #\n");
		printf("#      3. Fahrenheit    #\n");
		printf("#########################\n");
		printf("Silahkan Pilih Tipe Suhu Anda: ");
		scanf( "%f", &menuSuhuOutput );
		printf("\n Suhu Anda Ialah : ");
		suhuOutput = konversiReamur(suhuInput, menuSuhuOutput);
		printf("%f", suhuOutput);
		}
		
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("#########################\n");
		printf("#                       #\n");
		printf("#         SELESAI       #\n");
		printf("#                       #\n");
		printf("#########################\n");
		getchar();
	return 0;
}
