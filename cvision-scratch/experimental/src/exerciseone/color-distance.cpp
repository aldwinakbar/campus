#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

typedef struct {
    unsigned char r, g, b;
 } RGB;
 
 double ColourDistance(RGB e1, RGB e2)
 {
   long rmean = ( (long)e1.r + (long)e2.r ) / 2;
   long r = (long)e1.r - (long)e2.r;
   long g = (long)e1.g - (long)e2.g;
   long b = (long)e1.b - (long)e2.b;
   return sqrt((((512+rmean)*r*r)>>8) + 4*g*g + (((767-rmean)*b*b)>>8));
 }

 int main(){
    RGB a,b;
    a.r = 208;
    a.g = 39;
    a.b = 0;
    b.r = 255;
    b.g = 70;
    b.b = 95;
    cout << ColourDistance(a,b);
    return 0;
 }