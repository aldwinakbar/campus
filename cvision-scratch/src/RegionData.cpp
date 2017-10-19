#include "RegionData.h"
 
        double RegionData<BGRPixel>::colour_distance(cv::Vec3b e1,cv::Vec3b e2){
    
            long rmean = ( (long)e1.val[2] + (long)e2.val[2] ) / 2;
            long r = (long)e1.val[2] - (long)e2.val[2];
            long g = (long)e1.val[1] - (long)e2.val[1];
            long b = (long)e1.val[0] - (long)e2.val[0];
            return sqrt((((512+rmean)*r*r)>>8) + 4*g*g + (((767-rmean)*b*b)>>8));
        }
    
        bool RegionData<BGRPixel>::compare_v3b(cv::Vec3b a, cv::Vec3b b, int threshold){
            if(colour_distance(a,b) < threshold ) return true;
            return false;
        }

        void RegionData<BGRPixel>::find_region_util(cv::Mat &image,std::vector<std::vector<bool>> &marker, 
                          PixelList<BGRPixel> &region, int x, int y, cv::Vec3b target, 
                          int type, int threshold){
        
            int M = image.cols;
            int N = image.rows;
            // Base cases
            if (x < 0 || x >= M || y < 0 || y >= N)
                return;
            if (!compare_v3b(image.at<cv::Vec3b>(y,x), target, threshold))
                return;
            if (compare_v3b(image.at<cv::Vec3b>(y,x), target, threshold) && marker[x][y])
                return;
         
            region.push_back(std::make_pair(cv::Point(x,y),image.at<cv::Vec3b>(y,x)));
            marker[x][y] = true;
            
            if(type == 1){ 
                find_region_util(image,marker, region, x+1, y, target,type,threshold);
                find_region_util(image,marker,region, x-1, y, target, type,threshold);
                find_region_util(image,marker,region, x, y+1, target,type,threshold);
                find_region_util(image,marker, region,x, y-1, target, type,threshold);
        
                find_region_util(image,marker,region, x-1, y+1, target, type,threshold);
                find_region_util(image,marker,region, x+1, y+1, target,  type,threshold);
                find_region_util(image,marker,region, x+1, y-1, target,  type,threshold);
                find_region_util(image,marker, region,x-1, y-1, target,  type,threshold);
            }
            
            else{ 
                find_region_util(image,marker,region, x+1, y, target,  type,threshold);
                find_region_util(image,marker,region, x-1, y, target,  type,threshold);
                find_region_util(image,marker,region, x, y+1, target,  type,threshold);
                find_region_util(image,marker,region, x, y-1, target, type,threshold);
            }
        }

        PixelList<BGRPixel>  RegionData<BGRPixel>::find_region(cv::Mat &image, int x, int y, int type, int threshold){

            PixelList<BGRPixel> region;
            std::vector<std::vector<bool>> marker(image.cols,std::vector<bool>(image.rows, false));
            cv::Vec3b target = image.at<cv::Vec3b>(y,x);
            find_region_util(image,marker,region, x, y, target, type, threshold);
            return region;
        }
 
        RegionData<BGRPixel>::RegionData(RegionData<BGRPixel> &input){
            original_ = input.original_.clone();
            user_target_ = input.user_target_;
            type_ = input.type_;
            threshold_ = input.threshold_;
            pixel_list_ = input.pixel_list_;
            min_max_coor_ = input.min_max_coor_;
        }
        
        RegionData<BGRPixel>::RegionData(cv::Mat &image, int x, int y, int type, int threshold){
            original_ = image.clone();
            user_target_ = cv::Point(x,y);
            type_ = type;
            threshold_ = threshold;
            pixel_list_ = find_region(image, x, y, type, threshold );
            min_max_coor_ = minmax_coordinate(pixel_list_);
            normalize_pixel_lists(pixel_list_, min_max_coor_.first);
        }

        int RegionData<BGRPixel>::get_type(){
            return type_;
        }

        cv::Point RegionData<BGRPixel>::get_user_target(){
            return user_target_;
        }

        int RegionData<BGRPixel>::get_threshold(){
            return threshold_;
        }

        cv::Mat RegionData<BGRPixel>::get_original_image(){
            return original_;
        }
