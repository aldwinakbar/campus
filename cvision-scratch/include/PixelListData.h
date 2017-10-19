#include <vector>
#include <string>
#include <opencv2/opencv.hpp>


	using GPixel	= std::pair<cv::Point,uchar>;
    using BGRPixel  = std::pair<cv::Point,cv::Vec3b>;
    using SmoothingKernel = std::vector<std::vector<double>>;

	template <class T>	using PixelList = std::vector<T>;
    using MinMaxXY	= std::pair<cv::Point,cv::Point>; 

    template <class T> class PixelListData;

    template <>
    class PixelListData<BGRPixel>{

    protected:
        PixelList<BGRPixel>	pixel_list_;
        MinMaxXY 		    min_max_coor_;
        
        MinMaxXY minmax_coordinate(PixelList<BGRPixel> &region);
        void normalize_pixel_lists(PixelList<BGRPixel> &region, cv::Point min_coor);
        void unnormalize_pixel_lists(PixelList<BGRPixel> &region, cv::Point min_coor);

    public:
        virtual void abstract_if_pure_virtual() = 0; 

        MinMaxXY get_min_max_coordinate();
        PixelList<BGRPixel> get_normalized_pixel_list();
        PixelList<BGRPixel> get_unnormalized_pixel_list();
        cv::Mat get_image();
        void display(std::string const &win_name);
        void save_image(const char *name);
        bool save_list(const char *input_string);
    };