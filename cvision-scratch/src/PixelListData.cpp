#include "PixelListData.h"


        MinMaxXY PixelListData<BGRPixel>::minmax_coordinate(PixelList<BGRPixel> &region){

                int x_min = region[0].first.x;
                int y_min = region[0].first.y;
                int x_max = 0;
                int y_max = 0;
                for (BGRPixel value : region){
                    if(value.first.x < x_min) x_min = value.first.x;
                    if(value.first.y < y_min) y_min = value.first.y;

                    if(value.first.x > x_max) x_max = value.first.x;
                    if(value.first.y > y_max) y_max = value.first.y;        
                }
                x_max -= x_min;
                y_max -= y_min;
                return std::make_pair(cv::Point(x_min,y_min), cv::Point(x_max+1, y_max+1));
            }

        void PixelListData<BGRPixel>::normalize_pixel_lists(PixelList<BGRPixel> &region, cv::Point min_coor){

            for (BGRPixel &value : region){
                value.first.x -= min_coor.x;
                value.first.y -= min_coor.y;
            }
        }

        void PixelListData<BGRPixel>::unnormalize_pixel_lists(PixelList<BGRPixel> &region, cv::Point min_coor){
            for (BGRPixel &value : region){
                value.first.x += min_coor.x;
                value.first.y += min_coor.y;
            }
        }

        MinMaxXY PixelListData<BGRPixel>::get_min_max_coordinate(){
            return min_max_coor_;
        }
        PixelList<BGRPixel> PixelListData<BGRPixel>::get_normalized_pixel_list(){
            return pixel_list_;
        }
        PixelList<BGRPixel> PixelListData<BGRPixel>::get_unnormalized_pixel_list(){
            PixelList<BGRPixel> temp(pixel_list_);
            unnormalize_pixel_lists(temp, min_max_coor_.first);
            return temp;
        }
        cv::Mat PixelListData<BGRPixel>::get_image(){
            cv::Mat temp(cv::Size(min_max_coor_.second.x, min_max_coor_.second.y), CV_8UC3, cv::Scalar(255,255,255)); 
            for (BGRPixel value : pixel_list_){
                temp.at<cv::Vec3b>(value.first.y,value.first.x)[0] = value.second.val[0];
                temp.at<cv::Vec3b>(value.first.y,value.first.x)[1] = value.second.val[1];
                temp.at<cv::Vec3b>(value.first.y,value.first.x)[2] = value.second.val[2];
            }
            return temp;
        }

        void PixelListData<BGRPixel>::display(std::string const &win_name){
            cv::Mat temp = get_image();
            cv::namedWindow(win_name, cv::WINDOW_AUTOSIZE);
            cv::imshow(win_name, temp);
            cv::waitKey(0);
        }

        void PixelListData<BGRPixel>::save_image(const char *name){
            cv::Mat temp = get_image();
            cv::imwrite(name, temp);
        }
        bool PixelListData<BGRPixel>::save_list(const char *input_string){
            std::ofstream myfile (input_string);
            if (pixel_list_.size() > 0 && myfile.is_open())
            {
                for(BGRPixel value : pixel_list_){
                    myfile << value.first << " " << value.second << "\n";
                }
                myfile.close();
                return true;
            }
            else return false;
        }