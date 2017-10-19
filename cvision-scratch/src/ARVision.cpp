#include <iostream>
#include "SmoothData.h"
#include <string>

using namespace std;
using namespace cv;

int main(){
    
    Mat input;
    input = imread("images/test3.png", CV_LOAD_IMAGE_COLOR);
    if(!input.data) return -1;
    
    RegionData<BGRPixel> sample(input, 100,100,1,150);
    PerimeterData<BGRPixel> sample_two(sample);
    SmoothData<BGRPixel> sample_three(input, 1, 5);

    SmoothData<BGRPixel> sample_four(sample, 5, 10);
    SmoothData<BGRPixel> sample_five(sample_two, 10, 10);

    sample_two.display("Perimeter"); 
    sample.display("Region");

    sample_three.display("Smat");
    sample_four.display("SRegion");
    sample_five.display("SR");

    sample.save_image("out.png");
    sample_two.save_image("out2.png");
    waitKey(0);
    return 0;
}