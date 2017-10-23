#include "PerimeterData.h"
 
        PixelList<BGRPixel> PerimeterData<BGRPixel>::find_perimeter (PixelList<BGRPixel> pixel_list, FindRegionType type){ 
            PixelList<BGRPixel> perimeter;      
            cv::Point size = region_data_->get_min_max_coordinate().second;
            cv::Mat temp(cv::Size(size.x, size.y), CV_8UC3, cv::Scalar(255,255,255)); 
            std::vector<std::vector<bool>> marker(size.x, std::vector<bool>(size.y, false));

            for (BGRPixel value : pixel_list){
                temp.at<cv::Vec3b>(value.first.y,value.first.x)[0] = value.second.val[0];
                temp.at<cv::Vec3b>(value.first.y,value.first.x)[1] = value.second.val[1];
                temp.at<cv::Vec3b>(value.first.y,value.first.x)[2] = value.second.val[2];
                marker[value.first.x][value.first.y] = true;
            } 

            int x_size = marker.size();
            int y_size = marker[0].size();
            for (int i=0; i < x_size; i++){
                for (int j=0; j < y_size; j++){
                    if(marker[i][j] == false ) continue;
                    else if( marker[i][j] && type == FindRegionType::Eight_CD){
                    // for 8-point style
                        if(j-1 < 0 || i-1 < 0 || i+1 >= x_size || j+1 >= y_size || 
                            !marker[i-1][j] || !marker[i+1][j] || !marker[i][j+1] ||
                            !marker[i][j-1] || !marker[i-1][j+1] || !marker[i+1][j+1] || 
                            !marker[i+1][j-1] || !marker[i-1][j-1]){
                                        
                            perimeter.push_back(std::make_pair(cv::Point(i,j),temp.at<cv::Vec3b>(j,i)));
                        }
                    }
                    // for 4-point style
                    else{
                        if(j-1 < 0 || i-1 < 0 || i+1 >= x_size || j+1 >= y_size || 
                            !marker[i-1][j] || !marker[i+1][j] || !marker[i][j+1] ||
                            !marker[i][j-1]){
                                        
                            perimeter.push_back(std::make_pair(cv::Point(i,j),temp.at<cv::Vec3b>(j,i)));
                        }
                    }
                }
            }
            return perimeter;
        } 
        
        PerimeterData<BGRPixel>::PerimeterData(const PerimeterData<BGRPixel> &input){
            region_data_ = new RegionData<BGRPixel>(*(input.region_data_));
            min_max_coor_  = input.region_data_->get_min_max_coordinate();
            pixel_list_ = input.pixel_list_;
        }

        PerimeterData<BGRPixel>::PerimeterData(RegionData<BGRPixel> input){
            region_data_ = new RegionData<BGRPixel>(input);
            min_max_coor_  = input.get_min_max_coordinate();
            pixel_list_ = find_perimeter (input.get_normalized_pixel_list(), input.get_type());
        }
        PerimeterData<BGRPixel>::~PerimeterData(){
            delete region_data_;
        }

        RegionData<BGRPixel> *PerimeterData<BGRPixel>::get_region_data(){
            return region_data_;
        }      