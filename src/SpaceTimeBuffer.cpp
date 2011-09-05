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