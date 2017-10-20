#include "PixelListData.h"

    enum FindRegionType { Four_CD = 0, Eight_CD = 1 };  

    template <class T> class RegionData;
	template <>
	class RegionData<BGRPixel> : public PixelListData<BGRPixel> {
        void abstract_if_pure_virtual(){}   

        private:

            cv::Mat             original_;
            cv::Point           user_target_;
            FindRegionType      type_;
            int                 threshold_;

            double colour_distance(cv::Vec3b e1,cv::Vec3b e2);
            bool compare_v3b(cv::Vec3b a, cv::Vec3b b, int threshold);
            void find_region_util(cv::Mat &image,std::vector<std::vector<bool>> &marker, 
                              PixelList<BGRPixel> &region, int x, int y, cv::Vec3b target, 
                              FindRegionType type, int threshold);
		    PixelList<BGRPixel>  find_region(cv::Mat &image, int x, int y, FindRegionType type, int threshold);

        public:       
            RegionData(RegionData<BGRPixel> &input);
            RegionData(cv::Mat &image, int x, int y, FindRegionType type, int threshold);
            FindRegionType get_type();
            cv::Point get_user_target();
            int get_threshold();
            cv::Mat get_original_image();
    };