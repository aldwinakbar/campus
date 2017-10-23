#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

#define COLOUR_THRESHOLD 500

using namespace std;
using namespace cv;

double                      colour_distance(Vec3b e1,Vec3b e2);
bool                        compare_v3b(Vec3b a, Vec3b b, int threshold);
void                        find_region_util(Mat &image,vector<vector<bool>> &marker, vector<pair<Point,Vec3b>> &region, int x, int y, Vec3b target, int type, int threshold);
vector<pair<Point,Vec3b>>   find_region(Mat &image, int x, int y, int type, int threshold);
pair<Point,Point>           minmax_coordinate(vector<pair<Point,Vec3b>> &region);
void                        normalize_region(vector<pair<Point,Vec3b>> &region, Point &min_coor);
Mat                         create_image_from_pixel(vector<pair<Point,Vec3b>> pixel);
vector<pair<Point,Vec3b>>   find_perimeter(vector<pair<Point,Vec3b>> &region, int type);
void                        display_image(const char* location, std::string const &win_name);
void                        display_pixel(const cv::Mat &image, std::string const &win_name);
void                        save_pixel(Mat &image, const char *name);

void                        unnormalize_region(vector<pair<Point,Vec3b>> &region, Point &min_coor);
vector<pair<Point,Vec3b>>   find_region(Mat &image, int x, int y, int type, int threshold, Point &min_coor);

double                      gaussian (double x, double mu, double sigma);
std::vector<std::vector<double>> produce_2d_gaussian_kernel (int kernelRadius, double sigma);
Mat                         neighborhood_mean(Mat &src, vector<vector<double>> kernel); 
vector<pair<Point,Vec3b>>   region_smoothing(Mat &src,vector<pair<Point,Vec3b>> region,Point min_coor, int kernel_radius, double sigma);
Mat                         create_image_from_pixel(Mat &src, vector<pair<Point,Vec3b>> pixel);
vector<pair<Point,Vec3b>>   find_smooth_perimeter(Mat &src, vector<pair<Point,Vec3b>> region,Point min_coor, int kernel_radius, double sigma, int x, int y, int type, int threshold);


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
    Point min_coor;
    vector<pair<Point,Vec3b>> region = find_region(image,100, 100,1, 150, min_coor);
    vector<pair<Point,Vec3b>> perimeter = find_perimeter(region,1);

    Mat test = create_image_from_pixel(region);
    display_pixel(test, "Region");

    vector<pair<Point,Vec3b>> temp_region = region_smoothing(image, region,min_coor, 10, 10);
    
    Mat temp_image = create_image_from_pixel(temp_region);
    display_pixel(temp_image, "Smooth Region");
    
    vector<pair<Point,Vec3b>> perimeter2 = find_smooth_perimeter(image,region, min_coor, 10,10, 100,100,1,150);
    display_pixel(create_image_from_pixel(perimeter2), "Perimeter 2");

    display_image(argv[1], "Input");

    Mat smoothed_input = neighborhood_mean(image,produce_2d_gaussian_kernel(10,10));
    display_pixel(smoothed_input, "Smooth Region");

    save_pixel(image, argv[2]);
    return 0;
}

void display_image(const char* location, std::string const &win_name) {
    Mat image = imread(location, 1);

    if (!image.data) {
        printf("No image data (warning: OpenCV recognize files by extensions)\n");
        return;
    }

    namedWindow(win_name, WINDOW_AUTOSIZE);
    imshow(win_name, image);
    waitKey(0);
}

void display_pixel(const cv::Mat &image, std::string const &win_name) {
    namedWindow(win_name, WINDOW_AUTOSIZE);
    imshow(win_name, image);
    waitKey(0);
}

void save_pixel(Mat &image, const char *name){
    imwrite(name, image);
}

double colour_distance(Vec3b e1,Vec3b e2)
{
  long rmean = ( (long)e1.val[2] + (long)e2.val[2] ) / 2;
  long r = (long)e1.val[2] - (long)e2.val[2];
  long g = (long)e1.val[1] - (long)e2.val[1];
  long b = (long)e1.val[0] - (long)e2.val[0];
  return sqrt((((512+rmean)*r*r)>>8) + 4*g*g + (((767-rmean)*b*b)>>8));
}

