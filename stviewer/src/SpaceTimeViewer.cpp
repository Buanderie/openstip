//STL
#include <iostream>

//GLFW
#include <GL/GLFW.h>

//Internal
#include <SpaceTimeViewer.h>
#include <rendering.h>

using namespace monadic::openstip;
using namespace std;

#define STV CSpaceTimeViewer

void GLFWCALL OnMousePos(int mouseX, int mouseY)  // your callback function called by GLFW when mouse has moved
{
    if( !TwEventMousePosGLFW(mouseX, mouseY) )  // send event to AntTweakBar
    { // event has not been handled by AntTweakBar
      // your code here to handle the event
      // ...
    }
}

void GLFWCALL OnMouseButton( int button, int action )
{
	if( !TwEventMouseButtonGLFW( button, action ) )
	{

	}
}


void GLFWCALL OnKey( int key, int action )
{
	if( !TwEventKeyGLFW( key, action ))
	{

	}
}

void GLFWCALL OnMouseWheel( int pos )
{
	if( !TwEventMouseWheelGLFW( pos ))
	{

	}
}

void GLFWCALL OnChar( int character, int action )
{
	if( !TwEventCharGLFW( character, action ))
	{

	}
}

STV::STV()
{
    
}

STV::~STV()
{
    
}

bool STV::init(int windowWidth, int windowHeight, bool fullScreen, int dataWidth, int dataHeight, int dataLength )
{
    _winWidth = windowWidth;
    _winHeight = windowHeight;
	_dataWidth = dataWidth;
	_dataHeight = dataHeight;
	_dataLength = dataLength;

    _frameTime = 0.0f;


	_xtSlicePos = dataHeight/2;
	_ytSlicePos = dataWidth /2;
	_xySlicePos = dataLength/2;
	_timeScale  = 5.0f;

	// Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

	//Open window	 
	glfwOpenWindow(_winWidth, _winHeight, _mode.RedBits, _mode.GreenBits, _mode.BlueBits, 
                   0, 30, 0, ((!fullScreen)?(GLFW_WINDOW):(GLFW_FULLSCREEN)));

	glfwEnable(GLFW_MOUSE_CURSOR);
    glfwEnable(GLFW_KEY_REPEAT);

	//OpenGL and Camera settings
	//Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

    //Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.f, 1.f, 1.f, 1000.f);
	//
	cam = new glCamera();
	cam->m_Position.x=0;
	cam->m_Position.y = 10;
	cam->m_Position.z = -10;
	cam->m_MaxForwardVelocity = 5.0f;
	cam->m_MaxPitchRate = 5.0f;
	cam->m_MaxHeadingRate = 5.0f;
	cam->m_PitchDegrees = 0.0f;
	cam->m_HeadingDegrees = 0.0f;
	//

	//AntTweakBar
	TwInit(TW_OPENGL, NULL);
	TwWindowSize( _winWidth, _winHeight );
	_bar = TwNewBar("TweakBar");
	TwAddVarRW(_bar, "XT Slice Position", TW_TYPE_INT32, &_xtSlicePos, " min=0 max=119");
	TwAddVarRW(_bar, "YT Slice Position", TW_TYPE_INT32, &_ytSlicePos, " min=0 max=159");
	TwAddVarRW(_bar, "XY Slice Position", TW_TYPE_INT32, &_xySlicePos, " min=0 max=39");
	TwAddVarRW(_bar, "Time Scale", TW_TYPE_FLOAT, &_timeScale, " min=1 max=10 step=0.1 ");

	glfwSetMousePosCallback(OnMousePos);
	glfwSetMouseButtonCallback(OnMouseButton);
	glfwSetKeyCallback(OnKey);
	glfwSetCharCallback(OnChar);
	glfwSetMouseWheelCallback(OnMouseWheel);
}

void STV::processEvents() {

		//Move to the callback ?
		//Check for keyboard input
		if( glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS )
			cam->m_ForwardVelocity = 10.0f;
		if( glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS )
			cam->m_ForwardVelocity = -10.0f;
		if( glfwGetKey( GLFW_KEY_DOWN ) == GLFW_RELEASE && glfwGetKey( GLFW_KEY_UP ) == GLFW_RELEASE )
			cam->m_ForwardVelocity = 0;
		//

		//Check for mouse input
		if( glfwGetMouseButton( GLFW_MOUSE_BUTTON_RIGHT ) == GLFW_PRESS )
		{
			int xpos, ypos;
			glfwGetMousePos( &xpos, &ypos );
			cam->ChangeHeading(0.2f*(float)(xpos-((int)_winWidth/2)));
			cam->ChangePitch(0.2f*(float)(ypos-((int)_winHeight/2)));
			glfwSetMousePos( _winWidth/2, _winHeight/2 );
		}
		//
}

void STV::resizeViewport() {

}

