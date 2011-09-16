#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include <SpaceTimeBuffer.h>

#define STBUFFER CSpaceTimeBuffer

using namespace std;
using namespace cv;
using namespace monadic::openstip;

STBUFFER::CSpaceTimeBuffer( int Width, int Height, int TimeLength )
:_frameWidth(Width),_frameHeight(Height),_timeLength(TimeLength)
{
	for( int i = 0; i < _timeLength; ++i )
	{
		cv::Mat blankImg = cv::Mat::zeros( _frameHeight, _frameWidth, CV_8UC1 );
		CTemporalFrame tFrame( blankImg, 0.0f ); 
		_timeLine.push_front( tFrame );
	}
}

void STBUFFER::pushFrame(cv::Mat Frame, float TimeRef)
{
    //We pop the past (POP BACK)
    _timeLine.pop_back();
    
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
        tempFrm = _timeLine[i].getFrame();    
        cv::Mat resRow = res.row(i);
        cv::Mat srcRow = tempFrm.row(y);
        srcRow.copyTo( resRow );
    }
    cv::Mat tres;

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
		tempFrm = _timeLine[i].getFrame();
        cv::Mat resCol = res.col(i);
        cv::Mat srcCol = tempFrm.col(x);
        srcCol.copyTo( resCol );
    }
    
    cv::Mat tres;
    cv::transpose( res, tres );
    cv::flip( tres, res, 1 );

    return res;
    
}

cv::Mat STBUFFER::getXYSlice(int t)
{

    cv::Mat res;
	res = _timeLine[t].getFrame();
	cv::Mat tres;
    
	cv::flip( res, tres, 0 );
    return tres;
    
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

		int idx = i*(_frameWidth*_frameHeight);
		cv::Mat fltFrame( _frameHeight, _frameWidth, CV_32F );
		
		curFrame.convertTo( fltFrame, CV_32F, 1.0/255.0);

		memcpy( output + i, fltFrame.data, _frameWidth*_frameHeight*sizeof(float) );
    }
}