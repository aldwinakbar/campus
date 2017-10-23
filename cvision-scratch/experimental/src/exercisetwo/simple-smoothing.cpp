#include<iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
 
using namespace std;
using namespace cv;

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

int main()
{
 
      Mat src, dst;
           
      src = imread("test1.png", CV_LOAD_IMAGE_COLOR);
    
      if( !src.data )
      { 
          cout << "no data\n";
          return -1; }
 
          cout << "data ok\n";
          
      vector<vector<float>> Kernel {
                            {1/9.0, 1/9.0, 1/9.0},
                            {1/9.0, 1/9.0, 1/9.0},
                            {1/9.0, 1/9.0, 1/9.0}
                           }; 

        //dst = convolution_on_mat(src, Kernel);
        dst = neighborhood_mean(src, produce_2d_gaussian_kernel(1, 6.0));
        cout << 1/2 << endl;
        namedWindow("final");
        imshow("final", dst);
 
        namedWindow("initial");
        imshow("initial", src);
 
      waitKey(0);
 
 
    return 0;
}