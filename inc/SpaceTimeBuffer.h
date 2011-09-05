/* 
 * File:   SpaceTimeBuffer.h
 * Author: kal
 *
 * Created on September 5, 2011, 1:01 AM
 */

#ifndef SPACETIMEBUFFER_H
#define	SPACETIMEBUFFER_H

#include <deque>
#include <TemporalFrame.h>

namespace monadic{
    namespace openstip{
        
        class CSpaceTimeBuffer
        {
        private:
            std::deque< CTemporalFrame >        _timeLine;
            int                                 _timeLength;
            int                                 _frameWidth;
            int                                 _frameHeight;
            
        public:
            CSpaceTimeBuffer( int Width, int Height, int TimeLength );
            
            void pushFrame( cv::Mat Frame, float TimeRef );
            
        };
    }
}

#endif	/* SPACETIMEBUFFER_H */
