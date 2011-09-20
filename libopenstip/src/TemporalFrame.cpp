#include <opencv2/core/core.hpp>

#include <TemporalFrame.h>

using namespace monadic::openstip;

#define TFRAME CTemporalFrame

TFRAME::TFRAME( cv::Mat Frame, float TimeRef )
:_timeRef(TimeRef)
{
	//_fltFrame.create( Frame.rows, Frame.cols, CV_32F );
    Frame.copyTo( _frame );
	_frame.convertTo( _fltFrame, CV_32F, 1.0f/255.0f);
}

TFRAME::~CTemporalFrame()
{
    
}

float TFRAME::getTimeReference()
{
    return _timeRef;
}

cv::Mat& TFRAME::getFrame()
{
    return _frame;
}

cv::Mat& TFRAME::getFloatFrame()
{
	return _fltFrame;
}