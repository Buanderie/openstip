// glVector.cpp: implementation of the glVector class.
//
//////////////////////////////////////////////////////////////////////

#include "glVector.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

glVector::glVector()
{
	i = j = k = 0.0f;
}

glVector::~glVector()
{

}

void glVector::operator *=(float scalar)
{
	i *= scalar;
	j *= scalar;
	k *= scalar;
}
