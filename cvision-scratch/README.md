# exercise-AS0308

# Installation

```
mkdir build
cd build
cmake ..
make
```

# Main Image Processing Operation

## Find Region
The **find_region()** implementation in this API uses the basic recursive flood fill algorithm. A pixel is considered in the same region if comparison using **compare_v3b()** resulted in a number below the threshold value (e.g. 100 - 200 is considered having the same color in human perception). Comparison of color used in the **compare_v3b()** is a derivative of weighted Euclidean distance, other more complex formula that can be used is CIEDE2000. The pixel is then push to a **vector<pair(Point,Vec3b)>** where the [x,y] coordinate and the BGR value is stored. The disadvatage of using the recursive flood fill algorithm that it uses a lot of stack memory which can cause segmentation fault when handling large data. Another alternative to this is using non-recursive approach ( e.g. Forest Fire algorithm) and using multi-threaded process to further improve the process speed.

## Find Perimeter
The **find_perimeter()** is implemented by iterating to every coordinate from **find_region()** and check whether the surrounding pixel is a non-region or outside the area of the original image(e.g. larger or smaller than the image size), if its true then it is added to a new **vector<pair(Point,Vec3b)>** variable. This can be improve by using multi-threaded processing where each row iteration is done in a differet thread.

## Find Smooth Perimeter
The **find_smooth_perimeter()** is implemented using spatial filter algorithm which uses basic **neighborhood_mean** operation where the kernel is a 2D Gaussian distribution. The gaussian distribution can be tweaked by changing the size of the kernel and gaussian sigma value, through **produce_2d_gaussian_kernel()** function. Other kernel can be used (e.g. interpolation and simple low pass filter). The consideration of using gaussian is because calculation of the gaussian distribution is not heavy, changing the level of smoothness can be done by varying the sigma value, and the result is better than the simple low pass filter.

# Files

This API consist of 3 files as described below. A more detailed explanation will be given in each sub-section.

* ImageProcessing.h - **Main Algorithm for Image Processing**
* ImageAIO - **Class to handle and use the algorithm in ImageProcessing.h**
  * ImageAIO.h - **Header file for ImageAIO class.**
  * ImageAIO.cpp - **Implementation file for ImageAIO class.**
* main.cpp - **Entry point and command line interface implementation**

# ImageProcessing.h

ImageProcessing.h consist of all the main image processing algorithm, which are find_region(), find_perimeter(), display_image(), display_pixel(), and save_pixel(), implemented using namespace of arcv.

### ImageProcessing Function
* colour_distance
  * This function is used to calculate the difference between two RGB value in **Vec3b** type
* compare_v3b
  * This function works as an abstraction layer for the colour distance calculation. Further changes in the calculation of the colour distance and it's threshold can be set here
* minmax_coordinate
  * This function determine the minimum and maximum of the [x,y] coordinate in a vector of **cv::Point**. Used to Normalize the **find_region()** result and create the smallest possible **cv::Mat** to encapsulate the **find_region()** result.
* normalize_region
  * This function normalize the coordinate result of **find_region()**. Example : [1,2] and [2,3] becomes [0,0] and [1,1] 
* create_image_from_pixel 
  * This function will return a **cv::Mat** object from **find_region()** or **find_perimeter()**
* display_image 
  * This function display image from imread. Used for displaying orginal/un-modified image.
* display_pixel 
  * This function display image from any **cv::Mat** object
* save_pixel 
  * This function save and **cv::Mat** object into a file using **cv::imwrite()**
* find_region_util 
  * This function is the main find_region algorithm, derived from a recursion-type floodFill algorithm. 
* find_region 
  * This function serves as the entry point of the recursive **find_region()** algorithm
* find_perimeter
  * This function calculate the perimeter of a given **find_region()** data.
* unnormalize_region
  * This will revert normalized coordinate to it's original data.
* gaussian
  * This is a helper function to calculate gaussian distribution
* produce_2d_gaussian_kernel
  * This creates a 2D gaussian normallized distributin, which later can be used to do smoothing
* neighborhood_mean
  * This function will do **neighborhood mean** on every pixel of an **BGR cv::Mat** image and a n*n kernel
* region_smoothing
  * This function will do **neighborhood mean** on every pixel in a **find_region()** data points and a n*n kernel
* find_smooth_perimeter
  * This function calculate the smooth perimeter of a given **find_region()** data.

# ImageAIO

