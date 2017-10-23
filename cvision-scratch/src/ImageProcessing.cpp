#include "ImageProcessing.h"

namespace arcv{

		void display_image(const char* location, std::string const &win_name) {
			cv::Mat image = cv::imread(location, 1);

			if (!image.data) {
				printf("No image data (warning: OpenCV recognize files by extensions)\n");
				return;
			}

			cv::namedWindow(win_name, cv::WINDOW_AUTOSIZE);
			cv::imshow(win_name, image);
			cv::waitKey(0);
		}

		void display_pixel(const cv::Mat &image, std::string const &win_name) {
			cv::namedWindow(win_name, cv::WINDOW_AUTOSIZE);
			cv::imshow(win_name, image);
			cv::waitKey(0);
		}

		void save_pixel(cv::Mat &image, const char *name){
			cv::imwrite(name, image);
		}

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

		MinMaxXY minmax_coordinate(RegionData &region){

			int x_min = region[0].first.x;
			int y_min = region[0].first.y;
			int x_max = 0;
			int y_max = 0;
			for (PixelData value : region){
				if(value.first.x < x_min) x_min = value.first.x;
				if(value.first.y < y_min) y_min = value.first.y;

				if(value.first.x > x_max) x_max = value.first.x;
				if(value.first.y > y_max) y_max = value.first.y;        
			}
			x_max -= x_min;
			y_max -= y_min;
			return std::make_pair(cv::Point(x_min,y_min), cv::Point(x_max+1, y_max+1));
		}

		void normalize_region(RegionData &region, cv::Point &min_coor){

			for (PixelData &value : region){
				value.first.x -= min_coor.x;
				value.first.y -= min_coor.y;
			}
		}

		cv::Mat create_image_from_pixel(VectorOPixel pixel){
			
			std::pair<cv::Point,cv::Point> minmax_coor = minmax_coordinate(pixel);
			cv::Mat temp(cv::Size(minmax_coor.second.x, minmax_coor.second.y), CV_8UC3, cv::Scalar(255,255,255)); 
				
			for (PixelData value : pixel){
				temp.at<cv::Vec3b>(value.first.y,value.first.x)[0] = value.second.val[0];
				temp.at<cv::Vec3b>(value.first.y,value.first.x)[1] = value.second.val[1];
				temp.at<cv::Vec3b>(value.first.y,value.first.x)[2] = value.second.val[2];
			}
			return temp;
		}

