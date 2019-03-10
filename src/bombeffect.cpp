#include "bombeffect.h" // class's header file
    using namespace game;
#include <OpenLayer.hpp>
#include "settings.h"
#include "particlestack.h"
#include "resourcemanager.h"
#include "world.h"
#include "map.h"
#include "direction.h"
#include "character.h"

// class constructor
BombEffect::BombEffect( float pX, float pY, World* pWorld, Character* pOrigin, float pTime )
{
    world = pWorld;
    origin = pOrigin;
    bitmap = ( pWorld->getResourceManager() )->getOlBitmap( ResourceManager::BOMB );

	initSize = int(300.0 * Settings::particlePercent);
	x = pX;
	y = pY;
	lifeTime = pTime;

	particles = new Particle*[initSize];
    for ( int i = 0; i < initSize; i++ )
    {
        Particle* lPart = ParticleStack::getParticle();
        if ( lPart )
        {
            if ( i < ( initSize / 4 ) )
            {
                lPart->color.r = float( rand() % 128 + 128 ) / 256.0;
                lPart->color.g = float( rand() % 128 + 96 ) / 256.0;
                lPart->color.b = float( rand() % 32 ) / 256.0;
            }
            else
            {
                lPart->color.r = float( rand() % 64 + 128 ) / 256.0;
                lPart->color.g = float( rand() % 64 + 128 ) / 256.0;
                lPart->color.b = float( rand() % 16 + 128 ) / 256.0;
            }
            lPart->x = pX + rand() % 16 - 8;
            lPart->y = pY + rand() % 16 - 8;
            lPart->size = 4;
            lPart->life = rand() % 60;
            lPart->color.a = rand() % 8 + 8;
            lPart->dirX = float(rand() % 20) / 10.0 - 1.0;
            lPart->dirY = float(rand() % 20) / 10.0 - 1.0;
            particles[i] = lPart;
        }
        else
        {
            initSize = i;
            break;
        }
    }
    damaged = false;
    exploded = false;

}

// class destructor
BombEffect::~BombEffect()
{
	for ( int i = 0; i < initSize; i++ )
	   ParticleStack::releaseParticle( particles[i] );

    delete [] particles;
}

void BombEffect::draw( float pOffsX, float pOffsY )
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

    if ( exploded )
    {
        ol::Blenders::Set( ol::ADDITIVE_BLENDER );
        for ( int i = 0; i < initSize; i++ )
        {
            if ( particles[i]->life > 0 )
                particles[i]->draw( pOffsX, pOffsY );
        }
        ol::Blenders::Set( ol::ALPHA_BLENDER );
    }
    else
    {
        bitmap->Blit( float(lX - 16), float(lY - 16) );
    }

}

bool BombEffect::update( float pDelta )
{
    bool retValue = true;

    if ( exploded )
    {
        int pCount = 0;
        for ( int i = 0; i < initSize; i++ )
        {
            Particle* part = particles[i];
            if ( part->life > .0 )
            {
                part->life -= pDelta ;
                part->x += part->dirX * pDelta;
                part->y += part->dirY * pDelta;
                part->size -= ( pDelta / 20 );
                if ( part->size < .0 )
                    part->size = .1;
                pCount++;
            }
        }
        if ( ! damaged )
        {
            // do damage
            damaged = true;
            Map* lMap = world->getMap();

            for ( int lDir = 0; lDir < 9; lDir++ )
            {
                lMap->explodeTileAt( int(x + Direction::iDirX[ lDir ] * 32),
                                     int(y + Direction::iDirY[ lDir ] * 32) );
            }

            Character* lHero = (Character*) world->getHero();
            // damage characters
            CharacterList* lCharacters = world->getCharacter();
            for ( CharacterItor itor = lCharacters->begin();
                  itor != lCharacters->end(); ++itor )
            {
                Character* lChar = *itor;
                // if the bomb was lied by the hero
                // all characters will be damaged
                // if it was lied by an enemy, only the hero gets damaged
                // the origin can't damage himself
                if ( lChar != origin && ( origin == lHero || lChar == lHero ) )
                {
                    for ( int lDir = 0; lDir < 9; lDir++ )
                    {
                        if ( x + Direction::iDirX[ lDir ] * 32 < lChar->getLeft() )
                            continue;
                        if ( x - Direction::iDirX[ lDir ] * 32 > lChar->getRight() )
                            continue;
                        if ( y + Direction::iDirY[ lDir ] * 32 < lChar->getTop() )
                            continue;
                        if ( y - Direction::iDirY[ lDir ] * 32 > lChar->getBottom() )
                            continue;

                        if ( origin == lHero )
                        {
                        // bombs of the hero are much more dangerous!
                        // this ensures, that they remain useful at all levels
                        // of the game, when enemies are getting stronger and stronger
                            lChar->getsAttacked( 100, origin );
                        }
                        else
                        {
                            lChar->getsAttacked( 25, origin );
                        }
                        break;
                    }
                }
            }
        }

        retValue = pCount > 0;
    }
    else
    {
        lifeTime -= pDelta;
        if ( lifeTime <= .0 )
        {
            exploded = true;
        }
    }
    return retValue;

}

