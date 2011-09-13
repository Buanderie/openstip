#include <opencv2/core/core.hpp>
#include <SpaceTimeBuffer.h>

#define STBUFFER CSpaceTimeBuffer

using namespace std;
using namespace cv;
using namespace monadic::openstip;

STBUFFER::CSpaceTimeBuffer( int Width, int Height, int TimeLength )
:_frameWidth(Width),_frameHeight(Height),_timeLength(TimeLength)
{

}

void STBUFFER::pushFrame(cv::Mat Frame, float TimeRef)
{
    if( _timeLine.size() >= _timeLength )
    {
        //We pop the past (POP BACK)
        _timeLine.pop_back();
    }
    
    //In both cases, we push the NEW FRAME to the FRONT (Most recent)
    CTemporalFrame tFrame( Frame, TimeRef );
    _timeLine.push_front( tFrame );
}

cv::Mat STBUFFER::getXTSlice(int y)
{
    int w = _frameWidth;
    int h = _timeLength;
    
    cv::Mat res( h, w, CV_8UC1 );
    
    for( int i = 0; i < h; ++i )
    {
        cv::Mat tempFrm;
        if( i < _timeLine.size() )
            tempFrm = _timeLine[i].getFrame();
        else
            tempFrm = cv::Mat::zeros( _frameHeight, _frameWidth, CV_8UC1 );
            
        cv::Mat resRow = res.row(i);
        cv::Mat srcRow = tempFrm.row(y);
        srcRow.copyTo( resRow );
        
    }
    
    return res;
}

cv::Mat STBUFFER::getYTSlice(int x)
{
    int w = _frameHeight;
    int h = _timeLength;
    
    cv::Mat res( w, h, CV_8UC1 );
    
    for( int i = 0; i < h; ++i )
    {
        cv::Mat tempFrm;
        if( i < _timeLine.size() )
            tempFrm = _timeLine[i].getFrame();
        else
            tempFrm = cv::Mat::zeros( _frameHeight, _frameWidth, CV_8UC1 );
            
        cv::Mat resCol = res.col(i);
        cv::Mat srcCol = tempFrm.col(x);
        srcCol.copyTo( resCol );
    }
    
    cv::Mat tres;
    cv::transpose( res, tres );
    
    return tres;
    
}

cv::Mat STBUFFER::getXYSlice(int t)
{

    cv::Mat res;
    
    if( t < _timeLine.size() )
        res = _timeLine[t].getFrame();
    else
        res = cv::Mat::zeros( _frameHeight, _frameWidth, CV_8UC1 );

    return res;
    
}

int STBUFFER::getRawDataLength()
{
    return _frameWidth * _frameHeight * _timeLength;
}

void STBUFFER::getRawData(float* output)
{
    //For each XY-Slice
    for( int i = 0; i < _timeLength; ++i )
    {
        //Extract new frame from buffer
        cv::Mat curFrame = this->getXYSlice( i );
        
        //For each row in frame
        for( int j = 0; j < _frameHeight; ++j )
        {
            //For each pixel in row
            for( int k = 0; k < _frameWidth; ++k )
            {
                int idx = i*(_frameWidth*_frameHeight) + j*(_frameWidth) + k;
                output[ idx ] = (((float)(curFrame.at<unsigned char>(j,i)))/255.0f);
            }
        }
    }
}