#include "RegionData.h"

    template <class T> class PerimeterData;
    template <>
	class PerimeterData<BGRPixel> : public PixelListData<BGRPixel> {
        void abstract_if_pure_virtual(){}

        private:

            RegionData<BGRPixel> *region_data_;
            PixelList<BGRPixel> find_perimeter (PixelList<BGRPixel> pixel_list, FindRegionType type);
        public:
            
            PerimeterData(const PerimeterData<BGRPixel> &input);
            PerimeterData(RegionData<BGRPixel> input);
            ~PerimeterData();
            RegionData<BGRPixel> *get_region_data();
    };