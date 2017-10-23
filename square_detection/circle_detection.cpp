#include <vector>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/tracking.hpp>

using namespace cv;
using namespace std;

bool paused = false;

int main( int argc, char** argv ){
	
	//VideoCapture cap("test.avi"); //capture the video from webcam
	VideoCapture cap("Sore.avi"); //capture the video from webcam
	
	if (!cap.isOpened()){  // if not success, exit program
		cout << "Cannot open the web cam" << endl;
		return -1;
	}
	
	namedWindow("Image", CV_WINDOW_NORMAL); //create a window called "Thresholded Image"
	Mat imageRead;//	 = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);
		
	while (true){
		
		
		if (!paused) {
			bool bSuccess = cap.read(imageRead); // read a new frame from video
			if (!bSuccess){ //if not success, break loop
				
				cout << "Cannot read a frame from video stream" << endl;
				break;
			}
		}
		Mat gray;
		 cvtColor(imageRead, gray, CV_BGR2GRAY);
		// smooth it, otherwise a lot of false circles may be detected
		GaussianBlur( gray, gray, Size(9, 9), 2, 2 );
		vector<Vec3f> circles;
		HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 2, gray.rows/4, 200, 100 );
		for( size_t i = 0; i < circles.size(); i++ )
		{
			 Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			 int radius = cvRound(circles[i][2]);
			 // draw the circle center
			 circle( imageRead, center, 3, Scalar(0,255,0), -1, 8, 0 );
			 // draw the circle outline
			 circle( imageRead, center, radius, Scalar(0,0,255), 3, 8, 0 );
		} 
		
		imshow("Image", imageRead );
		
		 char c = (char)waitKey(30); //wait for key press for 30ms

        if (c == 27) // ascii of esc
        {
            cout << "esc key is pressed by user" << endl;
            break;
        }
        else if (c == 'p') paused = !paused;		
	}
	
	return 0;
}

