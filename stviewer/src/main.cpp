//OpenSTIP
#include <openstip.h>

//Internal
#include <SpaceTimeViewer.h>

using namespace monadic::openstip;

int main( int argc, char** argv )
{
    CSpaceTimeViewer stviewer;
    stviewer.init( 640, 480, false );
    
    for(;;)
    {
        stviewer.refresh();
    }
    return 0;
}