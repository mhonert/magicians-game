#include "paralyseeffect.h" // class's header file
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
ParalyseEffect::ParalyseEffect( World* pWorld, float pX, float pY, int pDirection, float pParalyseTime, Character* pOrigin  )
{
    origin = pOrigin;
    life = 50.0;
    paralyseTime = pParalyseTime;
    direction = pDirection;
    
    dirX = Direction::dirX[ direction ] * 8.0;
    dirY = Direction::dirY[ direction ] * 8.0;

    world = pWorld;
    initSize = int(100.0 * Settings::particlePercent);
    x = pX;
    y = pY;
    particles = new Particle*[initSize];
    for ( int i = 0; i < initSize; i++ )
    {
        Particle* lPart = ParticleStack::getParticle();
        if ( lPart )
        {
            lPart->color.r = float( rand() % 32 + 16 ) / 256.0;
            lPart->color.g = float( rand() % 64 + 192 ) / 256.0;
            lPart->color.b = float( rand() % 32 + 16) / 256.0;
            lPart->x = pX + rand() % 8 - 4;
            lPart->y = pY + rand() % 8 - 4;
            lPart->size = 2;
            lPart->life = rand() % 20;
            lPart->color.a = rand() % 32 + 64;
            lPart->dirX = float(rand() % 5) / 10.0 - .25;
            lPart->dirY = float(rand() % 5) / 10.0 - .25;
            particles[i] = lPart;
        }
        else
        {
            initSize = i;
            break;
        }
    }
    lifeEnd = false;
    target = NULL;

}

// class destructor
ParalyseEffect::~ParalyseEffect()
{
    for ( int i = 0; i < initSize; i++ )
       ParticleStack::releaseParticle( particles[i] );

    delete [] particles;
}

void ParalyseEffect::draw( float pOffsX, float pOffsY )
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

    //ol::Blenders::Set( ol::ADDITIVE_BLENDER );
    for ( int i = 0; i < initSize; i++ )
    {
        if ( particles[i]->life > 0 )
            particles[i]->draw( pOffsX, pOffsY );
    }
    //ol::Blenders::Set( ol::ALPHA_BLENDER );
}

bool ParalyseEffect::update( float pDelta )
{
    if ( ! target )
    {
        x += dirX * pDelta;
        y += dirY * pDelta;
    }
    else
    {
        x = target->getCenterX();
        y = target->getCenterY();
    }

    life -= pDelta;
    if ( life <= 0 )
    {
        lifeEnd = true;
    }

    int pCount = 0;

    if ( ! lifeEnd )
    {
        // check, if the firebullet hits a rock
        Map* lMap = world->getMap();
        if ( lMap->getTileIdAt( int(x), int(y) ) == Tile::ROCK )
        {
            dirX = 0;
            dirY = 0;
            lifeEnd = true;
        }
    
        if ( ! lifeEnd )
        {
            // check, if it hits a character
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
    
                    lChar->getsAttacked( 2, origin );
                    life = paralyseTime;
                    lifeEnd = true;
                    target = *itor;
                    target->setParalysed( true );                
                    dirX = 0;
                    dirY = 0;
                    break;
                }
            }
        }
    }
    
    for ( int i = 0; i < initSize; i++ )
    {
        Particle* part = particles[i];
        if ( part->life > 0 )
        {
            part->life -= pDelta;
            part->x += ( ( dirX  / 2.5 ) + part->dirX ) * pDelta;
            part->y += ( ( dirY / 2.5 ) + part->dirY ) * pDelta;

            pCount++;
        }
        else
        {
            // refresh element, if the effect is still alive
            if ( ! lifeEnd )
            {
                part->color.r = float(rand() % 32 + 16) / 256.0;
                part->color.g = float(rand() % 64 + 192 ) / 256.0;
                part->color.b = float( rand() % 32 + 16 ) / 256.0;
                part->x = x + rand() % 8;
                part->y = y + rand() % 8;
                part->life = rand() % 20;
                part->color.a = rand() % 32 + 64;
                part->dirX = float(rand() % 5) / 10.0 - .25;
                part->dirY = float(rand() % 5) / 10.0 - .25;
                pCount++;
            }
        }
    }
    bool retValue = !( life <= .0 && lifeEnd && pCount == 0 );
    if ( ! retValue )
    {
        if ( target )
            target->setParalysed( false );
    }
    
    return retValue;
}
