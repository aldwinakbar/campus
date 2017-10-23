#include <iostream>
#include "SmoothData.h"
#include <string>

using namespace std;
using namespace cv;

int main(){
    
    Mat input;
    input = imread("test4.jpg", CV_LOAD_IMAGE_COLOR);
    if(!input.data) return -1;
    
    RegionData<BGRPixel> sample(input, 1000,1000,FindRegionType::Four_CD,150);
    PerimeterData<BGRPixel> sample_two(sample);
    cout << "finished" << endl;
    SmoothData<BGRPixel> sample_three(input, 2, 2);

   // SmoothData<BGRPixel> sample_four(sample, 2, 2);
   // SmoothData<BGRPixel> sample_five(sample_two, 2, 2);

   // Mat temp_six = sample_three.get_image().clone();
   // RegionData<BGRPixel> sample_six(temp_six, 100,100,FindRegionType::Eight_CD,150);
    
    sample_two.display("Perimeter"); 
    sample.display("Region");

    
    sample_three.display("Smat");
    //sample_four.display("SRegion");
    //sample_six.display("SRegion2");
    //sample_five.display("SR");

    //sample.save_image("out.png");
    //sample_three.save_list("test.txt");
    //sample_two.save_image("out2.png");
    
    waitKey(0);
    return 0;
}