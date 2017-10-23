#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

void clear();
void pause();

void simple_notification(string input){
	clear();
	cout << "\n	  #######################################\n";
	cout << "	  #                                     #\n";
	cout << "  	            "<<input <<     "     	\n";
	cout << "  	  #                                     #\n";
	cout << "  	  #######################################\n \n \n";
}

int main(){

	int sub_menu;
	int menu;
	string input_string;
	while (1){   
        clear();
		cout << "\n	  ########################\n";
		cout << "	  #                      #\n";
		cout << "  	  #    Image Processing  #\n";
		cout << "  	  #          API         #\n";
		cout << "  	  #                      #\n";
		cout << "  	  #      CL Interface    #\n";
		cout << "  	  #                      #\n";
		cout << "  	  ########################\n \n \n";

		cout << "    #####################################\n";
		cout << "    #                                   #\n";
		cout << "    #  1. Load Image                    #\n";
		cout << "    #  2. Calculate All                 #\n";
		cout << "    #  3. Find Region                   #\n";
        cout << "    #  4. Find Perimeter                #\n";
		cout << "    #  5. Display                       #\n";
        cout << "    #  6. Save                          #\n";
		cout << "    #  7. Exit                          #\n";
		cout << "    #                                   #\n";
		cout << "    #####################################\n \n";

		cout << "	Enter a menu : ";

		cin >> menu;
 
		if(menu == 1){
			
			clear();
			cout << "\n	  #######################################\n";
			cout << "	  #                                     #\n";
			cout << "  	  #           Loading RAW Image     	#\n";
			cout << "  	  #                                     #\n";
			cout << "  	  #######################################\n \n \n";

			cout << "	Typed in the image location including filename.\n\n";


			cout << "	Enter a location : ";
			cin >> input_string;

			cout << input_string << endl;

			if(1){
				simple_notification("Load Image Success");
				pause();
			}
			else{
				simple_notification("Load Image Failed");
				pause();
			}			
		}

		else if(menu == 2){
			int x,y;
			simple_notification("Insert X and Y");
			cout << "    Insert X : ";
			cin >> x;
			cout << "    Insert Y : ";
			cin >> y;
			if(1){
				simple_notification("Calculation Success");
				pause();
			}
			else{
				simple_notification("Calculation Failed");
				pause();
			}
		}

		else if(menu == 3){
			int x,y;
			simple_notification("Insert X and Y");
			cout << "    Insert X : ";
			cin >> x;
			cout << "    Insert Y : ";
			cin >> y;
			if(1){
				simple_notification("Find Region Success");
				pause();
			}
			else{
				simple_notification("Find Region Failed");	
				pause();
			}
		}

		else if(menu == 4){
			if(1){
				simple_notification("Find Pmeter Success");
				pause();
			}
			else{
				simple_notification("Find Pmeter Failed");
				pause();
			}
		}

		else if(menu == 5){
			
			clear();
			cout <<"\n	  ############################\n";
			cout <<"	  #                          #\n";
			cout <<"  	  #       Display Image      #\n";
			cout <<"  	  #                          #\n";
			cout <<"  	  ############################\n \n \n";

			cout <<"       ##################################\n";
			cout <<"       #                                #\n";
			cout <<"       #  1. Original Image             #\n";
			cout <<"       #  2. Selected Region Image      #\n";
			cout <<"       #  3. Perimeter Image            #\n";
			cout <<"       #  4. Back                       #\n";
			cout <<"       #                                #\n";
			cout <<"       ##################################\n \n";

			cout <<"	Enter a menu : ";

			cin >> sub_menu;

			if (sub_menu == 1){    
				simple_notification("Displaying Original Image");

				pause();
			}
			else if (sub_menu == 2){   
				simple_notification("Displaying Region Image");
				pause();
			}
			else if (sub_menu == 3){    
				simple_notification("Displaying Perimeter Image");
				pause();
			}
		}

		else if(menu == 6){
			
			
			clear();
			cout <<"\n	  ############################\n";
			cout <<"	  #                          #\n";
			cout <<"  	  #        Save Option       #\n";
			cout <<"  	  #                          #\n";
			cout <<"  	  ############################\n \n \n";

			cout <<"       ##################################\n";
			cout <<"       #                                #\n";
			cout <<"       #  1. Region Coordinate          #\n";
			cout <<"       #  2. Perimeter Coordinate       #\n";
			cout <<"       #  3. Region Image               #\n";
			cout <<"       #  4. Perimeter Image            #\n";
			cout <<"       #  5. Back                       #\n";
			cout <<"       #                                #\n";
			cout <<"       ##################################\n \n";

			cout <<"	Enter a menu : ";

			cin >> sub_menu;

			clear();
			cout <<"	  ################################\n";
			cout <<"	  #                              #\n";
			cout <<"  	  #        Enter filename        #\n";
			cout <<"  	  #                              #\n";
			cout <<"  	  ################################\n \n \n";

			cout <<"	Enter a filename : ";
			cin >> input_string;
			cout << input_string << endl;
			pause();

			if (sub_menu == 1){     
				
			}
			else if (sub_menu == 2){     
				
			}
			else if (sub_menu == 3){    
				
			}
			else if (sub_menu == 4){
				
			}
		}

		else if(menu == 7){
			break;
		}
	}

	return 0;
}
void clear(){system("clear");}   
void pause() {
	cout << "      Press enter to continue.... ";
	cin.ignore().get();
}