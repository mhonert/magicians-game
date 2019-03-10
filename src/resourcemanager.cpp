#include "resourcemanager.h" // class's header file
    using namespace game;
    
#include <allegro.h>
#include "OpenLayer.hpp"
    using namespace ol;
#include "debug.h"    
    
    
// class constructor
ResourceManager::ResourceManager()
{
	init();
}

// class destructor
ResourceManager::~ResourceManager()
{
	clear();
}

void ResourceManager::clear()
{
    // destroy all Allegro Bitmaps
    AllegroBitmapItor alItor = allegroBitmaps.begin();
    while( alItor != allegroBitmaps.end() )
    {
        destroy_bitmap( *alItor );
        alItor = allegroBitmaps.erase( alItor );
    }
    
    // delete all OpenLayer Bitmaps
    OlBitmapItor olItor = olBitmaps.begin();
    while( olItor != olBitmaps.end() )
    {
        delete *olItor;
        olItor = olBitmaps.erase( olItor );
    }    
    
    olBitmapMap.clear();
    
    // delete all OpenLayer TextRenderer
    for ( OlTextRendererItor itor = olTextRendererMap.begin();
          itor != olTextRendererMap.end(); ++itor )
    {
        delete itor->second;
    }     
    olTextRendererMap.clear();
}

void ResourceManager::init()
{
    clear();
}

void ResourceManager::unload()
{
    // unloads all OpenLayer-Bitmaps from the graphics card
    for( OlBitmapItor olItor = olBitmaps.begin(); olItor != olBitmaps.end(); ++olItor )
    {
        (*olItor)->UnloadFromGPU();
    }     
}

void ResourceManager::reload()
{
    // reloads all OpenLayer-Bitmaps to the graphics card
    for( OlBitmapItor olItor = olBitmaps.begin(); olItor != olBitmaps.end(); ++olItor )
    {
        (*olItor)->SendToGPU();
    }      
}

void ResourceManager::manage( BITMAP* pBitmap )
{
    allegroBitmaps.push_front( pBitmap );
}

void ResourceManager::manage( Bitmap* pBitmap )
{
    olBitmaps.push_front( pBitmap );
}

void ResourceManager::remember( ol::Bitmap* pBitmap, int pId )
{
    Assert( olBitmapMap.find( pId ) == olBitmapMap.end(), "bitmap with this ID does already exist!" );
    olBitmapMap[ pId ] = pBitmap;
}

Bitmap* ResourceManager::getOlBitmap( int pId )
{
    Assert( olBitmapMap.find( pId ) != olBitmapMap.end(), "bitmap with this ID does not exist!" );    
    return olBitmapMap[ pId ];
}

void ResourceManager::manage( ol::TextRenderer* pText, int pId )
{
    Assert( olTextRendererMap.find( pId ) == olTextRendererMap.end(), "textrenderer with this ID does already exist!" );
    olTextRendererMap[ pId ] = pText;    
}

TextRenderer* ResourceManager::getOlTextRenderer( int pId )
{
    Assert( olTextRendererMap.find( pId ) != olTextRendererMap.end(), "textrenderer with this ID does not exist!" );    
    return olTextRendererMap[ pId ];
}



