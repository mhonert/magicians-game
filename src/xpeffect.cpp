#include "xpeffect.h" // class's header file
    using namespace game;

#include <OpenLayer.hpp>
    using namespace ol;
#include <string>
    using namespace std;
#include "resourcemanager.h"

// class constructor
XpEffect::XpEffect( float pX, float pY, int pValue, ResourceManager* pResource  )
{
	x = pX;
	y = pY;
	sprintf( text, "%i XP", pValue );
	alpha = 192.0;
	olTextRenderer = pResource->getOlTextRenderer( ResourceManager::SMALL_FONT );
	x -= olTextRenderer->FirstLineWidth( text ) / 2.0;

}

// class destructor
XpEffect::~XpEffect()
{
}

void XpEffect::draw( float pOffsX, float pOffsY )
{
    olTextRenderer->SetColor( Rgba( 255, 255, 255, int(alpha) ) );
    olTextRenderer->Print( text, int(x - pOffsX), int(y - pOffsY) );
}

bool XpEffect::update( float pDelta )
{
    alpha -= pDelta * 1.5;
    y -= pDelta;
    //x -= sin( ( alpha / 20.0 ) ) * pDelta;
    return alpha >= .0;
}
