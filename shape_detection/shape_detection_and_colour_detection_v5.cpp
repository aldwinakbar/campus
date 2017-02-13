#include <vector>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/tracking.hpp>
#define MAX_CONTOUR_SIZE 0

using namespace cv;
using namespace std;

RNG rng(12345);

/**
 * Helper function to find a cosine of angle between vectors
 * from pt0->pt1 and pt0->pt2
 */
static double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0);
void setHSVRange(int lowh, int highh, int lows, int highs, int lowv, int highv);
int imageProcessing(int shape_type, Mat imgInput, int minimum_area, int *detected_center_x, int *detected_center_y, double *contour_area, double* detected_radius, Mat& canny_detection);
int iLowH 	= 0;	// yellow = 15, red = 166 , blue = 92
int iHighH 	= 179;	// yellow = 29, red = 179 , blue = 114

int iLowS	= 90; // lower this to allow more noise, 80 is normal
int iHighS 	= 255;

int iLowV 	= 0; // lower this to allow more noise
int iHighV 	= 255;

int main( int argc, char** argv ){
	
	VideoCapture cap(0); //capture the video from webcam
	
	if (!cap.isOpened()){  // if not success, exit program
		cout << "Cannot open the web cam" << endl;
		return -1;
	}
	
	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
	//Create trackbars in "Control" window
	createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	createTrackbar("HighH", "Control", &iHighH, 179);
	
	createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	createTrackbar("HighS", "Control", &iHighS, 255);
	
	createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
	createTrackbar("HighV", "Control", &iHighV, 255);
	
	
	namedWindow("Image", CV_WINDOW_NORMAL); //create a window called "Thresholded Image"
		
	setHSVRange(0,179,90,255,0,255);
		
	while (true){
		
		Mat imageRead;//	 = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);
	
		bool bSuccess = cap.read(imageRead); // read a new frame from video
		if (!bSuccess){ //if not success, break loop
			
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}
		
		int center_buoy_x	= 0;
		int center_buoy_y 	= 0;
		double buoy_area	= 0;
		double radius_buoy	= 0;
		
		Mat canny_detection;
		std::vector<cv::Point> contour_shape;
	
		//int buoy_number = imageProcessing(3, imageRead, MAX_CONTOUR_SIZE, &center_buoy_x, &center_buoy_y, &buoy_area, &radius_buoy);
		int buoy_number = imageProcessing(12, imageRead, 0, &center_buoy_x, &center_buoy_y, &buoy_area, &radius_buoy, canny_detection);
		
		
		cout << "######## Posisi Yellow #########" << endl;
		cout << "Detected Buoy : " << buoy_number << endl;
		cout << "Posisi X  : " << center_buoy_x << endl;
		cout << "Posisi Y  : " << center_buoy_y << endl;
		cout << "Bouy Size : " << buoy_area << endl;
		cout << endl;
		cout << endl;
		
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		Point2f circle_center;
		circle_center.x = center_buoy_x;
		circle_center.y = center_buoy_y;
		circle( imageRead, circle_center, radius_buoy, color, 4, 8, 0 );
		
		imshow("Image Canny", canny_detection );
		imshow("Image", imageRead );
		
		if (waitKey(30) == 27){ //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
			
			cout << "esc key is pressed by user" << endl;
			break;
		}
		
	}
	
	return 0;
}
