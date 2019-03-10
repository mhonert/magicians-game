#include "enemy.h" // class's header file
    using namespace game;
#include "hero.h"

#include "attack.h"
#include "settings.h"
#include "direction.h"
#include "xpeffect.h"
#include <OpenLayer.hpp>
#include "map.h"

// class constructor
Enemy::Enemy()
{
    rethinkCnt = .0;
    dies = false;
    attack = NULL;
}

// class destructor
Enemy::~Enemy()
{
	if ( attack )
    {
        delete attack;
        attack = NULL;
    }
}

GameEntity* Enemy::clone()
{
    Enemy* tmp = new Enemy( *this );
    tmp->isClone = true;
    tmp->animCounter = rand() % 4;
    if ( attack )
        tmp->setAttack( attack->clone() );
    return tmp;
}

void Enemy::draw( float pOffsX, float pOffsY )
{
    Assert( curBitmap, "bitmap is NULL!" );
    if ( dies )
        curBitmap->Blit( int(x - pOffsX), int(y - pOffsY), alpha );
    else
    {
        if ( paralysed > 0 )
            curBitmap->Blit( int(x - pOffsX), int(y - pOffsY),
                             ol::TintMode( ol::Rgba( 0, 255, 0, 128 ) ) );
        else
            curBitmap->Blit( int(x - pOffsX), int(y - pOffsY) );
    }
}


void Enemy::getsAttacked( int pDamage, Character* pBy )
{
    if ( ! dies )
    {
        // enemies can only be damaged by the hero!
        if ( pBy == world->getHero() )
        {
            decAttribute( LIFE, pDamage );
            if ( attributes[ LIFE ] == 0 )
            {
                dies = true;
                alpha = 1.0;
                dieCounter = 10.0;

                pBy->incAttribute( EXPERIENCE, getAttribute( XP_VALUE ) );
                // show the amount of XP gained
                world->addParticleEffect( new XpEffect( getCenterX(), getTop(),
                                                        getAttribute( XP_VALUE ),
                                                        world->getResourceManager() ) );
            }
        }
    }
}

bool Enemy::update( float pDelta )
{
    Assert( attack, "no attack assigned!" );

    Hero* lHero = world->getHero();

    int distX = int( lHero->getCenterX() - getCenterX() );
    int distY = int( lHero->getCenterY() - getCenterY() );

    int absDistX = abs( distX );
    int absDistY = abs( distY );

    if ( absDistX > 1600 || absDistY > 1200 )
    {
        moving = false;
        return true;
    }

    bool retValue = true;
    if ( dies )
    {
        dieCounter -= pDelta / 4;
        alpha -= pDelta / 40;
        if ( dieCounter <= .0 )
            retValue = false;
    }
    else
    {
        retValue = Character::update( pDelta );

        if ( lastCollision )
        {
            if ( lastCollision != lHero )
            {
            // wait until the enemy moves again
                moving = false;
                rethinkCnt = float( rand() % 30 );
            }
            lastCollision = NULL;
        }

        attack->update( pDelta );

        if ( rethinkCnt == .0 )
        {
            // if the hero is near, then move towards him
            if ( absDistX > 800 || absDistY > 800 )
            {
                // hero is out of range, so move randomly
                changeDirection( rand() % 4 );
                moving = true;
                rethinkCnt = float(15 + rand() % 15);
            }
            else
            {
                turnToOptimalDirection( distX, distY );
                if ( paralysed == 0 )
                    attack->aiAttack( lHero, distX * distX + distY * distY, absDistX, absDistY );
            }
        }
        else
        {
            rethinkCnt -= pDelta;
            if ( rethinkCnt < 0 )
                rethinkCnt = 0.0;
        }
    }

    return retValue;
}

void Enemy::turnToOptimalDirection( int pDistX, int pDistY )
{
    Hero* lHero = world->getHero();

    float lHeroDir;
    float lMapDir;
    float lMapValue;
    int lDir;

    // determine the direction to the hero

    float dx = float( pDistX );
    float dy = float( pDistY );
    lHeroDir = fmod( 8.0 + 4.0 * atan2( dx, dy ) / 3.141592653, 8.0 );

    /*
    // determine the direction away from non-walkable-tiles
    {
        Map* lMap = world->getMap();

        int lCenterX = getCenterX();
        int lCenterY = getCenterY();
        lMapValue = .0;
        lMapDir = .0;
        float lSizeX = getRight() - getLeft() + 4.0;
        float lSizeY = getBottom() - getTop() + 4.0;

        for ( int i = 0; i < Direction::DIR_COUNT; i ++ )
        {
            int lX = lCenterX + int( Direction::dirX[ i ] * lSizeX );
            int lY = lCenterY + int( Direction::dirY[ i ] * lSizeY );

            if ( ! lMap->isWalkable( lX, lY ) )
            {
                lMapDir += float( Direction::InvertDir( i ) + 8.0 );
                lMapValue += 2.0;
            }
        }
    }
    lMapValue *= 4.0;
    lDir = int( round( ( lHeroDir * 2.0 + lMapDir ) / ( 2.0 + lMapValue ) ) ) % 8;
    */
    lDir = int( round( lHeroDir ) ) % 8;

    if ( lDir != direction )
    {
        changeDirection( lDir );
    }
    moving = true;

    rethinkCnt = 10.0;
}



void Enemy::setAttack( Attack* pAttack )
{
    attack = pAttack;
    attack->setOwner( this );
    attack->setWorld( world );
}
