#include <iostream>
#include "ImageAIO.h"

ImageAIO::ImageAIO(){
}
ImageAIO::ImageAIO(cv::Mat &input){
    original_ = input;
}
ImageAIO::ImageAIO(const char* location){
    
    original_ = cv::imread(location,1);
}

ImageAIO::ImageAIO(cv::Mat &input, int x, int y){
    
    original_ = input;
    user_target_.x = x;
    user_target_.y = y;
    calculate_all(x,y);
}
ImageAIO::ImageAIO(const char* location, int x, int y){

    original_ = cv::imread(location,1);
    user_target_.x = x;
    user_target_.y = y;
    calculate_all(x,y);
}

void ImageAIO::set_original (const char* location){
    original_ = cv::imread(location,1);
}
void ImageAIO::calculate_all(int x, int y){
    user_target_.x = x;
    user_target_.y = y;
    region_ = arcv::find_region(original_,x, y, find_region_type_, colour_threshold_, min_coor_);
    perimeter_ = arcv::find_perimeter(region_,find_region_type_);
    region_image_ = arcv::create_image_from_pixel(region_);
    perimeter_image_ = arcv::create_image_from_pixel(perimeter_);
}
void ImageAIO::calculate_all(int x, int y, int type, int threshold){
    user_target_.x = x;
    user_target_.y = y;
    find_region_type_ = type;
    colour_threshold_ = threshold;

    region_ = arcv::find_region(original_,x, y, type, threshold, min_coor_);
    perimeter_ = arcv::find_perimeter(region_,type);
    region_image_ = arcv::create_image_from_pixel(region_);
    perimeter_image_ = arcv::create_image_from_pixel(perimeter_);
}
void ImageAIO::display_original(){
    arcv::display_pixel(original_, "Original");
}
void ImageAIO::display_region(){
    arcv::display_pixel(region_image_, "Region");
}
void ImageAIO::display_perimeter(){
    arcv::display_pixel(perimeter_image_, "Perimeter");
}
void ImageAIO::save_region_image(const char* location){
    arcv::save_pixel(region_image_, location);
}
void ImageAIO::save_perimeter_image(const char* location){
    arcv::save_pixel(perimeter_image_, location);
}

void ImageAIO::display_smoothed_perimeter(int kernel_radius, int gaussian_sigma){

    arcv::PerimeterData smoothed_src = arcv::find_smooth_perimeter(original_,region_, min_coor_, kernel_radius,gaussian_sigma, user_target_.x,user_target_.y,find_region_type_,colour_threshold_);
    cv::Mat smoothed_image = arcv::create_image_from_pixel(smoothed_src);
    arcv::display_pixel(smoothed_image, "Smoothed Perimeter");
}

void ImageAIO::display_smoothed_region(int kernel_radius, int gaussian_sigma){
    
    arcv::RegionData smoothed_src = arcv::region_smoothing(original_, region_ ,min_coor_, kernel_radius, gaussian_sigma);
    cv::Mat smoothed_image = arcv::create_image_from_pixel(smoothed_src);
    arcv::display_pixel(smoothed_image, "Smoothed Region");
}

void ImageAIO::display_smoothed_image(cv::Mat &src, int kernel_radius, int gaussian_sigma){

    cv::Mat smoothed_image = arcv::neighborhood_mean(src, arcv::produce_2d_gaussian_kernel(kernel_radius, gaussian_sigma));
    arcv::display_pixel(smoothed_image, "Smoothed Image");
}

void ImageAIO::save_smoothed_image(const char* location, int kernel_radius, int gaussian_sigma){
    
    arcv::PerimeterData smoothed_src = arcv::find_smooth_perimeter(original_,region_, min_coor_, kernel_radius,gaussian_sigma, user_target_.x,user_target_.y,find_region_type_,colour_threshold_);
    cv::Mat smoothed_image = arcv::create_image_from_pixel(smoothed_src);
    arcv::save_pixel(smoothed_image, location);
}
void ImageAIO::save_smoothed_image(const char* location, cv::Mat &src, int kernel_radius, int gaussian_sigma){
    
    cv::Mat smoothed_image = arcv::neighborhood_mean(src, arcv::produce_2d_gaussian_kernel(kernel_radius, gaussian_sigma));
    arcv::save_pixel(smoothed_image, location);
}

arcv::PerimeterData ImageAIO::find_smoothed_perimeter( int kernel_radius, int gaussian_sigma){

    return arcv::find_smooth_perimeter(original_,region_, min_coor_, kernel_radius,gaussian_sigma, user_target_.x,user_target_.y,find_region_type_,colour_threshold_);
}

arcv::RegionData ImageAIO::calculate_region (int x, int y, int type, int threshold){
    user_target_.x = x;
    user_target_.y = y;
    find_region_type_ = type;
    colour_threshold_ = threshold;
    region_ = arcv::find_region(original_,x,y,type,threshold, min_coor_);
    region_image_ = arcv::create_image_from_pixel(region_);
    return region_;
}
arcv::RegionData ImageAIO::calculate_region (int x, int y){
    user_target_.x = x;
    user_target_.y = y;
    return calculate_region(x,y,find_region_type_, colour_threshold_);
}
arcv::PerimeterData ImageAIO::calculate_perimeter (int type){
    find_region_type_ = type;
    perimeter_ = arcv::find_perimeter(region_,type); 
    perimeter_image_ = arcv::create_image_from_pixel(perimeter_);
    return perimeter_;
}
arcv::PerimeterData ImageAIO::calculate_perimeter (){
    perimeter_ = arcv::find_perimeter(region_,find_region_type_); 
    perimeter_image_ = arcv::create_image_from_pixel(perimeter_);
    return perimeter_;
}