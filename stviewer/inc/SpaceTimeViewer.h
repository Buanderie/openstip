/* 
 * File:   SpaceTimeViewer.h
 * Author: kal
 *
 * Created on September 5, 2011, 1:44 AM
 */

#ifndef SPACETIMEVIEWER_H
#define	SPACETIMEVIEWER_H

//OpenSTIP
#include <openstip.h>

//GLFW
#include <GL/GLFW.h>

//AntTeakBar
#include <AntTweakBar.h>

//Internal
#include <glCamera.h>

class CSpaceTimeViewer
{
private:
    int                 _winWidth;
    int                 _winHeight;
	int					_dataWidth;
	int					_dataHeight;
	int					_dataLength;

	int					_xtSlicePos;
	int					_ytSlicePos;
	int					_xySlicePos;
	float				_timeScale;

    GLFWvidmode			_mode;
	glCamera*			cam;
	TwBar*				_bar;
	float				_frameTime;

	GLuint _xtTexture;
	GLuint _ytTexture;
	GLuint _xyTexture;

    void processEvents();
    void processDrawing();
	
	void loadSlices( monadic::openstip::CSpaceTimeBuffer& stbuffer );
	void unloadSlices();
	void drawXTSlice();
	void drawYTSlice();
	void drawXYSlice();

    void resizeViewport();
    
public:
    CSpaceTimeViewer();
    ~CSpaceTimeViewer();
    
    bool init(int windowWidth, int windowHeight, bool fullScreen, int dataWidth, int dataHeight, int dataLength );
    bool updateData( monadic::openstip::CSpaceTimeBuffer& stbuffer );
    bool refresh();
    
};

#endif	/* SPACETIMEVIEWER_H */