bool compare_v3b(Vec3b a, Vec3b b, int threshold){
    if(colour_distance(a,b) < threshold ) return true;
    return false;
}
void find_region_util(Mat &image,vector<vector<bool>> &marker, vector<pair<Point,Vec3b>> &region, int x, int y, Vec3b target, int type, int threshold){
    
        int M = image.cols;
        int N = image.rows;
        // Base cases
        if (x < 0 || x >= M || y < 0 || y >= N)
            return;
        if (!compare_v3b(image.at<Vec3b>(y,x), target, threshold))
            return;
        if (compare_v3b(image.at<Vec3b>(y,x), target, threshold) && marker[x][y])
            return;
     
        // Replace the color at (x, y)
        region.push_back(make_pair(Point(x,y),image.at<Vec3b>(y,x)));
        marker[x][y] = true;
        
        if(type == 1){
            // Recur for all direction
            find_region_util(image,marker, region, x+1, y, target,type,threshold);
            find_region_util(image,marker,region, x-1, y, target, type,threshold);
            find_region_util(image,marker,region, x, y+1, target,type,threshold);
            find_region_util(image,marker, region,x, y-1, target, type,threshold);
    
            find_region_util(image,marker,region, x-1, y+1, target, type,threshold);
            find_region_util(image,marker,region, x+1, y+1, target,  type,threshold);
            find_region_util(image,marker,region, x+1, y-1, target,  type,threshold);
            find_region_util(image,marker, region,x-1, y-1, target,  type,threshold);
        }
        
        else{
            // Recur for north, east, south and west
            find_region_util(image,marker,region, x+1, y, target,  type,threshold);
            find_region_util(image,marker,region, x-1, y, target,  type,threshold);
            find_region_util(image,marker,region, x, y+1, target,  type,threshold);
            find_region_util(image,marker,region, x, y-1, target, type,threshold);
        }
    }
    
    vector<pair<Point,Vec3b>> find_region(Mat &image, int x, int y, int type, int threshold){
        vector<pair<Point,Vec3b>> region;
        vector<vector<bool>> marker(image.cols,vector<bool>(image.rows, false));
        Vec3b target = image.at<Vec3b>(y,x);
    
        find_region_util(image,marker,region, x, y, target, type, threshold);

        pair<Point,Point> minmax_coor = minmax_coordinate(region);
        normalize_region(region,minmax_coor.first);
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

    Mat create_image_from_pixel(vector<pair<Point,Vec3b>> pixel){
        
        pair<Point,Point> minmax_coor = minmax_coordinate(pixel);
        cv::Mat temp(cv::Size(minmax_coor.second.x, minmax_coor.second.y), CV_8UC3, Scalar(255,255,255)); 
            
        for (pair<Point,Vec3b> value : pixel){
            temp.at<Vec3b>(value.first.y,value.first.x)[0] = value.second.val[0];
            temp.at<Vec3b>(value.first.y,value.first.x)[1] = value.second.val[1];
            temp.at<Vec3b>(value.first.y,value.first.x)[2] = value.second.val[2];
        }
        return temp;
    }

vector<pair<Point,Vec3b>> find_perimeter(vector<pair<Point,Vec3b>> &region, int type){

    vector<pair<Point,Vec3b>> perimeter;
    pair<Point,Point> minmax_coor = minmax_coordinate(region);

    cv::Mat temp(cv::Size(minmax_coor.second.x, minmax_coor.second.y), CV_8UC3, Scalar(255,255,255)); 
    vector<vector<bool>> marker(minmax_coor.second.x, vector<bool>(minmax_coor.second.y, false));

    for (pair<Point,Vec3b> value : region){
        temp.at<Vec3b>(value.first.y,value.first.x)[0] = value.second.val[0];
        temp.at<Vec3b>(value.first.y,value.first.x)[1] = value.second.val[1];
        temp.at<Vec3b>(value.first.y,value.first.x)[2] = value.second.val[2];

        marker[value.first.x][value.first.y] = true;
    } 

    int x_size = marker.size();
    int y_size = marker[0].size();
    for (int i=0; i < x_size; i++){
        for (int j=0; j < y_size; j++){
           if(marker[i][j] == false ) continue;
           else if (marker[i][j] == true){
                if( type == 1){
                // for 8-point style
                
                    if(j-1 < 0 || i-1 < 0 || i+1 >= x_size || j+1 >= y_size || 
                        !marker[i-1][j] || !marker[i+1][j] || !marker[i][j+1] ||
                        !marker[i][j-1] || !marker[i-1][j+1] || !marker[i+1][j+1] || 
                        !marker[i+1][j-1] || !marker[i-1][j-1]){
                            
                            perimeter.push_back(make_pair(Point(i,j),temp.at<Vec3b>(j,i)));
                    }
                }
                // for 4-point style
                else{
                    if(j-1 < 0 || i-1 < 0 || i+1 >= x_size || j+1 >= y_size || 
                        !marker[i-1][j] || !marker[i+1][j] || !marker[i][j+1] ||
                        !marker[i][j-1]){
                            
                            perimeter.push_back(make_pair(Point(i,j),temp.at<Vec3b>(j,i)));
                    }
                }
           }
        }
    }
    return perimeter;
}
    
double gaussian (double x, double mu, double sigma) {
  return std::exp( -(((x-mu)/(sigma))*((x-mu)/(sigma)))/2.0 );
}

std::vector<std::vector<double>> produce_2d_gaussian_kernel (int kernelRadius, double sigma) {
  std::vector<std::vector<double>> kernel2d(2*kernelRadius+1, std::vector<double>(2*kernelRadius+1));
  double sum = 0;
  // compute values
  for (int row = 0; row < kernel2d.size(); row++)
    for (int col = 0; col < kernel2d[row].size(); col++) {
      double x = gaussian(row, kernelRadius, sigma)
               * gaussian(col, kernelRadius, sigma);
      kernel2d[row][col] = x;
      sum += x;
    }
  // normalize
  for (int row = 0; row < kernel2d.size(); row++)
    for (int col = 0; col < kernel2d[row].size(); col++)
      kernel2d[row][col] /= sum;
  return kernel2d;
}

 
Mat neighborhood_mean(Mat &src, vector<vector<double>> kernel){
    Mat dst = src.clone();
    int radius = (kernel.size() - 1)/2;
    int lower_limit = 0 - radius;
    int upper_limit = radius;
    float sum[3];
    for(int y = radius; y < src.rows - radius; y++){
        for(int x = radius; x < src.cols - radius; x++){
            sum[0] = 0.0;
            sum[1] = 0.0;
            sum[2] = 0.0;
            for(int k = lower_limit; k <= upper_limit;k++){
                for(int j = lower_limit; j <= upper_limit; j++){
                    sum[0] = sum[0] + kernel[j+radius][k+radius]*src.at<Vec3b>(y - j, x - k)[0];
                    sum[1] = sum[1] + kernel[j+radius][k+radius]*src.at<Vec3b>(y - j, x - k)[1];
                    sum[2] = sum[2] + kernel[j+radius][k+radius]*src.at<Vec3b>(y - j, x - k)[2];
                }
            }
            dst.at<Vec3b>(y,x)[0] = sum[0];
            dst.at<Vec3b>(y,x)[1] = sum[1];
            dst.at<Vec3b>(y,x)[2] = sum[2];
        }
    }
    return dst;
}
vector<pair<Point,Vec3b>> region_smoothing(Mat &src,vector<pair<Point,Vec3b>> region,Point min_coor, int kernel_radius, double sigma){
    std::vector<std::vector<double>> kernel = produce_2d_gaussian_kernel(kernel_radius, sigma);
    vector<pair<Point,Vec3b>> result;
    int radius = (kernel.size() - 1)/2;
    int lower_limit = 0 - radius;
    int upper_limit = radius;
    float sum[3];
    int M = src.cols;
    int N = src.rows;
    unnormalize_region(region,min_coor); 
    for(pair<Point, Vec3b> value : region){
        int x = value.first.x;
        int y = value.first.y;
        sum[0] = 0.0;
        sum[1] = 0.0;
        sum[2] = 0.0;
        for(int k = lower_limit; k <= upper_limit;k++){
            for(int j = lower_limit; j <= upper_limit; j++){
                if ((x-k) < 0 || (x-k) >= M || (y - j) < 0 || (y - j) >= N) continue;

                sum[0] = sum[0] + kernel[j+radius][k+radius]*src.at<Vec3b>(y - j, x - k)[0];
                sum[1] = sum[1] + kernel[j+radius][k+radius]*src.at<Vec3b>(y - j, x - k)[1];
                sum[2] = sum[2] + kernel[j+radius][k+radius]*src.at<Vec3b>(y - j, x - k)[2];
            }
        }
        Vec3b temp;
        temp.val[0] = sum[0];
        temp.val[1] = sum[1];
        temp.val[2] = sum[2];
        result.push_back(make_pair(Point(x,y), temp));
    }

    normalize_region(result,min_coor);
    return result;
}


vector<pair<Point,Vec3b>> find_region(Mat &image, int x, int y, int type, int threshold, Point &min_coor){
    vector<pair<Point,Vec3b>> region;
    vector<vector<bool>> marker(image.cols,vector<bool>(image.rows, false));
    Vec3b target = image.at<Vec3b>(y,x);

    find_region_util(image,marker,region, x, y, target, type, threshold);

    pair<Point,Point> minmax_coor = minmax_coordinate(region);
    min_coor = minmax_coor.first;
    normalize_region(region,minmax_coor.first);
    return region;
}


void unnormalize_region(vector<pair<Point,Vec3b>> &region, Point &min_coor){
    for (pair<Point,Vec3b> &value : region){
        value.first.x += min_coor.x;
        value.first.y += min_coor.y;
    }
}


Mat create_image_from_pixel(Mat &src, vector<pair<Point,Vec3b>> pixel){
    
    cv::Mat temp = src.clone();
        
    for (pair<Point,Vec3b> value : pixel){
        temp.at<Vec3b>(value.first.y,value.first.x)[0] = value.second.val[0];
        temp.at<Vec3b>(value.first.y,value.first.x)[1] = value.second.val[1];
        temp.at<Vec3b>(value.first.y,value.first.x)[2] = value.second.val[2];
    }
    return temp;
}

vector<pair<Point,Vec3b>>   find_smooth_perimeter(Mat &src, vector<pair<Point,Vec3b>> region,Point min_coor, int kernel_radius, double sigma,int x, int y, int type, int threshold){
    vector<pair<Point,Vec3b>> temp_region(region);
    temp_region = region_smoothing(src, region,min_coor, kernel_radius, sigma);
    unnormalize_region(temp_region,min_coor);

    Mat temp_image = create_image_from_pixel(src,temp_region);
    vector<pair<Point,Vec3b>> temp_region_2 = find_region(temp_image,x, y,type, threshold);
    vector<pair<Point,Vec3b>> result = find_perimeter(temp_region_2,type);
    normalize_region(temp_region,min_coor);
    return result;
}