ImageAIO is the class that utilize the algorithm in ImageProcessing.h and capable of holding **cv::Mat** object for original, **find_region()** and **find_perimeter()** images. It also holds the vector of **cv::Point** from **find_region()** and **find_perimeter()**.

## Constructor

ImageAIO consist of 5 overloaded constructor.
* ImageAIO()
  * This constructor is used for serial operation such as in a CommandLine Interface. No object are initialized.
* ImageAIO(cv::Mat &input)
  * Object **input** will be assigned to the local **cv::Mat**. This will ensure that there is an image for **find_region()** and **find_perimeter()** function.
* ImageAIO(cv::Mat &input, int x, int y)
  * Other than assigning the **input** to the local **cv::Mat** this constructor will also calculate the **find_region()** and **find_perimeter()**.
* ImageAIO(const char* location)
  * local **cv::Mat** that holds the original image will be filled using **cv::imread()** using the **location** parameter.
* ImageAIO(const char* location, int x, int y)
  * This constructor is the same as **ImageAIO(cv::Mat &input, int x, int y)** only difference is that it reads the image data using **cv::imread()**
  
## Methods

ImageAIO have 12 methods with 9 non-overloaded methods.
 
* set_original (const char* location)
  * Using **cv::imread()** local **cv::Mat** will be assigned according to the file in the **location**
* calculate_all(int x, int y)
  * This will calculate **find_region()** and **find_perimeter()** using default threshold (150) and default **find_region_type**
* calculate_all(int x, int y, int type, int threshold)
  * This will calculate **find_region()** and **find_perimeter()** using the given **threshold** and **type** (0 is for 4 connected point and 1 is for 8 connecteed point)
* display_original()
  * This will display the original image from the local **cv::Mat** object
* display_region()
  * This will display the region image from  the local **cv::Mat** object
* display_perimeter()
  * This will display the perimeter image from  the local **cv::Mat** object
* save_region_image(const char* location)
  * This will save the region image from  the local **cv::Mat** object to the drive
* save_perimeter_image(const char* location)
  * This will display the perimeter image from the local **cv::Mat** object to the drive
* calculate_region (int x, int y, int type, int threshold)
  * This will calculate **find_region()** and create the image using given find_region_type and colour threhold
* calculate_region (int x, int y)
  * This will calculate **find_region()** and create the image using **default** find_region_type and colour threhold
* calculate_perimeter (int type)
  * This will calculate **find_perimeter()** and create the image using given find_region_type and colour threhold
* calculate_perimeter ()
  * This will calculate **find_perimeter()** and create the image using **default** find_region_type and colour threhold
* display_smoothed_perimeter(int kernel_radius, int gaussian_sigma)
  * This will display the smoothed perimeter image by using **find_smoothed_perimeter()** method
* display_smoothed_region(int kernel_radius, int gaussian_sigma)
  * This will display the smoothed region image by using **region_smoothing()** function
* display_smoothed_image(cv::Mat &src, int kernel_radius, int gaussian_sigma)
  * This will display the smoothed image by using **neighborhood_mean()** function
* save_smoothed_image(const char* location, int kernel_radius, int gaussian_sigma)
  * This will save the smoothed image by using **find_smoothed_perimeter()** method
* save_smoothed_image(const char* location, cv::Mat &src, int kernel_radius, int gaussian_sigma)
  * This will save the smoothed image by using **neighborhood_mean()** function

* find_smoothed_perimeter(int kernel_radius, int gaussian_sigma)
  * This will call the **find_smooth_perimeter()** from the ImageProcssing.h

# Future Works
* Implement faster and more memory-friendly **find_region()** (e.g without recursive method)
* Implement faster **find_perimeter()** (e.g. using multi-threaded process)
* Implement better color-differece calculator (e.g. using current CIEDE2000 formula)
* Implement better smoothing algorithm for border pixel.

# References

* https://www.compuphase.com/cmetric.htm
  * Implementation of Colour Differences Algorithm
* http://www.geeksforgeeks.org/flood-fill-algorithm-implement-fill-paint/
  * Basic FloodFill Algorithm
* http://www.programming-techniques.com/2013/01/low-pass-filters-blurring-in-image.html
  * Basic smoothing algorithm
* https://stackoverflow.com/questions/8204645/implementing-gaussian-blur-how-to-calculate-convolution-matrix-kernel
  * Algorithm to calculate 2D Gaussian kernel
