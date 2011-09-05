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
#include <opencv2/video/background_segm.hpp>

//SDL
#include <SDL/SDL.h>

//OpenSTIP
#include <SpaceTimeBuffer.h>

#define WIDTH 800
#define HEIGHT 600

using namespace std;
using namespace cv;
using namespace monadic::openstip;

int main(int argc, char** argv) {

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat initialFrame;
    cap >> initialFrame;
    int frameWidth =    initialFrame.cols;
    int frameHeight =   initialFrame.rows;
    
    BackgroundSubtractorMOG bg_model;
    
    CSpaceTimeBuffer stbuff(frameWidth, frameHeight, 40);
    
    Mat edges;
    
    namedWindow("edges",1);
    cv::Mat fgmask;
    int cpt = 0;
    
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, CV_BGR2GRAY);
        
        bg_model(edges, fgmask, -1);
        
        stbuff.pushFrame( edges, (cpt>100)?-1:0 );

        imshow("edges", fgmask);
        if(waitKey(30) >= 0) break;
        cpt++;
    }
    
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
    
}

