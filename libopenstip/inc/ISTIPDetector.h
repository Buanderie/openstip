#ifndef __ISTIPDETECTOR_H__
#define __ISTIPDETECTOR_H__

#include "SpaceTimeBuffer.h"

namespace monadic{
namespace openstip{

class ISTIPDetector
{
public:
	virtual void computeIntegralVolume( monadic::openstip::CSpaceTimeBuffer& stbuffer ) = 0;
};

}
}
#endif