		void find_region_util(cv::Mat &image,std::vector<std::vector<bool>> &marker, 
                              RegionData &region, int x, int y, cv::Vec3b target, 
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
			
		RegionData  find_region(cv::Mat &image, int x, int y, int type, int threshold){

				RegionData region;
				std::vector<std::vector<bool>> marker(image.cols,std::vector<bool>(image.rows, false));
				cv::Vec3b target = image.at<cv::Vec3b>(y,x);
			
				find_region_util(image,marker,region, x, y, target, type, threshold);

				std::pair<cv::Point,cv::Point> minmax_coor = minmax_coordinate(region);
				normalize_region(region,minmax_coor.first);
				return region;
			}

		PerimeterData find_perimeter(RegionData &region, int type){

			PerimeterData perimeter;
			std::pair<cv::Point,cv::Point> minmax_coor = minmax_coordinate(region);

			cv::Mat temp(cv::Size(minmax_coor.second.x, minmax_coor.second.y), CV_8UC3, cv::Scalar(255,255,255)); 
			std::vector<std::vector<bool>> marker(minmax_coor.second.x, std::vector<bool>(minmax_coor.second.y, false));

			for (PixelData value : region){
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


double gaussian (double x, double mu, double sigma) {
	return std::exp( -(((x-mu)/(sigma))*((x-mu)/(sigma)))/2.0 );
  }
  
  std::vector<std::vector<double>> produce_2d_gaussian_kernel (int kernelRadius, double sigma) {
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

  cv::Mat neighborhood_mean(cv::Mat &src, std::vector<std::vector<double>> kernel){
	  cv::Mat dst = src.clone();
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
			  dst.at<cv::Vec3b>(y,x)[0] = sum[0];
			  dst.at<cv::Vec3b>(y,x)[1] = sum[1];
			  dst.at<cv::Vec3b>(y,x)[2] = sum[2];
		  }
	  }
	  return dst;
  }

  RegionData region_smoothing(cv::Mat &src,RegionData region,cv::Point min_coor, 
                              int kernel_radius, double sigma){
	  std::vector<std::vector<double>> kernel = produce_2d_gaussian_kernel(kernel_radius, sigma);
	  RegionData result;
	  int radius = (kernel.size() - 1)/2;
	  int lower_limit = 0 - radius;
	  int upper_limit = radius;
	  float sum[3];
	  int M = src.cols;
	  int N = src.rows;
	  unnormalize_region(region,min_coor); 
	  for(std::pair<cv::Point, cv::Vec3b> value : region){
		  int x = value.first.x;
		  int y = value.first.y;
		  sum[0] = 0.0;
		  sum[1] = 0.0;
		  sum[2] = 0.0;
		  for(int k = lower_limit; k <= upper_limit;k++){
			  for(int j = lower_limit; j <= upper_limit; j++){
				  if ((x-k) < 0 || (x-k) >= M || (y - j) < 0 || (y - j) >= N) continue;
  
				  sum[0] = sum[0] + kernel[j+radius][k+radius]*src.at<cv::Vec3b>(y - j, x - k)[0];
				  sum[1] = sum[1] + kernel[j+radius][k+radius]*src.at<cv::Vec3b>(y - j, x - k)[1];
				  sum[2] = sum[2] + kernel[j+radius][k+radius]*src.at<cv::Vec3b>(y - j, x - k)[2];
			  }
		  }
		  cv::Vec3b temp;
		  temp.val[0] = sum[0];
		  temp.val[1] = sum[1];
		  temp.val[2] = sum[2];
		  result.push_back(std::make_pair(cv::Point(x,y), temp));
	  }
  
	  normalize_region(result,min_coor);
	  return result;
  }
  
  RegionData find_region(cv::Mat &image, int x, int y, int type, int threshold, cv::Point &min_coor){
	  RegionData region;
	  std::vector<std::vector<bool>> marker(image.cols,std::vector<bool>(image.rows, false));
	  cv::Vec3b target = image.at<cv::Vec3b>(y,x);
  
	  find_region_util(image,marker,region, x, y, target, type, threshold);
  
	  std::pair<cv::Point,cv::Point> minmax_coor = minmax_coordinate(region);
	  min_coor = minmax_coor.first;
	  normalize_region(region,minmax_coor.first);
	  return region;
  }
  
  void unnormalize_region(RegionData &region, cv::Point &min_coor){
	  for (PixelData &value : region){
		  value.first.x += min_coor.x;
		  value.first.y += min_coor.y;
	  }
  }
  
  cv::Mat create_image_from_pixel(cv::Mat &src, VectorOPixel pixel){
	  
	  cv::Mat temp = src.clone();
		  
	  for (PixelData value : pixel){
		  temp.at<cv::Vec3b>(value.first.y,value.first.x)[0] = value.second.val[0];
		  temp.at<cv::Vec3b>(value.first.y,value.first.x)[1] = value.second.val[1];
		  temp.at<cv::Vec3b>(value.first.y,value.first.x)[2] = value.second.val[2];
	  }
	  return temp;
  }
  
  PerimeterData	find_smooth_perimeter(cv::Mat &src, RegionData region, cv::Point min_coor, int kernel_radius, 
									  double sigma, int x, int y, int type, int threshold){
	  RegionData temp_region(region);
	  temp_region = region_smoothing(src, region,min_coor, kernel_radius, sigma);
	  unnormalize_region(temp_region,min_coor);
  
	  cv::Mat temp_image = create_image_from_pixel(src,temp_region);
	  RegionData temp_region_2 = find_region(temp_image,x, y,type, threshold);
	  PerimeterData result = find_perimeter(temp_region_2,type);
	  normalize_region(temp_region,min_coor);
	  return result;
  }
}