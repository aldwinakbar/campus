#include "PerimeterData.h"

    template <class T> class SmoothData;
    template<>
    class SmoothData<BGRPixel> : public PixelListData<BGRPixel> {
    void abstract_if_pure_virtual(){}
    private: 

        double  gaussian(double x, double mu, double sigma);
        SmoothingKernel produce_2d_gaussian_kernel (int kernelRadius, double sigma);
        cv::Point coordinate_repair(cv::Point size, cv::Point input);
        PixelList<BGRPixel> mat_smoothing(cv::Mat &src, int kernel_radius, double sigma);
        PixelList<BGRPixel> region_smoothing(RegionData<BGRPixel> region, int kernel_radius, double sigma);    
        PixelList<BGRPixel>	find_smooth_perimeter(PerimeterData<BGRPixel> perimeter, int kernel_radius, double sigma);

    public: 
        SmoothData(const SmoothData<BGRPixel> &input);
        SmoothData(cv::Mat input, int kernel_radius, double sigma);
        SmoothData(RegionData<BGRPixel> input, int kernel_radius, int sigma);
        SmoothData(PerimeterData<BGRPixel> input, int kernel_radius, int sigma);
    };