/* 
 * File:   SpaceTimeViewer.h
 * Author: kal
 *
 * Created on September 5, 2011, 1:44 AM
 */

#ifndef SPACETIMEVIEWER_H
#define	SPACETIMEVIEWER_H

//SDL
#include <SDL/SDL.h>

//OpenSTIP
#include <openstip.h>

class CSpaceTimeViewer
{
private:
    SDL_Surface* _surfDisplay;
    
public:
    CSpaceTimeViewer();
    ~CSpaceTimeViewer();
    
    bool init( int windowWidth, int windowHeight, bool fullScreen );
    bool refresh();
    
};

#endif	/* SPACETIMEVIEWER_H */

