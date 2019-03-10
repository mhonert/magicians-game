#include "map.h" // class's header file
    using namespace game;
#include "tile.h"
#include "settings.h"
#include "world.h"

#include <OpenLayer.hpp>

#include "debug.h"

// class constructor
Map::Map( TileManager* pTiles )
{
	tiles = pTiles;
	init();
}

// class destructor
Map::~Map()
{
	clear();
}


void Map::init()
{
    tilemap = NULL;
    tiletrans = NULL;
    tiletrans1 = NULL;
    
    // prepare the tileset
    tiles->begin( "tiles/wasser.bmp", Tile::WATER, false );
    tiles->end();
    
    tiles->begin( "tiles/sand.bmp", Tile::SAND, true );
    tiles->addTransition( "tiles/sand2wasser.bmp", Tile::WATER );
    tiles->end();

    tiles->begin( "tiles/gras.bmp", Tile::GRASS, true );
    tiles->addTransition( "tiles/gras2wasser.bmp", Tile::WATER );
    tiles->addTransition( "tiles/gras2sand.bmp", Tile::SAND );
    tiles->end();

    tiles->begin( "tiles/fels.bmp", Tile::ROCK, false );
    tiles->addTransition( "tiles/fels2wasser.bmp", Tile::WATER );
    tiles->addTransition( "tiles/fels2sand.bmp", Tile::SAND );
    tiles->addTransition( "tiles/fels2gras.bmp", Tile::GRASS );
    tiles->end();
    
    tiles->begin( "tiles/brfels.bmp", Tile::BROKEN_ROCK, true );
    tiles->end();
    
}

void Map::clear()
{
    if ( tilemap )
    {
        delete [] tilemap;
        tilemap = NULL;
    }
    if ( tiletrans )
    {
        delete [] tiletrans;
        tiletrans = NULL;
    }   
    if ( tiletrans1 )
    {
        delete [] tiletrans1;
        tiletrans1 = NULL;
    }       
}

bool Map::isWalkable( int pX, int pY ) const
{
    Assert( pX > 0 && pX / 32 < width, "x is not inside the map!" );
    Assert( pY > 0 && pY / 32 < height, "y is not inside the map!" );
    
    return tilemap[ (pX / 32) + (pY / 32) * width ]->isWalkable();
}

int Map::getTileIdAt( int pX, int pY ) const
{
    Assert( pX > 0 && pX / 32 < width, "x is not inside the map!" );
    Assert( pY > 0 && pY / 32 < height, "y is not inside the map!" );
    
    return tilemap[ (pX / 32) + (pY / 32) * width ]->getId();
}

void Map::explodeTileAt( int pX, int pY )
{
    // the rocks at the border of the map must not explode!
    if( pX / 32 <= 1 || pX / 32 >= width - 1 )
        return;
    if (pY / 32 <= 1 || pY / 32 >= height - 1 )
        return;
    
    int lPos = (pX / 32) + (pY / 32) * width;
    if ( tilemap[ lPos ]->getId() == Tile::ROCK )
    {
        tilemap[ lPos ] = tiles->getTile( Tile::BROKEN_ROCK );
    }
}
   		
void Map::draw( float pX, float pY )
{
    Assert( tilemap, "tilemap is NULL!" );
    
    int lX = MID( 0, int(pX), maxX );
    int lY = MID( 0, int(pY), maxY );
    
    int modX = lX % 32;
    int modY = lY % 32;
    
    int posX = lX / 32;
    int posY = lY / 32;
    ol::Bitmap::StartFastBlitting();
    for ( int y = 0; y <= tilesPerScrY; y++ )
    {
        int lOffs = (posY + y) * width + posX;
        int lDrawY = y * 32 - modY;
        for ( int x = 0; x <= tilesPerScrX; x++, lOffs++ )
        {
            int lDrawX = x * 32 - modX;
            tilemap[ lOffs ]->drawFast( lDrawX, lDrawY );
            
            Tile* lTile = tiletrans[ lOffs ];
            if ( lTile )
                lTile->drawFast( lDrawX, lDrawY );
            lTile = tiletrans1[ lOffs ];
            if ( lTile )
                lTile->drawFast( lDrawX, lDrawY );                
        }
    }
    ol::Bitmap::FinishFastBlitting();            
        
}

