#include "tilemanager.h" // class's header file
    using namespace game;
#include <OpenLayer.hpp>
    using namespace ol;
#include "tile.h"    
#include "debug.h"    

// class constructor
TileManager::TileManager( ResourceManager* pResourceManager )
{
	init();
    resources = pResourceManager;
}

// class destructor
TileManager::~TileManager()
{
	clear();
}

void TileManager::clear()
{
    // delete all tiles
    TileItor itor = tiles.begin();
    while( itor != tiles.end() )
    {
        delete itor->second;
        ++itor;
    }
    tiles.clear();
}

void TileManager::init()
{
    clear();
}

void TileManager::begin( const char* pFile, int pPrecedence, bool pWalkable )
{
    curPrecedence = pPrecedence;
    curWalkable = pWalkable;

    Assert( pFile, "given parameter is NULL!" );
    Assert( tiles.find( pPrecedence ) == tiles.end(), "tile does already exist" );
    
    BITMAP* lAlBmp = load_bitmap( pFile, NULL );
    Guarantee( lAlBmp, "bitmap could not be loaded!" );
    resources->manage( lAlBmp );    
    
    for ( int x = 0; x < lAlBmp->w / 32; x++ )
    {
        // allegro-sub-bitmap
        BITMAP* lAlSub = create_sub_bitmap( lAlBmp, x * 32, 0, 32, 32 );
        Guarantee( lAlSub, "sub-bitmap could not be created!" );
        //resources->manage( lAlSub );
        // OpenLayer Bitmap
        Bitmap* lBmp = new Bitmap( lAlSub, false, true );
        Guarantee( lBmp->IsValid(), "ol-bitmap could not be loaded!" );
        resources->manage( lBmp );
        // Tile
        Tile* lTile = new Tile( lBmp, curWalkable, curPrecedence );
        tiles.insert( TilePair(curPrecedence, lTile) );
    }    
}

void TileManager::addTransition( const char* pFile, int pPrecedence )
{
    Assert( pFile, "given parameter is NULL!" );        
    Assert( pPrecedence < curPrecedence, "invalid transition!" );
    
    BITMAP* lAlBmp = load_bitmap( pFile, NULL );
    Guarantee( lAlBmp, "bitmap could not be loaded!" );
    resources->manage( lAlBmp );    
    
    // bits 1-5     6-10    11      12-15
    // fromTile     toTile  c/s     corner/side - data
    int lId = curPrecedence | pPrecedence * 32;
    for ( int y = 0; y < 2; y++ )
    {
        for ( int x = 0; x < 15; x++ )
        {
            int lPos = lId | y * 1024 | ( x + 1 ) * 2048;
            // allegro-sub-bitmap
            BITMAP* lAlSub = create_sub_bitmap( lAlBmp, x * 32, y * 32, 32, 32 );
            Guarantee( lAlSub, "sub-bitmap could not be created!" );
            //resources->manage( lAlSub );
            // OpenLayer Bitmap
            Bitmap* lBmp = new Bitmap( lAlSub, false, true );
            Guarantee( lBmp->IsValid(), "ol-bitmap could not be loaded!" );
            resources->manage( lBmp );
            // Tile
            Tile* lTile = new Tile( lBmp, curWalkable, lPos );
            Assert( tiles.find( lPos ) == tiles.end(), "transition does already exist!" );
            tiles.insert( TilePair( lPos, lTile ) );                        
        }
    }
}

void TileManager::end()
{
    // nothing to do, yet
}

Tile* TileManager::getTile( int pId )
{
    Assert( tiles.find( pId ) != tiles.end(), "tile does not exist!" );
    int lCount = tiles.count( pId );
    Tile* lTile;
    if ( lCount == 1 )
    {
    // it is only one Tile!    
        lTile = ( tiles.find( pId ) )->second;
    }
    else
    {
    // randomly select one tile
    // probability of the first tile is the highest

        int lNum = rand() % ( lCount + 10 ) + 1;
        if ( lNum < 11 )
            lNum = 11;
        lNum -= 10;
        
        for ( TileItor itor = tiles.lower_bound( pId );
              itor != tiles.upper_bound( pId );
              ++itor )
        {
            lNum--;
            if ( lNum <= 0 )
            {
                lTile = itor->second;
                break;
            }
        }
    }
    return lTile;
}

Tile* TileManager::getTile( int pFromPrecedence, int pToPrecedence, int pCorner, int pSide )
{
    Assert( !( pCorner != 0 && pSide != 0 ), "choose either corner or side!" );
    int lSideOrCorner = pCorner == 0 ? 1: 0;
    int lValue = pCorner == 0 ? pSide: pCorner;
    
    int lPos = pFromPrecedence | pToPrecedence * 32 | lSideOrCorner * 1024 | lValue * 2048;
    return getTile( lPos );    
}
    		
