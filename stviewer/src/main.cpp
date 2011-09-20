//OpenSTIP
#include <openstip.h>

//STL
#include <iostream>

//OpenCV 2.X
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//Boost
#include <boost/timer.hpp>

//Internal
#include <SpaceTimeViewer.h>

#define WIDTH 160
#define HEIGHT 120
#define LENGTH 100

using namespace cv;
using namespace std;
using namespace monadic::openstip;

int main( int argc, char** argv )
{
    //Initialize camera input
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    
    cv::Mat rawFrame;
    cv::Mat rszFrame;
    cv::Mat grayFrame;
    
    CSpaceTimeViewer stviewer;
    CSpaceTimeBuffer stbuffer( WIDTH, HEIGHT, LENGTH );
    CCPUSTIPDetector* detector = new CCPUSTIPDetector();



    stviewer.init( 640, 480, false, WIDTH, HEIGHT, LENGTH );
    
    float* rawValues = new float[ WIDTH * HEIGHT * LENGTH ];
    
    int cpt = 0;
    for(;;)
    {
		boost::timer t;
        cap >> rawFrame; // get a new frame from camera
        cv::resize( rawFrame, rszFrame, cv::Size(WIDTH,HEIGHT));
        cvtColor(rszFrame, grayFrame, CV_BGR2GRAY);
        stbuffer.pushFrame( grayFrame, (float)cpt );
        stviewer.updateData( stbuffer );
		detector->computeIntegralVolume( stbuffer );
        stviewer.refresh();
        cpt++;
		double framet = t.elapsed();
		cout << "FPS=" << 1.0/framet << endl;
    }
    return 0;
}