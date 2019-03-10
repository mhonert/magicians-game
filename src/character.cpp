#include "character.h" // class's header file
using namespace game;
#include "debug.h"
#include <OpenLayer.hpp>

using namespace ol;
#include "world.h"
#include "attack.h"
#include "direction.h"
#include "levelupeffect.h"

// class constructor
Character::Character()
{
    init();
}

// class destructor
Character::~Character()
{
    clear();
}

void Character::init()
{
    bitmap = NULL;
    curBitmap = NULL;
    speed = 0;
    animCounter = 0;
    moving = false;
    direction = Direction::RIGHT;
    lastCollision = NULL;
    isClone = false;
    paralysed = 0;

    for ( int i = 0; i < ATTRIBUTE_COUNT; i++ )
        attributes[i] = 0;

}

void Character::clear()
{
    // nothing to do, yet
    if ( bitmap && ! isClone )
        delete [] bitmap;

}

void Character::changeDirection( int pDir )
{
    Assert( bitmap, "bitmap is NULL!" );
    Assert( pDir >= 0 && pDir < Direction::DIR_COUNT, "invalid direction!" );

    direction = pDir;
    curBitmap = bitmap[ direction * 4 + int(animCounter) ];
}

void Character::draw( float pOffsX, float pOffsY )
{
    Assert( curBitmap, "bitmap is NULL!" );
    if ( paralysed > 0 )
    {
        curBitmap->Blit( int(x - pOffsX), int(y - pOffsY),
                         TintMode( Rgba( 0, 255, 0, 128 ) ) );
    }
    else
        curBitmap->Blit( int(x - pOffsX), int(y - pOffsY) );
}

void Character::loadGraphics( const char* pFile, ResourceManager* pResource )
{
    Assert( pFile, "given parameter is NULL!" );
    Assert( ! bitmap, "graphics are already loaded!" );
    bitmap = new Bitmap*[ 4 * Direction::DIR_COUNT ];


    BITMAP* alBmp = load_bitmap( pFile, NULL );
    Guarantee( alBmp, "bitmap could not be loaded!" );
    pResource->manage( alBmp );

    width = alBmp->w / 4;
    height = alBmp->h / Direction::DIR_COUNT;
    for ( int lDir = 0; lDir < Direction::DIR_COUNT; lDir++ )
    {
        for ( int lAnim = 0; lAnim < 4; lAnim++ )
        {
            BITMAP* alSub = create_sub_bitmap( alBmp, lAnim * width, lDir * height, width, height );
            Guarantee( alSub, "sub-bitmap could not be created!" );
            //pResource->manage( alSub );

            Bitmap* lBmp = new Bitmap( alSub, false, true );
            Guarantee( lBmp->IsValid(), "ol-bitmap could not be created!" );
            pResource->manage( lBmp );
            bitmap[ lDir * 4 + lAnim ] = lBmp;
        }
    }
    curBitmap = bitmap[ direction * 4 + int(animCounter) ];
}

void Character::setSpeed( float pSpeed )
{
    speed = pSpeed;
    animSpeed = ( speed / 15.0);
}

bool Character::update( float pDelta )
{
    oldX = x;
    oldY = y;
    float lSpeed = speed;
    float lAnimSpeed = animSpeed;

    if ( moving )
    {
        if ( paralysed > 0 )
        {
            lSpeed /= 2.0;
            lAnimSpeed /= 2.0;
        }

        // animate
        animCounter += pDelta * lAnimSpeed;
        if ( animCounter >= 4.0 )
            animCounter = animCounter - floor( animCounter );

        Map* lMap = world->getMap();

        curBitmap = bitmap[ direction * 4 + int(animCounter) ];
        // move
        x += lSpeed * Direction::dirX[ direction ] * pDelta;
        y += lSpeed * Direction::dirY[ direction ] * pDelta;

        // check for collisions with the landscape
        if ( ! lMap->isWalkable( getLeft(), getTop() ) ||
                ! lMap->isWalkable( getRight(), getTop() ) ||
                ! lMap->isWalkable( getRight(), getBottom() ) ||
                ! lMap->isWalkable( getLeft(), getBottom() ) ||
                ! lMap->isWalkable( getLeft(), getCenterY() ) ||
                ! lMap->isWalkable( getRight(), getCenterY() ) )
        {
            x = oldX;
            y = oldY;
        }
        else
        {
            // check for collisions with other characters
            CharacterList* lChars = world->getCharacter();
            for ( CharacterItor itor = lChars->begin();
                    itor != lChars->end(); ++itor )
            {
                if ( *itor != this && collides( *itor ) )
                {
                    x = oldX;
                    y = oldY;
                    lastCollision = *itor;
                    animCounter = 0;
                    curBitmap = bitmap[ direction * 4 + int(animCounter) ];
                    moving = false;
                    break;
                }
            }
        }
    }
    return true;

}

void Character::setAttribute( int pId, int pValue )
{
    Assert( pId >= 0 && pId < ATTRIBUTE_COUNT,
            "invalid attribute ID!" );

    switch ( pId )
    {
        case LIFE:
        attributes[ pId ] = MID( 0, pValue, attributes[ MAX_LIFE ] );
        break;
        case MANA:
        attributes[ pId ] = MID( 0, pValue, attributes[ MAX_MANA ] );
        break;
        case LEVEL:
        attributes[ pId ] = pValue;
        attributes[ NEXT_LEVEL_XP ] = pValue * pValue * 10;
        attributes[ PREVIOUS_LEVEL_XP ] = ( pValue - 1 ) * ( pValue - 1 ) * 10;
        attributes[ MAX_LIFE ] = 49 + attributes[ NEXT_LEVEL_XP ] / 10;
        attributes[ MAX_MANA ] = 49 + attributes[ NEXT_LEVEL_XP ] / 10;
        attributes[ LIFE ] = attributes[ MAX_LIFE ];
        attributes[ MANA ] = attributes[ MAX_MANA ];
        break;
        case EXPERIENCE:
        attributes[ pId ] = pValue;
        while ( attributes[ pId ] >= attributes[ NEXT_LEVEL_XP ] )
        {
            // create level up effect
            world->addParticleEffect( new LevelUpEffect( getCenterX() + rand() % 16,
                                      getTop() - rand() % 16,
                                      world->getResourceManager() ) );

            // increase level
            incAttribute( LEVEL, 1 );
        }

        break;
        default:
        attributes[ pId ] = MAX( 0, pValue );
    }
}

void Character::incAttribute( int pId, int pValue )
{
    Assert( pId >= 0 && pId < ATTRIBUTE_COUNT,
            "invalid attribute ID!" );

    setAttribute( pId, attributes[ pId ] + pValue );
}

void Character::decAttribute( int pId, int pValue )
{
    Assert( pId >= 0 && pId < ATTRIBUTE_COUNT,
            "invalid attribute ID!" );

    setAttribute( pId, attributes[ pId ] - pValue );
}