void Map::prepareMap()
{
    // calculate tiles per screen
    tilesPerScrX = MIN( width - 1, Settings::screenWidth / 32 );
    if ( tilesPerScrX < width - 1 )
    {
        if ( Settings::screenWidth % 32 != 0 )
            tilesPerScrX++;
        maxX = ( width - tilesPerScrX ) * 32 - 1;
    }
    else
        maxX = 0;    
        
    tilesPerScrY = MIN( height - 1, Settings::screenHeight / 32 );
    if ( tilesPerScrY < height - 1 )
    {
        if ( Settings::screenHeight % 32 != 0 )
            tilesPerScrY++;
        maxY = ( height - tilesPerScrY ) * 32 - 1;
    }
    else
        maxY = 0;    
    
    tilemap = new Tile*[ width * height ];
    tiletrans = new Tile*[ width * height ];
    tiletrans1 = new Tile*[ width * height ];     
}

void Map::loadMap( const char* pFile, World* pWorld )
{
    clear();
    
    // level-bitmap should stay 8-bit
    set_color_conversion( COLORCONV_NONE );
    BITMAP* lMap = load_bitmap( pFile, NULL );
    Guarantee( lMap, "level-map could not be loaded!" );
    
    width = lMap->w;
    height = lMap->h;
    
    prepareMap();
    for ( int lY = 0; lY < height; lY++ )
    {
        for ( int lX = 0; lX < width; lX++ )
        {
            int lByte = _getpixel( lMap, lX, lY );
            
            if ( lByte < 32 )       // check, if it is a landscape-tile
            {
                tilemap[ lX + lY * width ] = tiles->getTile( lByte );
            }
            else if ( lByte < 128 ) // check, if it is an item
            {
                tilemap[ lX + lY * width ] = tilemap[ lX - 1 + lY * width ];
                pWorld->createItem( lByte - 32, lX * 32, lY * 32 );
            }
            else
            {
            // it must be a character
                tilemap[ lX + lY * width ] = tilemap[ lX - 1 + lY * width ];
                pWorld->createCharacter( lByte - 128, lX * 32, lY * 32 );                                
            }
            tiletrans[ lX + lY * width ] = NULL;
            tiletrans1[ lX + lY * width ] = NULL;
        }
    }
    
    destroy_bitmap( lMap );    
    set_color_conversion( COLORCONV_TOTAL );
    
    correctMap();
    smoothMap();
   
        
}

void Map::create()
{
    clear();
    width = 128;
    height = 128;
    
    prepareMap();
    // create map-border
    for ( int y = 0; y < height; y++ )
    {
        tilemap[ y * width ] = tiles->getTile( Tile::ROCK );
        tiletrans[ y * width ] = NULL;
        tiletrans1[ y * width ] = NULL;

        tilemap[ y * width + width - 1 ] = tiles->getTile( Tile::ROCK );
        tiletrans[ y * width + width - 1 ] = NULL;
        tiletrans1[ y * width + width - 1 ] = NULL;
    }        
    for ( int x = 0; x < width; x++ )
    {
        tilemap[ x ] = tiles->getTile( Tile::ROCK );
        tiletrans[ x ] = NULL;
        tiletrans1[ x ] = NULL;
        tilemap[ x + ( height - 1 ) * width ] = tiles->getTile( Tile::ROCK );
        tiletrans[ x + ( height - 1 ) * width ] = NULL;
        tiletrans1[ x + ( height - 1 ) * width ] = NULL;
    }        

    for ( int y = 1; y < height - 1; y++ )
    {
        for ( int x = 1; x < width - 1; x++ ) 
        {
            tilemap[ x + y * width ] = tiles->getTile( Tile::GRASS );   

            tiletrans[ x + y * width ] = NULL;    
            tiletrans1[ x + y * width ] = NULL;    
        }
    }

    // create water
    addLandscapes( 20, 300, Tile::WATER );       
    // create rocks
    addLandscapes( 10, 150, Tile::ROCK );       
    // create sand
    addLandscapes( 20, 100, Tile::SAND ); 
    // create gras      
    addLandscapes( 10, 20, Tile::GRASS ); 
    
    correctMap();    
    smoothMap();
}

void Map::addLandscapes( int pCount, int pSize, int pId )
{
    Tile* lTile = tiles->getTile( pId );
    for ( int i = 0; i < pCount; i++ )
    {
        int lSize = rand() % ( pSize / 2 ) + pSize / 2;
        int lX = rand() % (width - 4) + 2;
        int lY = rand() % (height - 4) + 2;
        for ( int j = 0; j < pSize; j++ )
        {
            tilemap[ lX + lY * width ] = lTile;
            bool okay;
            do
            {
                okay = true;
                switch( rand() % 4 )
                {
                    case 0: lX--; break;
                    case 1: lY--; break;
                    case 2: lX++; break;
                    case 3: lY++; break;
                }
                if ( lX < 1 )
                {    lX++; okay = false; }
                if ( lY < 1 )
                {    lY++; okay = false; }
                if ( lX > width - 2 )
                {    lX--; okay = false; }
                if ( lY > height - 2 )
                {    lY--; okay = false; }
            }
            while( ! okay );
        }
    }
}

