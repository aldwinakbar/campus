#include "RegionData.h"
  
        namespace std {
            template <> struct hash<cv::Point> {
                size_t operator()(const cv::Point & x) const {
                    std::hash<std::string> str_hash; 
                    std::string temp = std::to_string(x.x);
                    temp += std::to_string(x.y);
                    return str_hash(temp);
                }
            };
        }

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
                          FindRegionType type, int threshold){
        
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
            
            if(type == FindRegionType::Eight_CD){ 
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

        PixelList<BGRPixel>  RegionData<BGRPixel>::find_region(cv::Mat &image, int x, int y, FindRegionType type, int threshold){

            PixelList<BGRPixel> region;
            std::vector<std::vector<bool>> marker(image.cols,std::vector<bool>(image.rows, false));
            cv::Vec3b target = image.at<cv::Vec3b>(y,x);
            find_region_util(image,marker,region, x, y, target, type, threshold);
            return region;
        }

        void RegionData<BGRPixel>::unique_push(std::unordered_set<cv::Point> &pixel_checker, std::queue<cv::Point> &ff_operation, cv::Point data){
            if (pixel_checker.insert(data).second) ff_operation.push(data); 
        }
        
        PixelList<BGRPixel>  RegionData<BGRPixel>::nr_find_region(cv::Mat &image, int x, int y, FindRegionType type, int threshold){
            
            std::unordered_set<cv::Point> pixel_checker;
            std::queue<cv::Point> ff_operation;
            int M = image.cols;
            int N = image.rows;

            PixelList<BGRPixel> region;
            std::vector<std::vector<bool>> marker(image.cols,std::vector<bool>(image.rows, false));
            cv::Vec3b target = image.at<cv::Vec3b>(y,x);

            ff_operation.push(cv::Point(x,y));

            while (!ff_operation.empty()){
                cv::Point temp = ff_operation.front();
                ff_operation.pop(); 
                                    
                if (temp.x < 0 || temp.x >= M || temp.y < 0 || temp.y >= N) continue;
                if (!compare_v3b(image.at<cv::Vec3b>(temp.y,temp.x), target, threshold)) continue;
                if (compare_v3b(image.at<cv::Vec3b>(temp.y,temp.x), target, threshold) && marker[temp.x][temp.y]) continue;
                    
                region.push_back(std::make_pair(cv::Point(temp.x,temp.y),image.at<cv::Vec3b>(temp.y,temp.x)));
                marker[temp.x][temp.y] = true;
                
                if ( type == FindRegionType::Four_CD){
                    unique_push(pixel_checker, ff_operation, cv::Point(temp.x+1,temp.y));
                    unique_push(pixel_checker, ff_operation, cv::Point(temp.x-1,temp.y));
                    unique_push(pixel_checker, ff_operation, cv::Point(temp.x,temp.y+1));
                    unique_push(pixel_checker, ff_operation, cv::Point(temp.x,temp.y-1)); 
                }
                else if( type == FindRegionType::Eight_CD){ 
                    unique_push(pixel_checker, ff_operation, cv::Point(temp.x+1,temp.y));
                    unique_push(pixel_checker, ff_operation, cv::Point(temp.x-1,temp.y));
                    unique_push(pixel_checker, ff_operation, cv::Point(temp.x,temp.y+1));
                    unique_push(pixel_checker, ff_operation, cv::Point(temp.x,temp.y-1)); 

                    unique_push(pixel_checker, ff_operation, cv::Point(temp.x-1,temp.y+1));
                    unique_push(pixel_checker, ff_operation, cv::Point(temp.x+1,temp.y+1));
                    unique_push(pixel_checker, ff_operation, cv::Point(temp.x+1,temp.y-1));
                    unique_push(pixel_checker, ff_operation, cv::Point(temp.x-1,temp.y-1)); 
                }
            }
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
        
        RegionData<BGRPixel>::RegionData(cv::Mat &image, int x, int y, FindRegionType type, int threshold){
            original_ = image.clone();
            user_target_ = cv::Point(x,y);
            type_ = type;
            threshold_ = threshold;
            
            int width = image.cols;
            int height = image.rows;

            if (x >= width || x < 0 || y >= height || y < 0){
                pixel_list_ = convert_to_pixel_list(image);
                min_max_coor_ = std::make_pair(cv::Point(0,0),cv::Point(width - 1, height - 1));            
            }
            else {
                pixel_list_ = nr_find_region(image, x, y, type, threshold );
                min_max_coor_ = minmax_coordinate(pixel_list_); 
                normalize_pixel_lists(pixel_list_, min_max_coor_.first);
            }
        }

        FindRegionType RegionData<BGRPixel>::get_type(){
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
