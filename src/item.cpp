#include "item.h" // class's header file
    using namespace game;
#include <OpenLayer.hpp>
    using namespace ol;
#include <allegro.h>
#include "debug.h"
#include "hero.h"

#include "resourcemanager.h"

    
// class constructor
Item::Item()
{
	bitmap = NULL;
	type = -1;
}

// class destructor
Item::~Item()
{
	// nothing to do, yet
}

/// creates a clone of this item
GameEntity* Item::clone()
{
    Item* tmp = new Item( *this );
    tmp->isClone = true;
    return tmp;    
}    

/// loads the graphic for this item
void Item::loadGraphics( const char* pFile, ResourceManager* pResource )
{
    Assert( pFile, "given parameter is NULL!" );
    Assert( ! bitmap, "graphic is already loaded!" );
    
    bitmap = new Bitmap( pFile );
    Guarantee( bitmap->IsValid(), "ol-bitmap could not be created!" );

    // set the size of this item
    width = bitmap->Width();
    height = bitmap->Height();

    pResource->manage( bitmap );
}

void Item::draw( float pOffsX, float pOffsY )
{
    Assert( bitmap, "graphic is not loaded!" );
    bitmap->Blit( int(x - pOffsX), int(y - pOffsY) );
}

/// updates the object
bool Item::update( float pDelta )
{
    Assert( type >= 0, "invalid item type!" );
    bool retValue = true;

    Hero* lHero = world->getHero();
    if ( collides( lHero ) )
    {
        retValue = false;
        switch ( type )
        {
            case HEART:
                if ( lHero->getAttribute( Character::LIFE ) == lHero->getAttribute( Character::MAX_LIFE ) )
                    retValue = true;
                else                
                    lHero->incAttribute( Character::LIFE, 10 );
                break;
            case EXIT:
                world->levelCompleted();
                break;
            case BOMB:
                lHero->incAttribute( Character::BOMBS, 1 );
                break;
            case MANA:
                if ( lHero->getAttribute( Character::MANA ) == lHero->getAttribute( Character::MAX_MANA ) )
                    retValue = true;
                else                
                    lHero->incAttribute( Character::MANA, 10 );
                break;

        }
    }
    return retValue;
    
}
