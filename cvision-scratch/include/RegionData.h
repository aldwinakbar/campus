#include "PixelListData.h"

    template <class T> class RegionData;
	template <>
	class RegionData<BGRPixel> : public PixelListData<BGRPixel> {
        void abstract_if_pure_virtual(){}   

        private:

            cv::Mat             original_;
            cv::Point           user_target_;
            int                 type_;
            int                 threshold_;

            double colour_distance(cv::Vec3b e1,cv::Vec3b e2);
            bool compare_v3b(cv::Vec3b a, cv::Vec3b b, int threshold);
            void find_region_util(cv::Mat &image,std::vector<std::vector<bool>> &marker, 
                              PixelList<BGRPixel> &region, int x, int y, cv::Vec3b target, 
                              int type, int threshold);
		    PixelList<BGRPixel>  find_region(cv::Mat &image, int x, int y, int type, int threshold);

        public:       
            RegionData(RegionData<BGRPixel> &input);
            RegionData(cv::Mat &image, int x, int y, int type, int threshold);
            int get_type();
            cv::Point get_user_target();
            int get_threshold();
            cv::Mat get_original_image();
    };