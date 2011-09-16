//OpenSTIP
#include <openstip.h>

//OpenCV 2.X
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//Internal
#include <SpaceTimeViewer.h>

#define WIDTH 320
#define HEIGHT 240
#define LENGTH 50

using namespace cv;
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
    
    stviewer.init( 640, 480, false, WIDTH, HEIGHT, LENGTH );
    
    float* rawValues = new float[ WIDTH * HEIGHT * LENGTH ];
    
    int cpt = 0;
    for(;;)
    {
        cap >> rawFrame; // get a new frame from camera
        cv::resize( rawFrame, rszFrame, cv::Size(WIDTH,HEIGHT));
        cvtColor(rszFrame, grayFrame, CV_BGR2GRAY);
        stbuffer.pushFrame( grayFrame, (float)cpt );
        
		stbuffer.getRawData( rawValues );

        stviewer.updateData( stbuffer );

        stviewer.refresh();
        
        cpt++;
    }
    return 0;
}