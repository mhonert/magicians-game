#include "attack.h" // class's header file
    using namespace game;
#include "resourcemanager.h"
#include <OpenLayer.hpp>
    using namespace ol;
    
#include "debug.h"    

// class constructor
Attack::Attack()
{ 
    owner = NULL; 
    attackCounter = .0; 
    bitmap = NULL;
}


// class destructor
Attack::~Attack()
{
	// insert your code here
}

void Attack::loadIcon( const char* pFile, ResourceManager* pResource )
{
    BITMAP* alBmp = load_bitmap( pFile, NULL );
    Guarantee( alBmp, "bitmap could not be loaded!" );
    //pResource->manage( alBmp );

    bitmap = new Bitmap( alBmp, false, true );
    Guarantee( bitmap->IsValid(), "ol-bitmap could not be created!" );
    pResource->manage( bitmap );
}

