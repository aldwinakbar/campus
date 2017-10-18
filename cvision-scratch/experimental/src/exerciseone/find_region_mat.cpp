#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#define COLOUR_THRESHOLD 120

using namespace std;
using namespace cv;

void show_mat(const cv::Mat &image, std::string const &win_name);

cv::Mat&                    access_mat(cv::Mat &mat);
double colour_distance(Vec3b e1,Vec3b e2);
bool                        compare_v3b(Vec3b a, Vec3b b);
void                        find_region(Mat &image,vector<vector<bool>> &marker, vector<pair<Point,Vec3b>> &region, int x, int y, Vec3b target, int type);
vector<pair<Point,Vec3b>>   find_vector_region(Mat &image, int x, int y, int type);
pair<Point,Point>           minmax_coordinate(vector<pair<Point,Vec3b>> &region);
void                        normalize_region(vector<pair<Point,Vec3b>> &region, Point &min_coor);
Mat                         create_region_image(Mat &image,int x, int y, int type);
    
int main(int argc, char **argv) {
    if (argc != 3) {
        printf("usage: Opencv_Test <Image_Path> <Output_Path>\n");
        return -1;
    }

    Mat image;
    image = imread(argv[1], 1);

    if (!image.data) {
        printf("No image data (warning: OpenCV recognize files by extensions)\n");
        return -1;
    }

    Mat test = create_region_image(image, 86,359,0);
    
    show_mat(test, "region");

    show_mat(image, "Input");

    image = access_mat(image);

    show_mat(image, "Output");

    imwrite(argv[2], image);

    return 0;
}

cv::Mat& access_mat(cv::Mat &mat) {

    int nRows = mat.rows;
    int nCols = mat.cols;
    int i, j;
 
    // BGR image
    Vec3b *p;
    for (i = 0; i < nRows; ++i) {
        p = mat.ptr<Vec3b>(i);
        for (j = 0; j < nCols; ++j) {
            p[j][0] = ~p[j][0];
            p[j][1] = ~p[j][1];
            p[j][2] = ~p[j][2];
        }
    }    
    return mat;
}

void show_mat(const cv::Mat &image, std::string const &win_name) {
    namedWindow(win_name, WINDOW_AUTOSIZE);
    imshow(win_name, image);
    waitKey(0);
}

double colour_distance(Vec3b e1,Vec3b e2)
{
  long rmean = ( (long)e1.val[2] + (long)e2.val[2] ) / 2;
  long r = (long)e1.val[2] - (long)e2.val[2];
  long g = (long)e1.val[1] - (long)e2.val[1];
  long b = (long)e1.val[0] - (long)e2.val[0];
  return sqrt((((512+rmean)*r*r)>>8) + 4*g*g + (((767-rmean)*b*b)>>8));
}

bool compare_v3b(Vec3b a, Vec3b b){
    if(colour_distance(a,b) < COLOUR_THRESHOLD ) return true;
    return false;
}
void find_region(Mat &image,vector<vector<bool>> &marker, vector<pair<Point,Vec3b>> &region, int x, int y, Vec3b target, int type){
    
        int M = image.cols;
        int N = image.rows;
        // Base cases
        if (x < 0 || x >= M || y < 0 || y >= N)
            return;
        if (!compare_v3b(image.at<Vec3b>(y,x), target))
            return;
        if (compare_v3b(image.at<Vec3b>(y,x), target) && marker[x][y])
            return;
     
        // Replace the color at (x, y)
        region.push_back(make_pair(Point(x,y),image.at<Vec3b>(y,x)));
        marker[x][y] = true;
        
        if(type == 1){
            // Recur for all direction
            find_region(image,marker, region, x+1, y, target,type);
            find_region(image,marker,region, x-1, y, target, type);
            find_region(image,marker,region, x, y+1, target,type);
            find_region(image,marker, region,x, y-1, target, type);
    
            find_region(image,marker,region, x-1, y+1, target, type);
            find_region(image,marker,region, x+1, y+1, target,  type);
            find_region(image,marker,region, x+1, y-1, target,  type);
            find_region(image,marker, region,x-1, y-1, target,  type);
        }
        
        else{
            // Recur for north, east, south and west
            find_region(image,marker,region, x+1, y, target,  type);
            find_region(image,marker,region, x-1, y, target,  type);
            find_region(image,marker,region, x, y+1, target,  type);
            find_region(image,marker,region, x, y-1, target, type);
        }
    }
    
    vector<pair<Point,Vec3b>> find_vector_region(Mat &image, int x, int y, int type){
        vector<pair<Point,Vec3b>> region;
        vector<vector<bool>> marker(image.cols,vector<bool>(image.rows, false));
        Vec3b target = image.at<Vec3b>(y,x);
    
        find_region(image,marker,region, x, y, target, type);
        return region;
    }
    pair<Point,Point> minmax_coordinate(vector<pair<Point,Vec3b>> &region){
        int x_min = region[0].first.x;
        int y_min = region[0].first.y;
        int x_max = 0;
        int y_max = 0;
        for (pair<Point,Vec3b> value : region){
            if(value.first.x < x_min) x_min = value.first.x;
            if(value.first.y < y_min) y_min = value.first.y;
    
            if(value.first.x > x_max) x_max = value.first.x;
            if(value.first.y > y_max) y_max = value.first.y;        
        }
        x_max -= x_min;
        y_max -= y_min;
        return make_pair(Point(x_min,y_min), Point(x_max+1, y_max+1));
    }
    
    void normalize_region(vector<pair<Point,Vec3b>> &region, Point &min_coor){
        for (pair<Point,Vec3b> &value : region){
            value.first.x -= min_coor.x;
            value.first.y -= min_coor.y;
        }
    }

    Mat create_region_image(Mat &image,int x, int y, int type){

        vector<pair<Point,Vec3b>> region = find_vector_region(image,x, y,type);
        pair<Point,Point> minmax_coor = minmax_coordinate(region);
        normalize_region(region,minmax_coor.first);
        
        cv::Mat temp(cv::Size(minmax_coor.second.x, minmax_coor.second.y), CV_8UC3, Scalar(255,255,255)); 
    
        for (pair<Point,Vec3b> value : region){
            temp.at<Vec3b>(value.first.y,value.first.x)[0] = value.second.val[0];
            temp.at<Vec3b>(value.first.y,value.first.x)[1] = value.second.val[1];
            temp.at<Vec3b>(value.first.y,value.first.x)[2] = value.second.val[2];
        }
        return temp;
    }
    