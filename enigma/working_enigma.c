#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Struct untuk menyimpan data setiap titik di rotor */
struct rotorNode {
    int data;
    int flag;
    int notch;
    struct rotorNode *nextPtr;
};

typedef struct rotorNode RotorNode;
typedef RotorNode *RotorNodePtr;

void clear();
void pause();
void firstSetup();
int fullEncrypt(int input);
int rotate( RotorNodePtr *sPtr);
int isEmpty( RotorNodePtr sPtr );
void setRotor(char *array_settings);
void subMenu(int menu, char *sentence);
int checkRotor( RotorNodePtr currentPtr);
int encrypt( RotorNodePtr currentPtr, int order_input);
void insert( RotorNodePtr *sPtr, int value, int notch_input);
int reverseEncrypt( RotorNodePtr currentPtr, int order_input);
void inputData(char *output_char, int max_input, int mode, int menu);


char reflector[27] = "-QYHOGNECVPUZTFDJAXWMKISRBL";     // Settingan awal rotor reflector
char plugBoard[27] = "-IMETCGFRAYSQBZXWLHKDVUPOJN";     // Settingan awal plug board
char rotor_wiring[3][27];                               // wiring internal setiap rotor
RotorNodePtr rotor[3];                                  // objek dari ke 3 rotor


int main()
{
    int i;
    rotor[0] = NULL;
    rotor[1] = NULL;
    rotor[2] = NULL;
    char menuPilihan;
	int menu;
	char input_sentence[1024];

    firstSetup();   // Set semua nilai awal dari rotor, plugboard, reflector
	while (1){      // looping hingga user memilih exit
        clear();
		printf("\n	  ########################\n");
		printf("	  #                      #\n");
		printf("  	  #    Enigma Machine    #\n");
		printf("  	  #                      #\n");
		printf("  	  #    German Railway    #\n");
		printf("  	  #        model         #\n");
		printf("  	  #                      #\n");
		printf("  	  ########################\n \n \n");

		printf("    #####################################\n");
		printf("    #                                   #\n");
		printf("    #  1. Encrypt or Decrypt a sentence #\n");
		printf("    #  2. Encrypt or Decrypt a file     #\n");
		printf("    #  3. Encryption Settings           #\n");
		printf("    #  4. Exit                          #\n");
		printf("    #                                   #\n");
		printf("    #####################################\n \n");

		printf("	Enter a menu : ");

		inputData(&menuPilihan, 0, 1, 4);       // meminta menu yang dipilih
		menu =  atoi(&menuPilihan);

        /* kondisi-kondisi jika memilih menu-menu masing-masing */
		if(menu == 1){
			subMenu(1,input_sentence);
		}

		else if(menu == 2){
			subMenu(2,input_sentence);
		}

		else if(menu == 3){
			subMenu(3,input_sentence);
		}

		else if(menu == 4){
			break;
		}
	}

	return 0;
}

