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
		Mat src = imageRead;
		
		
		 Mat dst, cdst;
    Canny(src, dst, 50, 200, 3); 
    cvtColor(dst, cdst, CV_GRAY2BGR); 
 
    vector<Vec2f> lines;
    // detect lines
    HoughLines(dst, lines, 1, CV_PI/180, 150, 0, 0 );
 
    // draw lines
    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
    }
 
    imshow("source", src);
    imshow("detected lines", cdst);
    
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

