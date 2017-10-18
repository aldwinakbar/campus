#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>


	using GPixel	= std::pair<cv::Point,uchar>;
	using BGRPixel  = std::pair<cv::Point,cv::Vec3b>;

	template <class T>	using PixelList = std::vector<T>;
    using MinMaxXY	= std::pair<cv::Point,cv::Point>; 

    template <class T> class RegionData;
    template <class T> class PerimeterData;

	template <>
	class RegionData<BGRPixel> {

        private:
            PixelList<BGRPixel>	pixel_list_;
            MinMaxXY 		    min_max_coor_;

                
            double colour_distance(cv::Vec3b e1,cv::Vec3b e2){
        
                long rmean = ( (long)e1.val[2] + (long)e2.val[2] ) / 2;
                long r = (long)e1.val[2] - (long)e2.val[2];
                long g = (long)e1.val[1] - (long)e2.val[1];
                long b = (long)e1.val[0] - (long)e2.val[0];
                return sqrt((((512+rmean)*r*r)>>8) + 4*g*g + (((767-rmean)*b*b)>>8));
            }
        
            bool compare_v3b(cv::Vec3b a, cv::Vec3b b, int threshold){
                if(colour_distance(a,b) < threshold ) return true;
                return false;
            }

            void minmax_coordinate(PixelList<BGRPixel> &region){

                int x_min = region[0].first.x;
                int y_min = region[0].first.y;
                int x_max = 0;
                int y_max = 0;
                for (BGRPixel value : region){
                    if(value.first.x < x_min) x_min = value.first.x;
                    if(value.first.y < y_min) y_min = value.first.y;

                    if(value.first.x > x_max) x_max = value.first.x;
                    if(value.first.y > y_max) y_max = value.first.y;        
                }
                x_max -= x_min;
                y_max -= y_min;
                min_max_coor_ = std::make_pair(cv::Point(x_min,y_min), cv::Point(x_max+1, y_max+1));
            }

            void normalize_region(PixelList<BGRPixel> &region, cv::Point min_coor){

                for (BGRPixel &value : region){
                    value.first.x -= min_coor.x;
                    value.first.y -= min_coor.y;
                }
            }

            void unnormalize_region(PixelList<BGRPixel> &region, cv::Point min_coor){
                for (BGRPixel &value : region){
                    value.first.x += min_coor.x;
                    value.first.y += min_coor.y;
                }
            }

            void find_region_util(cv::Mat &image,std::vector<std::vector<bool>> &marker, 
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
			
				// Replace the color at (x, y)
				region.push_back(std::make_pair(cv::Point(x,y),image.at<cv::Vec3b>(y,x)));
				marker[x][y] = true;
				
				if(type == 1){
					// Recur for all direction
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
					// Recur for north, east, south and west
					find_region_util(image,marker,region, x+1, y, target,  type,threshold);
					find_region_util(image,marker,region, x-1, y, target,  type,threshold);
					find_region_util(image,marker,region, x, y+1, target,  type,threshold);
					find_region_util(image,marker,region, x, y-1, target, type,threshold);
				}
			}

		    void  find_region(cv::Mat &image, int x, int y, int type, int threshold){

                PixelList<BGRPixel> region;
				std::vector<std::vector<bool>> marker(image.cols,std::vector<bool>(image.rows, false));
				cv::Vec3b target = image.at<cv::Vec3b>(y,x);
			
                find_region_util(image,marker,region, x, y, target, type, threshold);
                
                pixel_list_ = region;
            }

        public:
            RegionData<BGRPixel>(PixelList<BGRPixel> input){
                pixel_list_ = input;
                minmax_coordinate(pixel_list_);
                normalize_region(pixel_list_, min_max_coor_.first);
            }
            RegionData<BGRPixel>(cv::Mat &image, int x, int y, int type, int threshold){
                find_region(image, x, y, type, threshold );
                minmax_coordinate(pixel_list_);
                normalize_region(pixel_list_, min_max_coor_.first);
            }
            PixelList<BGRPixel> get_normalized_pixel_list(){
                return pixel_list_;
            }
            PixelList<BGRPixel> get_unnormalized_pixel_list(){
                PixelList<BGRPixel> temp(pixel_list_);
                unnormalize_region(temp, min_max_coor_.first);
                return temp;
            }
            MinMaxXY get_min_max_coordinate(){
                return min_max_coor_;
            }
            cv::Mat get_image(){
                cv::Mat temp(cv::Size(min_max_coor_.second.x, min_max_coor_.second.y), CV_8UC3, cv::Scalar(255,255,255)); 
                for (BGRPixel value : pixel_list_){
                    temp.at<cv::Vec3b>(value.first.y,value.first.x)[0] = value.second.val[0];
                    temp.at<cv::Vec3b>(value.first.y,value.first.x)[1] = value.second.val[1];
                    temp.at<cv::Vec3b>(value.first.y,value.first.x)[2] = value.second.val[2];
                }
                return temp;
            }
    };
    
    template <>
	class PerimeterData<BGRPixel> {

		PixelList<BGRPixel>	pixel_list_;
		MinMaxXY 		    min_max_coor_;

		PerimeterData<BGRPixel>(PixelList<BGRPixel> input, cv::Point min_max_coor){
            pixel_list_ = input;
        }
    };
    

	PerimeterData<BGRPixel> 		find_perimeter (RegionData<BGRPixel> &region, int type);
    /*
	void              		        display_image(const char* location, std::string const &win_name);
	void                     		display_pixel(const cv::Mat &image, std::string const &win_name);
	void                        	save_pixel(cv::Mat &image, const char *name);
		
	double                      	gaussian(double x, double mu, double sigma);
	std::vector<std::vector<double>>produce_2d_gaussian_kernel(int kernelRadius, double sigma);
	cv::Mat                         neighborhood_mean(cv::Mat &src, std::vector<std::vector<double>> kernel); 
	RegionData 						region_smoothing(cv::Mat &src,RegionData region,cv::Point min_coor, 
													 int kernel_radius, double sigma);
	cv::Mat                         create_image_from_pixel(cv::Mat &src, VectorOPixel pixel);
	PerimeterData 					find_smooth_perimeter(cv::Mat &src, RegionData region, cv::Point min_coor,
														  int kernel_radius, double sigma, int x, int y, 
														  int type, int threshold);
    */

   /*
        PerimeterData<BGRPixel> find_perimeter(RegionData<BGRPixel> &region, int type){

            PixelList<BGRPixel> perimeter;            
			cv::Mat temp(cv::Size(region.get_min_max_coordinate().second.x, region.get_min_max_coordinate().second.y), CV_8UC3, cv::Scalar(255,255,255)); 
			std::vector<std::vector<bool>> marker(region.get_min_max_coordinate().second.x, std::vector<bool>(region.get_min_max_coordinate().second.y, false));

			for (BGRPixel value : region.get_normalized_pixel_list()){
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
				else if (marker[i][j] == true){
						if( type == 1){
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
            }
            PerimeterData<BGRPixel> result(perimeter, region.get_min_max_coordinate());
			return result;
		}
     */       
    int main(){
        
        PixelList<BGRPixel> base;
        RegionData<BGRPixel> sample(base);

        return 0;
    }