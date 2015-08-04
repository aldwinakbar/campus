#include <stdio.h>
#include <stdlib.h>

float konversiKelvin (float a, float c);
float konversiCelcius(float a, float c);
float konversiKelvin (float a, float c);
float konversiFahrenheit(float a, float c);
float konversiReamur(float a, float c);
void errorCheck();
float menuSuhuOutput;

int main(void) {
	float suhuInput;
	float suhuOutput;
	int menuPilihan;

	while (1){
    system("cls");
	printf("\n    ########################\n");
	printf("    #                      #\n");
	printf("    #   PROGRAM PENGUBAH   #\n");
	printf("    #        SUHU          #\n");
	printf("    #                      #\n");
	printf("    #     Aldwin Akbar     #\n");
	printf("    #      1306368495      #\n");
	printf("    #                      #\n");
	printf("    ########################\n \n \n \n");



	printf("    ########################\n");
	printf("    #                      #\n");
	printf("    #  1. Kelvin           #\n");
	printf("    #  2. Celcius          #\n");
	printf("    #  3. Fahrenheit       #\n");
	printf("    #  4. Reamur           #\n");
	printf("    #  5. Exit             #\n");
	printf("    #                      #\n");
	printf("    ########################\n \n");

	printf("	Silahkan Pilih Tipe Suhu Anda (1 - 4): ");

	scanf( "%d", &menuPilihan );
	if (menuPilihan == 5){break;}
	if (menuPilihan < 1 || menuPilihan > 4){
		while(1){
			printf("        Salah memasukan input, pilih Tipe Suhu Anda (1 hingga 4) : ");
			scanf( "%d", &menuPilihan );
			if(menuPilihan > 0 && menuPilihan < 5){	break;}
		}
	}

	system("cls");

	if( menuPilihan == 1){
		printf("\n \n \n Masukan Suhu : ");
		scanf( "%f", &suhuInput );

	    printf("\n \n    ##########################\n");
	    printf("    #                        #\n");
		printf("    #   Diubah ke suhu apa ? #\n");
		printf("    #  1. Celcius            #\n");
		printf("    #  2. Fahrenheit         #\n");
		printf("    #  3. Reamur             #\n");
	    printf("    #                        #\n");
		printf("    ##########################\n");

		printf("     Silahkan Pilih Tipe Suhu Anda : ");
		scanf( "%f", &menuSuhuOutput );
		errorCheck();
		suhuOutput = konversiKelvin(suhuInput, menuSuhuOutput);
		printf("\n\n Suhu Anda Ialah %f \n", suhuOutput);
		}



	if( menuPilihan == 2){
		printf("\n \n \n Masukan Suhu ");
		scanf( "%f", &suhuInput );

	    printf("\n \n    ##########################\n");
	    printf("    #                        #\n");
		printf("    #   Diubah ke suhu apa ? # \n");
		printf("    #  1. Kelvin             #\n");
		printf("    #  2. Fahrenheit         #\n");
		printf("    #  3. Reamur             #\n");
	    printf("    #                        #\n");
		printf("    ##########################\n");

		printf("     Silahkan Pilih Tipe Suhu Anda : ");
		scanf( "%f", &menuSuhuOutput );
		errorCheck();
		suhuOutput = konversiCelcius(suhuInput, menuSuhuOutput);
		printf("\n\n Suhu Anda Ialah %f \n", suhuOutput);

	}


	if( menuPilihan == 3){
		printf("\n\n \n Masukan Suhu ");
		scanf( "%f", &suhuInput );
	    printf("\n \n    ##########################\n");
	    printf("    #                        #\n");
		printf("    #   Diubah ke suhu apa ? # \n");
		printf("    #  1. Kelvin             #\n");
		printf("    #  2. Celcius            #\n");
		printf("    #  3. Reamur             #\n");
	    printf("    #                        #\n");
		printf("    ##########################\n");

		printf("\n     Silahkan Pilih Tipe Suhu Anda : ");
		scanf( "%f", &menuSuhuOutput );
		errorCheck();
		suhuOutput = konversiFahrenheit(suhuInput, menuSuhuOutput);
		printf("\n\n Suhu Anda Ialah %f \n", suhuOutput);
		}


	if( menuPilihan == 4){
		printf("\n \n \n Masukan Suhu ");
		scanf( "%f", &suhuInput );
	    printf("\n \n    ##########################\n");
	    printf("    #                        #\n");
		printf("    #   Diubah ke suhu apa ? # \n");
		printf("    #  1. Kelvin             #\n");
		printf("    #  2. Celcius            #\n");
		printf("    #  3. Fahreinheit        #\n");
	    printf("    #                        #\n");
		printf("    ##########################\n");

		printf("\n     Silahkan Pilih Tipe Suhu Anda : ");
		scanf( "%f", &menuSuhuOutput );
		errorCheck();
		suhuOutput = konversiReamur(suhuInput, menuSuhuOutput);
		printf("\n\n Suhu Anda Ialah %f \n", suhuOutput);
		}

    printf("\n\n");
    system("pause");
	}

	return 0;
}



float konversiKelvin (float a, float c){
   float b;
   if(c == 1){
   b = a - 273.15;
   }
   if(c == 2){
   b =(a*1.8)-459.67;
   }
   if(c == 3){
   	b = (a-273.15)*0.8;
   }

 return b;

}

float konversiCelcius(float a, float c){
	float b;
	if(c == 1){
	b = a + 273.15;
	}
	if(c == 2){
	b = (a*1.8) + 32;
	}
	if(c == 3){
   	b = a*0.8;
   }

 return b;
}

float konversiFahrenheit(float a, float c){
	float b;
	if(c == 1){
	b = (a+459.67)*1.4;
	}
	if(c == 2){
	b = (a-32)*1.8;
	}
	if(c == 3){
   	b = (a-32)*2.25;
   }

 return b;
}

float konversiReamur(float a, float c){
	float b;
	if(c == 1){
	b = (a*0.8) + 273.15;
	}
	if(c == 2){
	b = (a*0.8);
	}
	if(c == 3){
   	b = (a*2.25)+32;
   }

 return b;
}

void errorCheck(){
if(menuSuhuOutput < 1 || menuSuhuOutput > 3){
		while(1){
			printf("       Salah memasukan input, pilih Tipe Suhu Anda (1 hingga 3) : ");
			scanf( "%f", &menuSuhuOutput );
			if(menuSuhuOutput > 0 && menuSuhuOutput < 4){	break;}
		}}

}
