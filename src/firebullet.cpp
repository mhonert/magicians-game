#include "firebullet.h" // class's header file
    using namespace game;
#include "particle.h"
#include "particlestack.h"
#include "world.h"
#include "settings.h"
#include "map.h"
#include "tile.h"
#include "character.h"
#include <OpenLayer.hpp>
#include "direction.h"

// class constructor
FireBullet::FireBullet( World* pWorld, float pX, float pY, int pDirection, float pLife, Character* pOrigin  )
{
    origin = pOrigin;
    life = pLife;
    direction = pDirection;

    dirX = Direction::dirX[ direction ] * 5.0;
    dirY = Direction::dirY[ direction ] * 5.0;

    world = pWorld;
	initSize = int(300.0 * Settings::particlePercent);
	x = pX;
	y = pY;
	particles = new Particle*[initSize];
    for ( int i = 0; i < initSize; i++ )
    {
        Particle* lPart = ParticleStack::getParticle();
        if ( lPart )
        {
            lPart->color.r = float( rand() % 32 + 128 ) / 256.0;
            lPart->color.g = float( rand() % 64 + 64 ) / 256.0;
            lPart->color.b = float( rand() % 16 + 16) / 256.0;
            lPart->x = pX + rand() % 8 - 4;
            lPart->y = pY + rand() % 8 - 4;
            lPart->size = 4;
            lPart->life = rand() % 20;
            lPart->color.a = rand() % 8 + 8;
            lPart->dirX = float(rand() % 30) / 10.0 - 1.5;
            lPart->dirY = float(rand() % 30) / 10.0 - 1.5;
            particles[i] = lPart;
        }
        else
        {
            initSize = i;
            break;
        }
    }
    lifeEnd = false;

}

// class destructor
FireBullet::~FireBullet()
{
	for ( int i = 0; i < initSize; i++ )
	   ParticleStack::releaseParticle( particles[i] );

    delete [] particles;
}

void FireBullet::draw( float pOffsX, float pOffsY )
{
	int lX = int( x - pOffsX );
	int lY = int( y - pOffsY );

	if ( lX < -400 )
	   return;
	if ( lX > Settings::screenWidth + 400 )
	   return;
	if ( lY < -400 )
	   return;
	if ( lY > Settings::screenHeight + 400 )
	   return;

    ol::Blenders::Set( ol::ADDITIVE_BLENDER );
    for ( int i = 0; i < initSize; i++ )
    {
        if ( particles[i]->life > 0 )
            particles[i]->draw( pOffsX, pOffsY );
    }
    ol::Blenders::Set( ol::ALPHA_BLENDER );
}

bool FireBullet::update( float pDelta )
{
	x += dirX * pDelta;
	y += dirY * pDelta;
    life -= pDelta;
    if ( life <= 0 )
        lifeEnd = true;

    int pCount = 0;

    // check, if the firebullet hits a rock
    Map* lMap = world->getMap();
    if ( lMap->getTileIdAt( int(x), int(y) ) == Tile::ROCK )
    {
        dirX = 0;
        dirY = 0;
    }

    if ( ! lifeEnd )
    {
        // check, if the firebullet hits a character
        CharacterList* lCharacters = world->getCharacter();
        for ( CharacterItor itor = lCharacters->begin();
              itor != lCharacters->end(); ++itor )
        {
            Character* lChar = *itor;
            if ( lChar != origin )
            {
                if ( x + 10 < lChar->getLeft() )
                    continue;
                if ( x - 4 > lChar->getRight() )
                    continue;
                if ( y + 10 < lChar->getTop() )
                    continue;
                if ( y - 4 > lChar->getBottom() )
                    continue;

                lChar->getsAttacked( 5, origin );
                lifeEnd = true;
                dirX = 0;
                dirY = 0;
            }
        }
    }

    for ( int i = 0; i < initSize; i++ )
    {
        Particle* part = particles[i];
        if ( part->life > 0 )
        {
            part->life -= pDelta;
            part->x += ( ( dirX  / 2 ) + part->dirX ) * pDelta;
            part->y += ( ( dirY / 2 ) + part->dirY ) * pDelta;

            pCount++;
        }
        else
        {
            // refresh element, if the effect is still alive
            if ( ! lifeEnd )
            {
                part->color.r = float(rand() % 32 + 128) / 256.0;
                part->color.g = float(rand() % 64 + 64) / 256.0;
                part->color.b = float( rand() % 16 + 16 ) / 256.0;
                part->x = x + rand() % 8;
                part->y = y + rand() % 8;
                part->life = rand() % 30;
                part->color.a = rand() % 8 + 8;
                part->dirX = float(rand() % 20) / 10.0 - 1.0;
                part->dirY = float(rand() % 20) / 10.0 - 1.0;
                pCount++;
            }
        }
    }
    return pCount > 0;
}