void STV::drawXTSlice()
{
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, _xtTexture);
	glBegin(GL_QUADS);
	glColor4f(1.0f,0.5f,1.0f,0.1f);
	glTexCoord2f(0.0f, 0.0f); glVertex3d(0, _dataHeight-_xtSlicePos, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3d(_dataWidth, _dataHeight-_xtSlicePos, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3d(_dataWidth, _dataHeight-_xtSlicePos, _dataLength);
	glTexCoord2f(0.0f, 1.0f); glVertex3d(0, _dataHeight-_xtSlicePos, _dataLength);
	glEnd();

	glDisable( GL_TEXTURE_2D );
}

void STV::drawYTSlice()
{
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, _ytTexture);
	glBegin(GL_QUADS);
	glColor4f(1.0f,1.0f,1.0f,100.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3d( _ytSlicePos,0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3d( _ytSlicePos,_dataHeight, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3d( _ytSlicePos,_dataHeight, _dataLength);
	glTexCoord2f(0.0f, 1.0f); glVertex3d( _ytSlicePos,0, _dataLength);
	glEnd();
	glDisable( GL_TEXTURE_2D );
}

void STV::drawXYSlice()
{
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, _xyTexture);
	glBegin(GL_QUADS);
	glColor4f(1.0f,1.0f,1.0f,100.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3d(0, 0,						_xySlicePos);
	glTexCoord2f(1.0f, 0.0f); glVertex3d( _dataWidth, 0,			_xySlicePos);
	glTexCoord2f(1.0f, 1.0f); glVertex3d( _dataWidth, _dataHeight,	_xySlicePos);
	glTexCoord2f(0.0f, 1.0f); glVertex3d( 0, _dataHeight,			_xySlicePos);
	glEnd();

	glDisable( GL_TEXTURE_2D );
}

void STV::processDrawing()
{
	 // Clear frame buffer using bgColor
        glClearColor(0.5,0.5,0.5, 1);
        glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );

		//Do stuff
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		cam->SetPrespective();
		//

		//drawFloorGrid();

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glPushMatrix();
		glScalef( 1.0f, 1.0f, _timeScale );
		drawXTSlice();
		drawYTSlice();
		drawXYSlice();
		glPopMatrix();

		TwDraw();  // draw the tweak bar(s)

		// Present frame buffer
        glfwSwapBuffers();

		unloadSlices();
}

bool STV::refresh()
{
	float startTime = glfwGetTime();
    processDrawing();
    processEvents();
	_frameTime = glfwGetTime() - startTime;
	//cout << "FPS=" << 1.0f/_frameTime << endl;
	return true;
}

void STV::loadSlices( CSpaceTimeBuffer& stbuffer )
{
	cv::Mat xtslice = stbuffer.getXTSlice( _xtSlicePos );
	cv::Mat ytslice = stbuffer.getYTSlice( _ytSlicePos );
	cv::Mat xyslice = stbuffer.getXYSlice( _xySlicePos );
	int height, width;

	//XT
	width = xtslice.cols;// = stbuffer.getFrameWidth();
	height = xtslice.rows;// = stbuffer.getFrameHeight();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures( 1, &_xtTexture );
    glBindTexture( GL_TEXTURE_2D, _xtTexture );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_LINEAR);
    glTexImage2D(	GL_TEXTURE_2D,
					0,
					GL_RGB,
					width,
					height,
                    0,
					GL_LUMINANCE,
					GL_UNSIGNED_BYTE,
					xtslice.data );
	//

	//YT
	width = ytslice.cols;// = stbuffer.getFrameWidth();
	height = ytslice.rows;// = stbuffer.getFrameHeight();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures( 1, &_ytTexture );
    glBindTexture( GL_TEXTURE_2D, _ytTexture );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_LINEAR);
    glTexImage2D(	GL_TEXTURE_2D,
					0,
					GL_RGB,
					width,
					height,
                    0,
					GL_LUMINANCE,
					GL_UNSIGNED_BYTE,
					ytslice.data );
	//

	//XY
	width = xyslice.cols;// = stbuffer.getFrameWidth();
	height = xyslice.rows;// = stbuffer.getFrameHeight();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures( 1, &_xyTexture );
    glBindTexture( GL_TEXTURE_2D, _xyTexture );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_LINEAR);
    glTexImage2D(	GL_TEXTURE_2D,
					0,
					GL_RGB,
					width,
					height,
                    0,
					GL_LUMINANCE,
					GL_UNSIGNED_BYTE,
					xyslice.data );
	//
}

void STV::unloadSlices()
{
	glDeleteTextures( 1, &_xtTexture );
	glDeleteTextures( 1, &_ytTexture );
	glDeleteTextures( 1, &_xyTexture );
}

bool STV::updateData(monadic::openstip::CSpaceTimeBuffer& stbuffer)
{
	loadSlices( stbuffer );
    return true;
}

#undef STV
