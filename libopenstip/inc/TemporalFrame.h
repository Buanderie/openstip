#ifndef __TEMPORALFRAME_H__
#define __TEMPORALFRAME_H__

#include <opencv2/core/core.hpp>

namespace monadic
{
    namespace openstip
    {
        class CTemporalFrame
        {
        private:
            float       _timeRef; //Time reference in msec
            cv::Mat     _frame;
			cv::Mat		_fltFrame;
            
        public:
            CTemporalFrame( cv::Mat Frame, float TimeRef );
            ~CTemporalFrame();
            
            cv::Mat&    getFrame();
			cv::Mat&	getFloatFrame();
            float       getTimeReference();
        };
    }
}


#endif
