#include "gameentity.h" // class's header file
    using namespace game;

#include <allegro.h>
#include "debug.h"

// class constructor
GameEntity::GameEntity()
{
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    box.offsetBottom = 0;
    box.offsetLeft = 0;
    box.offsetRight = 0;
    box.offsetTop = 0;
}

// class destructor
GameEntity::~GameEntity()
{
	// nothing to do, yet
}

bool GameEntity::collides( GameEntity* pOpponent )
{
    Assert( width > 0, "width is not set!" );
    Assert( height > 0, "height is not set!" );
    if ( getLeft() > pOpponent->getRight() )
        return false;
    if ( getRight() < pOpponent->getLeft() )
        return false;
    if ( getTop() > pOpponent->getBottom() )
        return false;
    if ( getBottom() < pOpponent->getTop() )
        return false;
    return true;
}
