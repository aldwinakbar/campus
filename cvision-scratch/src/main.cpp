#include <iostream>
#include "ImageAIO.h"
#include <string>

using namespace std;

void clear();
void pause();
void simple_notification(string input);
void main_menu();

int main(){

    ImageAIO image;
    int menu;
    string input_string;
    
	while (1){   
        clear();

        main_menu();
		
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
            
            cv::Mat checker = cv::imread(input_string, 1);
        
            if (!checker.data) {
                simple_notification("Load Image Failed");
				pause();
            }
            else{
                image.original_ = checker;
				simple_notification("Load Image Success");
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
			if(!image.original_.data || x >= image.original_.cols || x < 0 || y >= image.original_.rows || y < 0){
				simple_notification("Calculation Failed");
				pause();
			}
			else{
                image.calculate_all(x,y);
				simple_notification("Calculation Success");
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
			if(!image.original_.data || x >= image.original_.cols || x < 0 || y >= image.original_.rows || y < 0){
				simple_notification("Find Region Failed");
				pause();
			}
			else{
                simple_notification("Find Region Success");	
                image.calculate_region(x,y);
				pause();
			}
		}

		else if(menu == 4){
			if(!image.original_.data || image.region_.size() < 1 ){
				simple_notification("Find Pmeter Failed");
				pause();
			}
			else{
                simple_notification("Find Pmeter Success");
                image.calculate_perimeter();
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

			cin >> menu;

			if (menu == 1){    
                if(!image.original_.data){
                    simple_notification("Original Image Empty");
                    pause();
                }
                else{
                    simple_notification("Displaying Original Image");
                    image.display_original();
                    pause();
                    cv::destroyAllWindows();
                }
			}
			else if (menu == 2){   
				if(!image.region_image_.data){
                    simple_notification("Region Image Empty");
                    pause();
                }
                else{
                    simple_notification("Displaying Region Image");
                    image.display_region();
                    pause();
                    cv::destroyAllWindows();
                }
			}
			else if (menu == 3){    
				if(!image.perimeter_image_.data){
                    simple_notification("Perimeter Image Empty");
                    pause();
                }
                else{
                    simple_notification("Displaying Perimeter Image");
                    image.display_perimeter();
                    pause();
                    cv::destroyAllWindows();
                }
			}
		}

		else if(menu == 6){	
            
            int kernel_radius;
            int gaussian_sigma;
			
			clear();
			cout <<"\n	  ############################\n";
			cout <<"	  #                          #\n";
			cout <<"  	  #         Smoothing        #\n";
			cout <<"  	  #                          #\n";
			cout <<"  	  ############################\n \n \n";

			cout <<"       ##################################\n";
			cout <<"       #                                #\n";
			cout <<"       #  1. Dispay Smoothed Original   #\n";
			cout <<"       #  2. Dispay Smoothed Region     #\n";
			cout <<"       #  3. Dispay Smoothed Perimeter  #\n";
            cout <<"       #  4. Save Smoothed Perimeter    #\n";
            cout <<"       #  5. Save Smoothed Pmeter Image #\n";
			cout <<"       #  6. Back                       #\n";
			cout <<"       #                                #\n";
			cout <<"       ##################################\n \n";

			cout <<"	Enter a menu : ";

            cin >> menu;
            
            if( menu > 0 && menu < 6 ){ 
                simple_notification("Insert Gaussian Radius and Sigma");
                cout << "    Insert Gaussian Radius : ";
                cin >> kernel_radius;
                cout << "    Insert Gaussian Sigma : ";
                cin >> gaussian_sigma;
            }

            if(menu == 4 || menu == 5){
                clear();
                cout <<"	  ################################\n";
                cout <<"	  #                              #\n";
                cout <<"  	  #        Enter filename        #\n";
                cout <<"  	  #                              #\n";
                cout <<"  	  ################################\n \n \n";

                cout <<"	Enter a filename : ";
                cin >> input_string;
            }

			if (menu == 1){    
                
                if(!image.original_.data){
                    simple_notification("Original Image Empty");
                    pause();
                }
                else{
                    simple_notification("Displaying Smoothed Image");
                    image.display_smoothed_image(image.original_,kernel_radius, gaussian_sigma);
                    pause();
                    cv::destroyAllWindows();
                }
            }
            else if (menu == 2){    
                if(!image.region_.size() || !image.original_.data ){
                    simple_notification("Region Data Empty");
                    pause();
                }
                else{
                    simple_notification("Displaying Smoothed Image");
                    image.display_smoothed_region(kernel_radius, gaussian_sigma);
                    pause();        
                    cv::destroyAllWindows();
                }
			}
			else if (menu == 3){    
                if(!image.region_.size() || !image.original_.data){
                    simple_notification("Region Data Empty");
                    pause();
                }
                else{
                    simple_notification("Displaying Smoothed Image");
                    image.display_smoothed_perimeter(kernel_radius, gaussian_sigma);
                    pause();
                    cv::destroyAllWindows();
                }
            }
            
            else if (menu == 4){    
                ofstream myfile (input_string);
                if (image.region_.size() > 0 && myfile.is_open())
                {
                    std::vector<std::pair<cv::Point,cv::Vec3b>> temp_smooth = image.find_smoothed_perimeter(kernel_radius, gaussian_sigma);
                    for(std::pair<cv::Point,cv::Vec3b> value : temp_smooth){
                        myfile << value.first << " " << value.second << "\n";
                    }
                    myfile.close();
                    simple_notification("Smoothed Pmeter Saved");
                    pause();
                }
                else {
                    simple_notification("Failed to Save");
                    pause();
                }
            }
            
			else if (menu == 5){
                if(!image.region_.size() || !image.original_.data){
                    simple_notification("Region Data Empty");
                    pause();
                }
                else{
				    image.save_smoothed_image(input_string.c_str(), kernel_radius, gaussian_sigma);
                    simple_notification("Perimeter Image Save");
                    pause();
                }
			}
        }
        
        else if(menu == 7){			
			
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

			cin >> menu;
            if(menu < 5){
                clear();
                cout <<"	  ################################\n";
                cout <<"	  #                              #\n";
                cout <<"  	  #        Enter filename        #\n";
                cout <<"  	  #                              #\n";
                cout <<"  	  ################################\n \n \n";

                cout <<"	Enter a filename : ";
                cin >> input_string;
            }

			if (menu == 1){     
                ofstream myfile (input_string);
                if (image.region_.size() > 0 && myfile.is_open())
                {
                    for(std::pair<cv::Point,cv::Vec3b> value : image.region_){
                        myfile << value.first << " " << value.second << "\n";
                    }
                    myfile.close();
                    simple_notification("Region Coordinate Saved");
                    pause();
                }
                else {
                    simple_notification("Region Failed to Save");
                    pause();
                }
				
			}
			else if (menu == 2){   
                ofstream myfile (input_string);
                if (image.perimeter_.size() > 0 && myfile.is_open())
                {
                  for(std::pair<cv::Point,cv::Vec3b> value : image.perimeter_){
                    myfile << value.first << " " << value.second << "\n";
                  }
                  myfile.close();
                  simple_notification("Perimeter Coordinate Saved");
                  pause();
                }
                else {
                    simple_notification("Perimeter Failed to Save");
                    pause();
                }  
				
			}
			else if (menu == 3){  
                if(!image.region_image_.data){
                    simple_notification("Region Failed to Save");
                    pause();
                }
                else{
				    image.save_region_image(input_string.c_str());
                    simple_notification("Region Image Save");
                    pause();
                }
			}
			else if (menu == 4){
                if(!image.perimeter_image_.data){
                    simple_notification("Perimeter Failed to Save");
                    pause();
                }
                else{
				    image.save_perimeter_image(input_string.c_str());
                    simple_notification("Perimeter Image Save");
                    pause();
                }
			}
		}

		else if(menu == 8){
			break;
		}
	}

	return 0;
}
void clear(){
    system("clear");
}   
void pause() {
	cout << "      Press enter to continue.... ";
	cin.ignore().get();
}
void simple_notification(string input){
	clear();
	cout << "\n	  #######################################\n";
	cout << "	  #                                     #\n";
	cout << "  	            "<<input <<     "     	\n";
	cout << "  	  #                                     #\n";
	cout << "  	  #######################################\n \n \n";
}
void main_menu(){
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
    cout << "    #  6. Smoothing                     #\n";
    cout << "    #  7. Save                          #\n";
    cout << "    #  8. Exit                          #\n";
    cout << "    #                                   #\n";
    cout << "    #####################################\n \n";

    cout << "	Enter a menu : ";
}