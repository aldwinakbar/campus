#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>


	using GPixel	= std::pair<cv::Point,uchar>;
    using BGRPixel  = std::pair<cv::Point,cv::Vec3b>;
    using SmoothingKernel = std::vector<std::vector<double>>;

	template <class T>	using PixelList = std::vector<T>;
    using MinMaxXY	= std::pair<cv::Point,cv::Point>; 

    template <class T> class PixelListData;
    template <class T> class RegionData;
    template <class T> class PerimeterData;
    template <class T> class SmoothData;


    template <>
    class PixelListData<BGRPixel>{

    protected:
        PixelList<BGRPixel>	pixel_list_;
        MinMaxXY 		    min_max_coor_;
        
        MinMaxXY minmax_coordinate(PixelList<BGRPixel> &region){

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
                return std::make_pair(cv::Point(x_min,y_min), cv::Point(x_max+1, y_max+1));
            }

        void normalize_pixel_lists(PixelList<BGRPixel> &region, cv::Point min_coor){

            for (BGRPixel &value : region){
                value.first.x -= min_coor.x;
                value.first.y -= min_coor.y;
            }
        }

        void unnormalize_pixel_lists(PixelList<BGRPixel> &region, cv::Point min_coor){
            for (BGRPixel &value : region){
                value.first.x += min_coor.x;
                value.first.y += min_coor.y;
            }
        }

    public:
        virtual void abstract_if_pure_virtual() = 0; 

        MinMaxXY get_min_max_coordinate(){
            return min_max_coor_;
        }
        PixelList<BGRPixel> get_normalized_pixel_list(){
            return pixel_list_;
        }
        PixelList<BGRPixel> get_unnormalized_pixel_list(){
            PixelList<BGRPixel> temp(pixel_list_);
            unnormalize_pixel_lists(temp, min_max_coor_.first);
            return temp;
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

        void display(std::string const &win_name){
            cv::Mat temp = get_image();
            cv::namedWindow(win_name, cv::WINDOW_AUTOSIZE);
            cv::imshow(win_name, temp);
            cv::waitKey(0);
        }

        void save_image(const char *name){
            cv::Mat temp = get_image();
            cv::imwrite(name, temp);
        }
        bool save_list(const char *input_string){
            std::ofstream myfile (input_string);
            if (pixel_list_.size() > 0 && myfile.is_open())
            {
                for(BGRPixel value : pixel_list_){
                    myfile << value.first << " " << value.second << "\n";
                }
                myfile.close();
                return true;
            }
            else return false;
        }
    };

	template <>
	class RegionData<BGRPixel> : public PixelListData<BGRPixel> {
        void abstract_if_pure_virtual(){}    

        private:

            cv::Mat             original_;
            cv::Point           user_target_;
            int                 type_;
            int                 threshold_;

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

		    PixelList<BGRPixel>  find_region(cv::Mat &image, int x, int y, int type, int threshold){

                PixelList<BGRPixel> region;
				std::vector<std::vector<bool>> marker(image.cols,std::vector<bool>(image.rows, false));
				cv::Vec3b target = image.at<cv::Vec3b>(y,x);
                find_region_util(image,marker,region, x, y, target, type, threshold);
                return region;
            }

        public:       
            RegionData(RegionData<BGRPixel> &input){
                original_ = input.original_.clone();
                user_target_ = input.user_target_;
                type_ = input.type_;
                threshold_ = input.threshold_;
                pixel_list_ = input.pixel_list_;
                min_max_coor_ = input.min_max_coor_;
            }
            
            RegionData(cv::Mat &image, int x, int y, int type, int threshold){
                original_ = image.clone();
                user_target_ = cv::Point(x,y);
                type_ = type;
                threshold_ = threshold;
                pixel_list_ = find_region(image, x, y, type, threshold );
                min_max_coor_ = minmax_coordinate(pixel_list_);
                normalize_pixel_lists(pixel_list_, min_max_coor_.first);
            }

            int get_type(){
                return type_;
            }

            cv::Point get_user_target(){
                return user_target_;
            }

            int get_threshold(){
                return threshold_;
            }

            cv::Mat get_original_image(){
                return original_;
            }
    };

    template <>
	class PerimeterData<BGRPixel> : public PixelListData<BGRPixel> {
        void abstract_if_pure_virtual(){}

        private:
            RegionData<BGRPixel>    *region_data_;

            PixelList<BGRPixel> find_perimeter (PixelList<BGRPixel> pixel_list, int type){ 
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
                return perimeter;
            }
            
        public:
            
            PerimeterData(const PerimeterData<BGRPixel> &input){
                region_data_ = new RegionData<BGRPixel>(*(input.region_data_));
                min_max_coor_  = input.region_data_->get_min_max_coordinate();
                pixel_list_ = input.pixel_list_;
            }

            PerimeterData(RegionData<BGRPixel> input){
                region_data_ = new RegionData<BGRPixel>(input);
                min_max_coor_  = input.get_min_max_coordinate();
                pixel_list_ = find_perimeter (input.get_normalized_pixel_list(), input.get_type());
            }
            ~PerimeterData(){
                delete region_data_;
            }

            RegionData<BGRPixel> *get_region_data(){
                return region_data_;
            }     
    };

    template<>
    class SmoothData<BGRPixel> : public PixelListData<BGRPixel> {
    void abstract_if_pure_virtual(){}
    private: 

        double  gaussian(double x, double mu, double sigma){
            return std::exp( -(((x-mu)/(sigma))*((x-mu)/(sigma)))/2.0 );
        }
        
        SmoothingKernel produce_2d_gaussian_kernel (int kernelRadius, double sigma) {
            std::vector<std::vector<double>> kernel2d(2*kernelRadius+1, std::vector<double>(2*kernelRadius+1));
            double sum = 0;
            // compute values
            for (int row = 0; row < kernel2d.size(); row++)
              for (int col = 0; col < kernel2d[row].size(); col++) {
                double x = gaussian(row, kernelRadius, sigma)
                         * gaussian(col, kernelRadius, sigma);
                kernel2d[row][col] = x;
                sum += x;
              }
            // normalize
            for (int row = 0; row < kernel2d.size(); row++)
              for (int col = 0; col < kernel2d[row].size(); col++)
                kernel2d[row][col] /= sum;
            return kernel2d;
        }

        PixelList<BGRPixel> mat_smoothing(cv::Mat &src, int kernel_radius, double sigma){
            SmoothingKernel kernel = produce_2d_gaussian_kernel(kernel_radius, sigma);
            PixelList<BGRPixel> dst; // certain pixel are not initialized
            int radius = (kernel.size() - 1)/2;
            int lower_limit = 0 - radius;
            int upper_limit = radius;
            float sum[3];
            for(int y = radius; y < src.rows - radius; y++){
                for(int x = radius; x < src.cols - radius; x++){
                    sum[0] = 0.0;
                    sum[1] = 0.0;
                    sum[2] = 0.0;
                    for(int k = lower_limit; k <= upper_limit;k++){
                        for(int j = lower_limit; j <= upper_limit; j++){
                            sum[0] = sum[0] + kernel[j+radius][k+radius]*src.at<cv::Vec3b>(y - j, x - k)[0];
                            sum[1] = sum[1] + kernel[j+radius][k+radius]*src.at<cv::Vec3b>(y - j, x - k)[1];
                            sum[2] = sum[2] + kernel[j+radius][k+radius]*src.at<cv::Vec3b>(y - j, x - k)[2];
                        }
                    }
                    cv::Vec3b temp;
                    temp.val[0] = sum[0];
                    temp.val[1] = sum[1];
                    temp.val[2] = sum[2];
                    dst.push_back(std::make_pair(cv::Point(x,y), temp));
                }
            }
            return dst;
        }
        
        PixelList<BGRPixel> region_smoothing(RegionData<BGRPixel> region, int kernel_radius, double sigma){
            std::vector<std::vector<double>> kernel = produce_2d_gaussian_kernel(kernel_radius, sigma);
            RegionData<BGRPixel> temp_region = region;
            PixelList<BGRPixel> temp = region.get_unnormalized_pixel_list();
            cv::Mat temp_image = region.get_original_image();
            PixelList<BGRPixel> result;

            int radius = (kernel.size() - 1)/2;
            int lower_limit = 0 - radius;
            int upper_limit = radius;
            float sum[3];
            int M = temp_region.get_original_image().cols;
            int N = temp_region.get_original_image().rows;

            for(BGRPixel value : temp){
                int x = value.first.x;
                int y = value.first.y;
                sum[0] = 0.0;
                sum[1] = 0.0;
                sum[2] = 0.0;
                for(int k = lower_limit; k <= upper_limit;k++){
                    for(int j = lower_limit; j <= upper_limit; j++){
                        if ((x-k) < 0 || (x-k) >= M || (y - j) < 0 || (y - j) >= N) continue; // inefficient way to be safe
        
                        sum[0] = sum[0] + kernel[j+radius][k+radius]*temp_image.at<cv::Vec3b>(y - j, x - k)[0];
                        sum[1] = sum[1] + kernel[j+radius][k+radius]*temp_image.at<cv::Vec3b>(y - j, x - k)[1];
                        sum[2] = sum[2] + kernel[j+radius][k+radius]*temp_image.at<cv::Vec3b>(y - j, x - k)[2];
                    }
                }
                cv::Vec3b temp_vec3b;
                temp_vec3b.val[0] = sum[0];
                temp_vec3b.val[1] = sum[1];
                temp_vec3b.val[2] = sum[2];
                result.push_back(std::make_pair(cv::Point(x,y), temp_vec3b));
            }
            normalize_pixel_lists(result,temp_region.get_min_max_coordinate().first);
            return result;
        }
        
        PixelList<BGRPixel>	find_smooth_perimeter(PerimeterData<BGRPixel> perimeter, int kernel_radius, double sigma){
            
            RegionData<BGRPixel> temp_region (*(perimeter.get_region_data()));

            PixelList<BGRPixel> smoothed_region = region_smoothing(temp_region, kernel_radius, sigma);
            unnormalize_pixel_lists(smoothed_region,temp_region.get_min_max_coordinate().first);
            
            cv::Mat temp_image = temp_region.get_original_image().clone();
            
            for (BGRPixel value : smoothed_region){
                temp_image.at<cv::Vec3b>(value.first.y,value.first.x)[0] = value.second.val[0];
                temp_image.at<cv::Vec3b>(value.first.y,value.first.x)[1] = value.second.val[1];
                temp_image.at<cv::Vec3b>(value.first.y,value.first.x)[2] = value.second.val[2];
            }

            RegionData<BGRPixel> temp_region_2(temp_image, temp_region.get_user_target().x, 
                                               temp_region.get_user_target().y, temp_region.get_type(), 
                                               temp_region.get_threshold());

            PerimeterData<BGRPixel> result(temp_region_2);
            return result.get_normalized_pixel_list();
        }
    
    public: 
        SmoothData(cv::Mat input, int kernel_radius, double sigma){
            min_max_coor_ = std::make_pair(cv::Point(0,0), cv::Point(input.cols-1, input.rows-1));
            pixel_list_ = mat_smoothing(input, kernel_radius, sigma);
        }
        SmoothData(RegionData<BGRPixel> input, int kernel_radius, int sigma){
            min_max_coor_ = input.get_min_max_coordinate();
            pixel_list_ = region_smoothing(input, kernel_radius, sigma); 
        }
        
        SmoothData(PerimeterData<BGRPixel> input, int kernel_radius, int sigma){
            min_max_coor_ = input.get_min_max_coordinate();
            pixel_list_ = find_smooth_perimeter(input, kernel_radius, sigma); 
        }
    };

    using namespace cv;      
    int main(){
        
        Mat input;
        input = imread("images/test3.png", CV_LOAD_IMAGE_COLOR);
        if(!input.data) return -1;
        
        RegionData<BGRPixel> sample(input, 100,100,1,150);
        PerimeterData<BGRPixel> sample_two(sample);
        SmoothData<BGRPixel> sample_three(input, 1, 5);

        SmoothData<BGRPixel> sample_four(sample, 5, 10);
        SmoothData<BGRPixel> sample_five(sample_two, 10, 10);

        sample_two.display("Perimeter"); 
        sample.display("Region");

        sample_three.display("Smat");
        sample_four.display("SRegion");
        sample_five.display("SR");

        sample.save_image("out.png");
        sample_two.save_image("out2.png");
        waitKey(0);
        return 0;
    }