#include <opencv2/core/core.hpp>

#include <TemporalFrame.h>

using namespace monadic::openstip;

#define TFRAME CTemporalFrame

TFRAME::TFRAME( cv::Mat Frame, float TimeRef )
:_timeRef(TimeRef), _frame(Frame)
{

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