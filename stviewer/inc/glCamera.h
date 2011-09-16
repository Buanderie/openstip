// glCamera.h: interface for the glCamera class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __GLCAMERA_H__
#define __GLCAMERA_H__

#include <gl/GLFW.h>

#include "glQuaternion.h"
#include "glPoint.h"
#include "glVector.h"

class glCamera  
{
public:
	GLfloat m_MaxPitchRate;
	GLfloat m_MaxHeadingRate;
	GLfloat m_HeadingDegrees;
	GLfloat m_PitchDegrees;
	GLfloat m_MaxForwardVelocity;
	GLfloat m_ForwardVelocity;
	glQuaternion m_qHeading;
	glQuaternion m_qPitch;
	glPoint m_Position;
	glVector m_DirectionVector;

	void ChangeVelocity(GLfloat vel);
	void ChangeHeading(GLfloat degrees);
	void ChangePitch(GLfloat degrees);
	void SetPrespective(void);
	glCamera();
	virtual ~glCamera();

};

#endif