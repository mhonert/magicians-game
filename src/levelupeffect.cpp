#include "levelupeffect.h" // class's header file
    using namespace game;
#include <OpenLayer.hpp>
    using namespace ol;
#include <string>
    using namespace std;
#include "resourcemanager.h"

#include "localize.h"

// class constructor
LevelUpEffect::LevelUpEffect( float pX, float pY, ResourceManager* pResource  )
{
	x = pX;
	y = pY;
	sprintf( text, localize( "level up" ) );
	alpha = 192.0;
	olTextRenderer = pResource->getOlTextRenderer( ResourceManager::BIG_FONT );
	x -= olTextRenderer->FirstLineWidth( text ) / 2.0;
}

// class destructor
LevelUpEffect::~LevelUpEffect()
{
}

void LevelUpEffect::draw( float pOffsX, float pOffsY )
{
    olTextRenderer->SetColor( Rgba( 255, 255, 255, int(alpha) ) );
    olTextRenderer->Print( text, int(x - pOffsX), int(y - pOffsY) );
}

bool LevelUpEffect::update( float pDelta )
{
    alpha -= pDelta;
    y -= pDelta;
    x -= sin( ( alpha / 20.0 ) ) * pDelta;
    return alpha >= .0;
}
