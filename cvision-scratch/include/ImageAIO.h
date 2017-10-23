#ifndef IMGAIO_H
#define IMGAIO_H

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "ImageProcessing.h"

class ImageAIO {

    public:
        cv::Mat original_;
        cv::Mat region_image_;
        cv::Mat perimeter_image_;
        cv::Point min_coor_;
        cv::Point user_target_;
        arcv::RegionData region_;
        arcv::PerimeterData perimeter_;
        int colour_threshold_ = 150;
        int find_region_type_ = 0;

        ImageAIO();
        ImageAIO(cv::Mat &input);
        ImageAIO(cv::Mat &input, int x, int y);
        ImageAIO(const char* location);
        ImageAIO(const char* location, int x, int y);

        void set_original (const char* location);
        void calculate_all(int x, int y);
        void calculate_all(int x, int y, int type, int threshold);
        void display_original();
        void display_region();
        void display_perimeter();
        void save_region_image(const char* location);
        void save_perimeter_image(const char* location);

        void display_smoothed_perimeter(int kernel_radius, int gaussian_sigma);
        void display_smoothed_region(int kernel_radius, int gaussian_sigma);
        void display_smoothed_image(cv::Mat &src, int kernel_radius, int gaussian_sigma);
        void save_smoothed_image(const char* location, int kernel_radius, int gaussian_sigma);
        void save_smoothed_image(const char* location, cv::Mat &src, int kernel_radius, int gaussian_sigma);

        arcv::PerimeterData find_smoothed_perimeter(int kernel_radius, int gaussian_sigma);
        
        arcv::RegionData calculate_region (int x, int y, int type, int threshold);
        arcv::RegionData calculate_region (int x, int y);
        arcv::PerimeterData calculate_perimeter (int type);
        arcv::PerimeterData calculate_perimeter ();
};

#endif