/* 
 * File:   main.cpp
 * Author: kal
 *
 * Created on September 5, 2011, 12:22 AM
 */
//STD & STL
#include <cstdlib>

//OpenCV 2.X
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//SDL
#include <SDL/SDL.h>

//OpenSTIP
#include <openstip.h>

#define WIDTH 320
#define HEIGHT 240
#define LENGTH 500

using namespace std;
using namespace cv;
using namespace monadic::openstip;

int main(int argc, char** argv) {

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    CSpaceTimeBuffer stbuff( WIDTH, HEIGHT, LENGTH );
    Mat gray;
    int cpt = 0;
    
    for(;;)
    {
        Mat frame, frameRsz;
        Mat xtslice;
        Mat ytslice;
        Mat xyslice;
        
        cap >> frame; // get a new frame from camera
        cv::resize( frame, frameRsz, cv::Size(WIDTH,HEIGHT));
        
        cvtColor(frameRsz, gray, CV_BGR2GRAY);
        
        stbuff.pushFrame( gray, (float)cpt );
        xtslice = stbuff.getXTSlice( HEIGHT/2 );
        ytslice = stbuff.getYTSlice( WIDTH/2 );
        xyslice = stbuff.getXYSlice( LENGTH/2 );
        
        imshow("XT", xtslice);
        imshow("YT", ytslice);
        imshow("XY", xyslice);
        
        if(waitKey(5) >= 0) break;
        cpt++;
        
    }
    
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
    
}