void Map::correctMap()
{
    int lNeighbour[8];
    for ( int y = 1; y < height - 1; y++ )
    {
        for ( int x = 1; x < width - 1; x++ ) 
        {
            int diffNeighbours = 0;
            int maxId = -1;
            int selfId = tilemap[ x + y * width ]->getId();
            // ignore special tiles
            if ( selfId > Tile::MAX_LANDSCAPE )
                continue;            
            lNeighbour[0] = tilemap[ x - 1 + ( y - 1 ) * width ]->getId();
            lNeighbour[1] = tilemap[ x + 1 + ( y - 1 ) * width ]->getId();
            lNeighbour[2] = tilemap[ x + 1 + ( y + 1 ) * width ]->getId();
            lNeighbour[3] = tilemap[ x - 1 + ( y + 1 ) * width ]->getId();
            lNeighbour[4] = tilemap[ x - 1 + y * width ]->getId();
            lNeighbour[5] = tilemap[ x + ( y - 1 ) * width ]->getId();
            lNeighbour[6] = tilemap[ x + 1 + y * width ]->getId();
            lNeighbour[7] = tilemap[ x + ( y + 1 ) * width ]->getId();            
            
            int lFind[8];
            int lFindCnt = 0;
            for ( int i = 0; i < 8; i++ )
            {
                if ( lNeighbour[i] > selfId && lNeighbour[i] < Tile::MAX_LANDSCAPE )
                {
                    // check, if this id is already counted
                    bool isCount = false;
                    for ( int j = 0;j < lFindCnt; j++ )
                        if ( lFind[j] == lNeighbour[i] )
                        {
                            isCount = true;
                            break;
                        }
                    if ( ! isCount )
                    {
                        lFind[lFindCnt] = lNeighbour[i];
                        lFindCnt++;
                        diffNeighbours++;
                        if ( lNeighbour[i] > maxId )
                            maxId = lNeighbour[i];
                    }
                }                        
            }
            if ( diffNeighbours > 1 )
            {
                tilemap[ x + y * width ] = tiles->getTile( maxId );
                x = 0;
                y = 1;
            }
        }
    }    
}

void Map::smoothMap()
{
    int corner[4];
    int side[4];
    
    int pow2[] = { 0, 1, 2, 4, 8, 16, 32 };
    
    for ( int y = 1; y < height - 1; y++ )
    {
        for ( int x = 1; x < width - 1; x++ ) 
        {
            int selfId = tilemap[ x + y * width ]->getId();
            // ignore special tiles
            if ( selfId > Tile::MAX_LANDSCAPE )
                continue;             
            corner[0] = tilemap[ x - 1 + ( y - 1 ) * width ]->getId();
            corner[1] = tilemap[ x + 1 + ( y - 1 ) * width ]->getId();
            corner[2] = tilemap[ x + 1 + ( y + 1 ) * width ]->getId();
            corner[3] = tilemap[ x - 1 + ( y + 1 ) * width ]->getId();
            side[0] = tilemap[ x - 1 + y * width ]->getId();
            side[1] = tilemap[ x + ( y - 1 ) * width ]->getId();
            side[2] = tilemap[ x + 1 + y * width ]->getId();
            side[3] = tilemap[ x + ( y + 1 ) * width ]->getId();
            
            int cornerId = 0;
            int lCounter = 1;
            int lCorner = 0;
            // check the corners
            for ( int i = 0; i < 4; i++ )
            {
                if ( corner[i] > selfId && corner[i] < Tile::MAX_LANDSCAPE )
                {
                    cornerId = corner[i];
                    lCorner |= lCounter;
                }
                lCounter *= 2;
            }
            // check the sides
            int sideId = 0;
            int lSide = 0;
            lCounter = 1;
            for ( int i = 0; i < 4; i++ )
            {
                if ( side[i] > selfId && side[i] < Tile::MAX_LANDSCAPE )
                {
                    sideId = side[i];
                    // remove corners, which are covered by the side
                    lCorner &= ! pow2[ ( i - 1 + 4) % 4 + 1 ];
                    lCorner &= ! lCounter;
                    lSide |= lCounter;
                }
                lCounter *= 2;
            }
            
            if ( lSide != 0 ) 
            {
                tiletrans[ x + y * width ] = tiles->getTile( sideId + selfId * 32 + lSide * 2048 );    
            }                
            if ( lCorner != 0 ) 
            {
                tiletrans1[ x + y * width ] = tiles->getTile( cornerId + selfId * 32 + 1024 + lCorner * 2048 );    
            }                


        }
    }
}
