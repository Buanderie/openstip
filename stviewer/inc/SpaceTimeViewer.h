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
    SDL_Surface*        _surfDisplay;
    int                 _winWidth;
    int                 _winHeight;
    int                 _flags;
    
    void processEvents();
    void processDrawing();
    void resizeViewport();
    
public:
    CSpaceTimeViewer();
    ~CSpaceTimeViewer();
    
    bool init( int windowWidth, int windowHeight, bool fullScreen );    
    bool updateData( monadic::openstip::CSpaceTimeBuffer& stbuffer );
    bool refresh();
    
};

#endif	/* SPACETIMEVIEWER_H */

