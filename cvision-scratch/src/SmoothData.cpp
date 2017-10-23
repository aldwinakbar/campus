#include "SmoothData.h"

    double SmoothData<BGRPixel>::gaussian(double x, double mu, double sigma){
        return std::exp( -(((x-mu)/(sigma))*((x-mu)/(sigma)))/2.0 );
    }

    SmoothingKernel SmoothData<BGRPixel>::produce_2d_gaussian_kernel (int kernelRadius, double sigma) {
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

    cv::Point SmoothData<BGRPixel>::coordinate_repair(cv::Point size, cv::Point input){

        int N = size.x;
        int M = size.y;    

        int x_temp = input.x;
        int y_temp = input.y;

        if (x_temp < 0 && y_temp < 0){
            x_temp = 0;
            y_temp = 0;
        }
        else if(x_temp >= 0 && x_temp < N && y_temp < 0) y_temp = 0;
        else if(x_temp >= N && y_temp < 0){
            x_temp = N-1;
            y_temp = 0;
        }
        else if(x_temp < 0 && y_temp >= 0 && y_temp < M) x_temp = 0;
        else if(x_temp >= N && y_temp >= 0 && y_temp < M) x_temp = N-1;
        else if(x_temp < 0 && y_temp >= M) {
            x_temp = 0;
            y_temp = M-1;
        }
        else if(x_temp >= 0 && x_temp < N && y_temp >= M) y_temp = M - 1;
        else if(x_temp >= M && y_temp >= N){
            x_temp = N-1;
            y_temp = M-1;
        }

        return cv::Point(x_temp, y_temp);        
    }

    PixelList<BGRPixel> SmoothData<BGRPixel>::mat_smoothing(cv::Mat &src, int kernel_radius, double sigma){
        SmoothingKernel kernel = produce_2d_gaussian_kernel(kernel_radius, sigma);
        PixelList<BGRPixel> dst; // certain pixel are not initialized
        int radius = (kernel.size() - 1)/2;
        int lower_limit = 0 - radius;
        int upper_limit = radius;
        float sum[3]; 

        for(int y = 0; y < src.rows ; y++){
            for(int x = 0; x < src.cols; x++){
                sum[0] = 0.0;
                sum[1] = 0.0;
                sum[2] = 0.0;
                for(int k = lower_limit; k <= upper_limit; k++){
                    for(int j = lower_limit; j <= upper_limit; j++){ 
                        cv::Point temp_coor = coordinate_repair(cv::Point(src.cols,src.rows), cv::Point( (x + k), (y + j) ));
                        
                        sum[0] = sum[0] + kernel[j+radius][k+radius]*src.at<cv::Vec3b>(temp_coor.y, temp_coor.x)[0];
                        sum[1] = sum[1] + kernel[j+radius][k+radius]*src.at<cv::Vec3b>(temp_coor.y, temp_coor.x)[1];
                        sum[2] = sum[2] + kernel[j+radius][k+radius]*src.at<cv::Vec3b>(temp_coor.y, temp_coor.x)[2];
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

    PixelList<BGRPixel> SmoothData<BGRPixel>::region_smoothing(RegionData<BGRPixel> region, int kernel_radius, double sigma){
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
                    cv::Point temp_coor = coordinate_repair(cv::Point(M,N), cv::Point( (x + k), (y + j) ));
                    
                    sum[0] = sum[0] + kernel[j+radius][k+radius]*temp_image.at<cv::Vec3b>(temp_coor.y, temp_coor.x)[0];
                    sum[1] = sum[1] + kernel[j+radius][k+radius]*temp_image.at<cv::Vec3b>(temp_coor.y, temp_coor.x)[1];
                    sum[2] = sum[2] + kernel[j+radius][k+radius]*temp_image.at<cv::Vec3b>(temp_coor.y, temp_coor.x)[2];
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

    PixelList<BGRPixel>	SmoothData<BGRPixel>::find_smooth_perimeter(PerimeterData<BGRPixel> perimeter, int kernel_radius, double sigma){
        
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
 
    SmoothData<BGRPixel>::SmoothData(const SmoothData<BGRPixel> &input){
        
        pixel_list_ = input.pixel_list_;
        min_max_coor_ = input.min_max_coor_;
    }

    SmoothData<BGRPixel>::SmoothData(cv::Mat input, int kernel_radius, double sigma){
        min_max_coor_ = std::make_pair(cv::Point(0,0), cv::Point(input.cols, input.rows));
        pixel_list_ = mat_smoothing(input, kernel_radius, sigma);
    }
    SmoothData<BGRPixel>::SmoothData(RegionData<BGRPixel> input, int kernel_radius, int sigma){
        min_max_coor_ = input.get_min_max_coordinate();
        pixel_list_ = region_smoothing(input, kernel_radius, sigma); 
    }

    SmoothData<BGRPixel>::SmoothData(PerimeterData<BGRPixel> input, int kernel_radius, int sigma){
        min_max_coor_ = input.get_min_max_coordinate();
        pixel_list_ = find_smooth_perimeter(input, kernel_radius, sigma); 
    }