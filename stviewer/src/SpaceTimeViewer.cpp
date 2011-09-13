//SDL
#include <SDL/SDL.h>

//STL
#include <iostream>

//OpenGL
#include <gl/gl.h>
#include <gl/glu.h>

//Internal
#include <SpaceTimeViewer.h>
#include <rendering.h>

using namespace monadic::openstip;
using namespace std;

#define STV CSpaceTimeViewer

STV::STV()
{
    
}

STV::~STV()
{
    
}

bool STV::init(int windowWidth, int windowHeight, bool fullScreen)
{
    _winWidth = windowWidth;
    _winHeight = windowHeight;
    _flags = SDL_OPENGL | SDL_HWPALETTE | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE | SDL_HWSURFACE;
    if( fullScreen )
        _flags ^= SDL_FULLSCREEN;
    
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
 SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,          8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,           8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,          8);
 
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,          16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,            32);
 
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,        8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,        8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);
 
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
 
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);
    
    if((_surfDisplay = SDL_SetVideoMode(_winWidth, _winHeight, 32, _flags)) == NULL) {
        return false;
    }
    
    
    //this->resizeViewport();
    
    glClearColor((128.0f / 255.0f), 1.0f, 1.0f, 1.0f); //Cyan color
    glViewport(0, 0, 640, 480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 640, 480, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();
    
    return true;
}

void STV::processEvents() {
    
    SDL_Event event;
    int handled = 0;
    
    // Process incoming events
    
    while (SDL_PollEvent(&event)) {
        
        // Send event to AntTweakBar
        //handled = TwEventSDL(&event, SDL_MAJOR_VERSION, SDL_MINOR_VERSION);
        
        // If event has not been handled by AntTweakBar, process it
        if (!handled) {
            switch (event.type) {
                case SDL_QUIT: // Window is closed
                    cout << "quit" << endl;     
                    exit(0);
                    break;

                case SDL_VIDEORESIZE: // Window size has changed
                    // Resize SDL video mode
                    _winWidth = event.resize.w;
                    _winHeight = event.resize.h;
                    if (!SDL_SetVideoMode(_winWidth, _winHeight, 32, _flags))
                        fprintf(stderr, "WARNING: Video mode set failed: %s\n", SDL_GetError());
                    
                    resizeViewport();
                    cout << "resize" << endl;
                    
                    break;
            }
        }
    }
    
}

void STV::resizeViewport() {
    /* Height / width ration */
    GLfloat ratio;

    ratio = ( GLfloat )_winWidth / ( GLfloat )_winHeight;

    /* Setup our viewport. */
    glViewport( 0, 0, ( GLsizei )_winWidth, ( GLsizei )_winHeight );

    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    /* Set our perspective */
    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW );

    /* Reset The View */
    glLoadIdentity( );
}

void STV::processDrawing()
{
        /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* Move Left 1.5 Units And Into The Screen 6.0 */
    glLoadIdentity();
    glTranslatef( -1.5f, 0.0f, -6.0f );

    glBegin( GL_TRIANGLES );            /* Drawing Using Triangles */
      glVertex3f(  0.0f,  1.0f, 0.0f ); /* Top */
      glVertex3f( -1.0f, -1.0f, 0.0f ); /* Bottom Left */
      glVertex3f(  1.0f, -1.0f, 0.0f ); /* Bottom Right */
    glEnd( );                           /* Finished Drawing The Triangle */

    /* Move Right 3 Units */
    glTranslatef( 3.0f, 0.0f, 0.0f );

    glBegin( GL_QUADS );                /* Draw A Quad */
      glVertex3f( -1.0f,  1.0f, 0.0f ); /* Top Left */
      glVertex3f(  1.0f,  1.0f, 0.0f ); /* Top Right */
      glVertex3f(  1.0f, -1.0f, 0.0f ); /* Bottom Right */
      glVertex3f( -1.0f, -1.0f, 0.0f ); /* Bottom Left */
    glEnd( );                           /* Done Drawing The Quad */

    /* Draw it to the screen */
    SDL_GL_SwapBuffers( );
    cout << "draw.." << endl;
}

bool STV::refresh()
{
    processDrawing();
    processEvents();
}

bool STV::updateData(monadic::openstip::CSpaceTimeBuffer& stbuffer)
{
    return true;
}

#undef STV
