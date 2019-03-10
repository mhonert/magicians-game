#include "tile.h" // class's header file
    using namespace game;
#include "debug.h"    

// class constructor
Tile::Tile( ol::Bitmap* pBitmap, bool pWalkable, int pId )
{
	Assert( pBitmap, "given Bitmap is NULL!" );
	bitmap = pBitmap;
	walkable = pWalkable;
	id = pId;
}

// class destructor
Tile::~Tile()
{
    // nothing to do, yet
}

void Tile::draw( float pX, float pY ) const
{
    bitmap->Blit( pX, pY );
}

void Tile::drawFast( float pX, float pY ) const
{
    bitmap->FastBlit( pX, pY );
}
