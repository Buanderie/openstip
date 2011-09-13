//SDL
#include <SDL/SDL.h>

//OpenGL
#include <gl/gl.h>

//Internal
#include <SpaceTimeViewer.h>

using namespace monadic::openstip;

#define STV CSpaceTimeViewer

STV::STV()
{
    
}

STV::~STV()
{
    
}

bool STV::init(int windowWidth, int windowHeight, bool fullScreen)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
 
    if((_surfDisplay = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }
 
    return true;
}

bool STV::refresh()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    SDL_GL_SwapBuffers();
}

#undef STV