// isi dari setiap menu pada fungsi main.
void subMenu(int menu, char *sentence){
	int i = 0, j;
	int sub_menu;
    int flag = 0;
	char rotor_plug_settings[27];
	char sub_menu_pilihan;

	if(menu == 1){          // isi dari menu 1

		clear();
		printf("\n	  #######################################\n");
		printf("	  #                                     #\n");
		printf("  	  #    Encrypt or Decrypt a sentence	#\n");
		printf("  	  #                                     #\n");
		printf("  	  #######################################\n \n \n");

		printf("	Just typed in the sentence and it will decrypt/encrypt.\n");
		printf("	Make sure it's below 1024 words.\n\n");


		printf("	Enter a sentence : ");
		inputData(sentence,1024,0,0);       // meminta kalimat yang akan di encrypt, disimpan pada array sentence


		while (sentence[i] != '\0'){        // loop hingga akhir dari string

            sentence[i] = toupper(sentence[i]);
			if(isalpha(sentence[i])){       // meng-encrypt setiap huruf alfabet
			sentence[i] = fullEncrypt(sentence[i] - 64) + 64;       // meng-encrypt dan merubahnya lagi jadi char
			}

			i++;
		}

		clear();
		printf("\n	  #######################################\n");
		printf("	  #                                     #\n");
		printf("  	  #    Encrypt or Decrypt a sentence	#\n");
		printf("  	  #                                     #\n");
		printf("  	  #######################################\n \n \n");

		printf("	The encrypted or derypted sentence : %s",sentence);         // menampilkan kalimat yang telah di encrypt

		pause();
	}

	else if(menu == 2){         // isi dari menu 2

        char c;
        clear();
		printf("\n	  #######################################\n");
		printf("	  #                                     #\n");
		printf("  	  #    Encrypt or Decrypt a file    	#\n");
		printf("  	  #                                     #\n");
		printf("  	  #######################################\n \n \n");

		printf("	Just type in the filename and extension, it will be decrypted/encrypted.\n");
		printf("	Make sure its in the same place with the program.\n\n");


		printf("	Type in the filename: ");
		inputData(sentence,1024,0,0);       // meminta input nama file dan ekstensinya
        char output_file[128];
        FILE *wFile, *rFile;                // deklarasi variable untuk membuka file

        strcpy(output_file,sentence);       // mengubah nama input file menjadi output
        strcat(output_file, ".enigma");     // file dengan menambahakan akhiran .enigma

        wFile = fopen (output_file,"w");    // membuka file output
        rFile=fopen (sentence,"r");         // membuka file input

        if (wFile!=NULL && rFile!=NULL) {   // jika membuka kedua file berhasil

            while ((c = fgetc(rFile)) != EOF){      // looping dan mengambil setiap char dari file
                c = toupper(c);
                if(isalpha(c)){         // jika char tersebut alfabet maka lakukan
                    c = fullEncrypt(c - 64) + 64;   // enkripsi char tersebut
                    c = tolower(c);
                }
                fputc ( c , wFile );    // menulis ke output file
            }

        fclose (wFile);
        fclose (rFile);
        printf("\n\t");
        printf("Encrypt/Decrypt the file is a success!");
        }

        else{
            printf("\n\t");
            perror ("Error opening file");
        }
        pause();
	}

	else if(menu == 3){

		clear();
		printf("\n	  ############################\n");
		printf("	  #                          #\n");
		printf("  	  #    Encryption Settings   #\n");
		printf("  	  #                          #\n");
		printf("  	  ############################\n \n \n");

		printf("       ##################################\n");
		printf("       #                                #\n");
		printf("       #  1. Show Encryption Settings   #\n");
		printf("       #  2. Set Rotor Settings         #\n");
		printf("       #  3. Set Plug Board             #\n");
		printf("       #  4. Reset Settings             #\n");
		printf("       #  5. Back                       #\n");
		printf("       #                                #\n");
		printf("       ##################################\n \n");

		printf("	Enter a menu : ");

		inputData(&sub_menu_pilihan, 0, 1, 5);      // meminta pilihan menu
		sub_menu =  atoi(&sub_menu_pilihan);

		if (sub_menu == 1){     // isi dari submenu 1
			clear();
			printf("	  ################################\n");
			printf("	  #                              #\n");
			printf("  	  #    Show Encryption Settings  #\n");
			printf("  	  #                              #\n");
			printf("  	  ################################\n \n \n");

            /* memprint lokasi titik rotor dan isi dari array plugboard */
			printf("	Rotor Settings are : %c%c%c\n", checkRotor(rotor[2]) + 64,checkRotor(rotor[1]) + 64,checkRotor(rotor[0]) + 64);
			printf("	                          ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
			printf("	Plug Board Settings are : ");

			for( i = 1; i < 27; i++){
                printf("%c",plugBoard[i] + 64);
			}
			pause();
		}

		else if (sub_menu == 2){        // isi dari submenu 2

            clear();
			printf("	  #########################\n");
			printf("	  #                       #\n");
			printf("  	  #   Set Rotor Settings  #\n");
			printf("  	  #                       #\n");
			printf("  	  #########################\n \n");

            printf("\n\t Input the settings of each rotor. example : AQZ");

            printf("\n	Enter a settings : ");
			inputData(rotor_plug_settings,4,0,0);   // input 3 buah kata untuk rotor settings
            i = 0;
			while (rotor_plug_settings[i] != '\0'){    // looping hingga akhr string
				if (!isalpha(rotor_plug_settings[i])){      // jika terdapat non-alfabat maka, update setting gagal.
					printf("\n        Your Input is Invalid. \n ");
					flag = 1;
					pause();
					break;
				}

				rotor_plug_settings[i] = toupper(rotor_plug_settings[i]);
				i++;
			}

			if( i != 3 && flag == 0){   // Jika inputnya kurang dari 3 huruf maka gagal update settings

				printf("\n		Your Input is Invalid. \n ");
				flag = 1;
				pause();
			}

			if(flag == 0) setRotor(rotor_plug_settings); // jika bberhasil maka update rotor settings
		}

		else if (sub_menu == 3){    // isi dari submenu ke 3
            clear();
			printf("	  #########################\n");
			printf("	  #                       #\n");
			printf("  	  #    Set Plug Board     #\n");
			printf("  	  #                       #\n");
			printf("  	  #########################\n\n");

			printf("\n\t Pair every alphabet below with another word. It could be");
			printf("\n\t any alphabet. If you pair A with C, C must be pair with A,");
			printf("\n\t and so on. If you don't want to pair anything, input the");
			printf("\n\t same alphabet as the one above it.");
			printf("\n\t Example : IMETCGFRAYSQBZXWLHKDVUPOJN");

			printf("\n\n\n\t                                  ABCDEFGHIJKLMNOPQRSTUVWXYZ");
			printf("\n\tTyped in the PlugBoard Settings : ");
			inputData(rotor_plug_settings,27,0,0);      // input berupa 26 huruf dan dimasukan ke array rotor_plug_settings

			while (rotor_plug_settings[i] != '\0'){     // looping hingga akhir string
				if (!isalpha(rotor_plug_settings[i])){  // // jika terdapat non-alfabat maka, update setting gagal.
					printf("\n		Your Input is Invalid.");
					flag = 1;
					pause();
					break;
				}
				rotor_plug_settings[i] = toupper(rotor_plug_settings[i]);
				i++;
			}

			if( i != 26 && flag == 0){      // Jika inputnya kurang dari 26 huruf maka gagal update settings

				printf("\n		Your Input is Invalid. \n ");
				flag = 1;
				pause();
			}

			if(flag == 0){
                for (i = 0; i < 27; i++) plugBoard[i+1] = rotor_plug_settings[i] - 64;  // jika berhasil masukan ke array plugboard dan ubah menjadi angka
			}
		}

		else if (sub_menu == 4){        // me reset semuanya ke settingan awal
            strcpy(plugBoard, "-IMETCGFRAYSQBZXWLHKDVUPOJN");
            for(i = 0 ; i < 27; i++)plugBoard[i] -= 64;
			rotor_plug_settings[0] = 'A';
			rotor_plug_settings[1] = 'A';
			rotor_plug_settings[2] = 'A';
			setRotor(rotor_plug_settings);
		}

		else if (sub_menu == 5){    // exit
		}
	}
}

/* untuk membuat objek rotor tersebut agar dapat mensimulasikan berputar */
void insert( RotorNodePtr *sPtr, int value, int notch_input)
{
    RotorNodePtr newPtr = NULL;          // pointer untuk titik baru
    RotorNodePtr previousPtr = NULL;     // pointer ke titik sebelumnya
    RotorNodePtr currentPtr = NULL;      // pointer ke titik sekarang

    newPtr = malloc( sizeof( RotorNode ) );     // membuat pointer titik baru sebesar struct RotorNode

    if ( newPtr != NULL ) {         // lakukan jika berhasil mebuat titik aru
       /* men-set nilai */
        newPtr->data = value;
        newPtr->notch = notch_input;
        newPtr->flag = 0;
        newPtr->nextPtr = NULL;
        previousPtr = NULL;
        currentPtr = *sPtr;

        /* looping hingga akhir dari list */
        while ( currentPtr != NULL ) {
            previousPtr = currentPtr;          // titik sekarang jadi titik sebelumnya
            currentPtr = currentPtr->nextPtr;  // pindah ke titik selanjutnya
        }

        /* jika list masih kosong maka lakukan */
        if ( previousPtr == NULL ) {
            newPtr->nextPtr = *sPtr;
            newPtr->flag = 2; // menunjukan bahwa titik pertama di rotor
            *sPtr = newPtr;
        }
        else {      // me-link titik baru ke list yang ada
            previousPtr->nextPtr = newPtr;

            if (notch_input == 26)          // jika sudah alfabet terakhir, maka next
                newPtr->nextPtr = *sPtr;    // nextptr node terakhir diarahkan ke node pertama
                                            // sehingga membentuk lingkaran seperti rotor

            else
                newPtr->nextPtr = currentPtr;   // jika tidak maka menunjuk ke NULL
        }

    }
}

/* untuk memutar rotor tersebut */
int rotate( RotorNodePtr *sPtr)
{
    /* inisialisasi nilai awal */
    int i = 0;
    RotorNodePtr previousPtr = NULL;
    RotorNodePtr currentPtr = NULL;
    previousPtr = NULL;
    currentPtr = *sPtr;
    previousPtr = currentPtr;

        /* looping hingga ketemu titik pertama di rotor
            looping ini untuk memutar rotor dan tetap mem-
            paralelkan output rotor dengan posisi inputnya */
        while ( i < 1 ) {
            currentPtr->data = currentPtr->data - 1;    // jika berputar sekali, outputnya ikut berpindah sekali
            if (currentPtr->data == 0) currentPtr->data = 26;   // jika ada nilai yang 0, diubah menjadi 26 berarti ada diakhir titi rotor
            currentPtr = currentPtr->nextPtr;   // pindah ke titik selanjutnya
            if(currentPtr->flag == 2) i++;
        }

        currentPtr = currentPtr->nextPtr;   // diputar sekali, pindah ke titik berikutnya
        currentPtr->flag = 2;               // menandakan bahwa titik ini yang lagi ditunjuk
        previousPtr->flag = 0;
        *sPtr = currentPtr;
        return previousPtr->notch;
}



/* cek apakah list kosong */
int isEmpty( RotorNodePtr sPtr ){
    return sPtr == NULL;
}

/* check titik yang lagi ditunjuk di linked list */
int checkRotor( RotorNodePtr currentPtr){

    if ( currentPtr == NULL ) {
        printf( "List is empty.\n\n" );
        return 1;
    }

    else {
		return currentPtr->notch;
    }
}

/* mengenkripsi dengan me-return nilai hasil enkripsi di satu rotor, dari kanan ke kiri*/
int encrypt( RotorNodePtr currentPtr, int order_input){

    int i = 1;
    if ( currentPtr == NULL || order_input > 26 ) {
        return -1;
    }

    else {
        while ( i != order_input ) {        // looping hingga mencapai titik ke-n
            currentPtr = currentPtr->nextPtr;
            i++;
        }

        return currentPtr->data;        // mem-return isi data di titik tersebut, yaitu char hasil enkripsi
    }
}

/* mengenkripsi dengan me-return nilai hasil enkripsi di satu rotor, dari kiri ke kanan */
int reverseEncrypt( RotorNodePtr currentPtr, int order_input){

    int i = 1;
    if ( currentPtr == NULL || order_input > 26 ) {
            return -1;
    }

    else {
        while ( currentPtr->data != order_input ) { // looping hingga bertemu node yang berisi n
            currentPtr = currentPtr->nextPtr;
            i++;
        }

            return i;       // me-return lokasi node yang berisi data
    }

}

/* meng-inisialisasi mesin engima dengan memasukan settingan awal */
void firstSetup(){
    int i,j;

    // settingan awal rotor sesuai model german railway (http://en.wikipedia.org/wiki/Enigma_rotor_details)
    strcpy(rotor_wiring[0], "JGDQOXUSCAMIFRVTPNEWKBLZYH");
    strcpy(rotor_wiring[1], "NTZPSFBOKMWRCJDIVLAEYUXHGQ");
    strcpy(rotor_wiring[2], "JVIUBHTCDYAKEQZPOSGXNRMWFL");

    /* mengubah huruf menjadi angka untuk di rotor */
    for (i = 0 ; i < 3; i++){
        for(j = 0 ; j < 26; j++){
        rotor_wiring[i][j] -= 64; //All Upper Case convert into int
        }
    }
    for(i = 0 ; i < 27; i++){
        reflector[i] -= 64;
    }

    for(i = 0 ; i < 27; i++){
        plugBoard[i] -= 64;
    }

    /* memasukan array rotor_wiring ke linked list rotor, agar menjadi sebuah lingkaran atau rotor */
    for(i = 0; i < 3; i++){
        for(j = 0; j < 26 ; j++){
            insert( &rotor[i], rotor_wiring[i][j],j+1);
        }
    }

}

/* fungsi yang me-simulasikan saat satu karakter ditekan pada mesin enigma */
int fullEncrypt(int input){

    /* rotor-rotor akan berputar */
    if (rotate(&rotor[0]) == 26){
        if(rotate(&rotor[1]) == 26){
            if(rotate(&rotor[2]) == 26){

            }
            else{}
        }
        else {}
    }
    else {}

    input = plugBoard[input];                   // huruf akan melewati plugBoard
    input = encrypt(rotor[0], input);           // terenkripsi di rotor paling kanan
    input = encrypt(rotor[1], input);           // terenkripsi di rotor tengah
    input = encrypt(rotor[2], input);           // terenkripsi di rotor paling kiri
    input = reflector[input];                   // terenkripsi dan dibalikan di rotor reflector
    input = reverseEncrypt(rotor[2], input);    // terenkripsi ulang di rotor paling kiri
    input = reverseEncrypt(rotor[1], input);    // terenkripsi ulang di rotor tengah
    input = reverseEncrypt(rotor[0], input);    // terenkripsi ulang di rotor paling kanan
    input = plugBoard[input];                   // melewati plugboard lagi

    return input;

}

/* me-set posisi rotor */
void setRotor(char *array_settings){

	int i = 0;
	/* looping untuk mengubah input char menjadi angka */
    while(i != 3){
        array_settings[i] = toupper(array_settings[i]) - 65;
        if (array_settings[i] == 0) array_settings[i] = 26;
        i++;
    }
    /* diputar hingga posisi yang sesuai dengan nilai input */
	while (rotate(&rotor[2]) != array_settings[0]);
	while (rotate(&rotor[1]) != array_settings[1]);
	while (rotate(&rotor[0]) != array_settings[2]);
}

/* untuk mengambil input dari user, pengganti scanf() */
/* mode 1 untuk menu, mode 2 untuk input string */
void inputData(char *output_char, int max_input, int mode, int menu){

	int i = 0, word_count;
	if (mode == 0){

        for(word_count=0; (output_char[word_count] = getchar()) != '\n' ; word_count++){ ;} // masukan input ke array hingga ketemu enter
		output_char[word_count]='\0';       // me-set sebagai akhir dari sebua string
		if (word_count+1 > max_input){      // jika input lebih besar dari array maka, minta ulang input
			printf("\n	Please input below %d character.", max_input-1);
			printf("\n	Type in the character : ");
			inputData(output_char, max_input, mode, menu); // rekursif hingga input memenuhi kondisi
			clear();
		}
	}

	else if (mode == 1){

		*output_char = getchar();   // masukan input pertama ke variable
		while (getchar() != '\n'){i++;};    // looping untuk me-clear buffer stdin
		if (!isdigit(*output_char) || atoi(output_char) > menu || i != 0){  // cek apakah terdapat non-digit dan apakah input tidak sesuai pilihan dimenu
			printf("\n	Invalid option. Choose a valid menu");
			printf("\n	Choose a menu : ");
			inputData(output_char, max_input, mode, menu);  // rekursif hingga mendapat input yang benar
			clear();
		}
	}
}
void clear(){system("cls");}    // clear screen
void pause(){printf("\n\n\t");system("pause");}     // pause system
