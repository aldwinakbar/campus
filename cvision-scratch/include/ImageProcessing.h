#ifndef IMGPROC_H
#define IMGPROC_H

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

namespace arcv{

		using PixelData  = std::pair<cv::Point,cv::Vec3b>;
		using VectorOPixel = std::vector<PixelData>;
		using MinMaxXY	= std::pair<cv::Point,cv::Point>;
		using RegionData = VectorOPixel;
		using PerimeterData = VectorOPixel;

		double                      	colour_distance(cv::Vec3b e1,cv::Vec3b e2);
		bool                        	compare_v3b(cv::Vec3b a, cv::Vec3b b, int threshold);
		MinMaxXY						minmax_coordinate(RegionData &region);
		void                       		normalize_region(RegionData &region, cv::Point &min_coor);
		cv::Mat                         create_image_from_pixel(VectorOPixel pixel);
		void              		        display_image(const char* location, std::string const &win_name);
		void                     		display_pixel(const cv::Mat &image, std::string const &win_name);
		void                        	save_pixel(cv::Mat &image, const char *name);
		void                        	find_region_util(cv::Mat &image,std::vector<std::vector<bool>> &marker, 
														 RegionData &region, int x, int y, cv::Vec3b target,
														 int type, int threshold);
		RegionData 						find_region (cv::Mat &image, int x, int y, int type, int threshold);
		PerimeterData					find_perimeter (RegionData &region, int type);
			
		void                        	unnormalize_region(RegionData &region, cv::Point &min_coor);
		RegionData 						find_region(cv::Mat &image, int x, int y, int type, int threshold, 
													cv::Point &min_coor);
		
		double                      	gaussian(double x, double mu, double sigma);
		std::vector<std::vector<double>>produce_2d_gaussian_kernel(int kernelRadius, double sigma);
		cv::Mat                         neighborhood_mean(cv::Mat &src, std::vector<std::vector<double>> kernel); 
		RegionData 						region_smoothing(cv::Mat &src,RegionData region,cv::Point min_coor, 
														 int kernel_radius, double sigma);
		cv::Mat                         create_image_from_pixel(cv::Mat &src, VectorOPixel pixel);
		PerimeterData 					find_smooth_perimeter(cv::Mat &src, RegionData region, cv::Point min_coor,
															  int kernel_radius, double sigma, int x, int y, 
															  int type, int threshold);
		
}

#endif