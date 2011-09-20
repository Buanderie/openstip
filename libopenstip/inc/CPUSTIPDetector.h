#ifndef __CPUSTIPDETECTOR_H__
#define __CPUSTIPDETECTOR_H__

#include "ISTIPDetector.h"

namespace monadic{
namespace openstip{
	
	class CCPUSTIPDetector : public ISTIPDetector
	{
		public:
		CCPUSTIPDetector();
		~CCPUSTIPDetector();
		virtual void computeIntegralVolume( monadic::openstip::CSpaceTimeBuffer& stbuffer );
	};
}
}
#endif