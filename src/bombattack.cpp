#include "bombattack.h" // class's header file
    using namespace game;

#include "world.h"
#include "bombeffect.h"
#include "character.h"
#include "hero.h"
#include "direction.h"

// class constructor
BombAttack::BombAttack()
{
}

// class destructor
BombAttack::~BombAttack()
{
	// nothing to do, yet
}

Attack* BombAttack::clone() const
{
    Attack* tmp = new BombAttack( *this );
    return tmp;    
}

void BombAttack::aiAttack( Character* pDest, int pDistance, 
                           int pDistX, int pDistY )
{
    Assert( owner, "no owner of this attack is set!" );
    if ( attackCounter > .0 )
        return;    
        
    if ( pDistX < 48 && pDistY < 48 )
    {
        int lDir = owner->getDirection();
        int lX;
        int lY;
        switch ( lDir )
        {
            case Direction::UP:
                lX = int( owner->getCenterX() );
                lY = int( owner->getTop() );
                break;        
            case Direction::DOWN:
                lX = int( owner->getCenterX() );
                lY = int( owner->getBottom() );
                break;        
            case Direction::LEFT:
                lX = int( owner->getLeft() );
                lY = int( owner->getBottom() );
                break;        
            case Direction::RIGHT:
                lX = int( owner->getRight() );
                lY = int( owner->getBottom() );
                break;        
        }   
        world->addParticleEffect( new BombEffect( lX, lY, world, owner, 25.0 ) );
        attackCounter = 75.0;              
    }
}                           


void BombAttack::playerAttack()
{
    Assert( owner, "no owner of this attack is set!" );
    if ( attackCounter > .0 || owner->getAttribute( Character::BOMBS ) == 0 )
        return;    

    int lDir = owner->getDirection();
    int lX;
    int lY;
    switch ( lDir )
    {
        case Direction::UP:
            lX = int( owner->getCenterX() );
            lY = int( owner->getTop() );
            break;        
        case Direction::DOWN:
            lX = int( owner->getCenterX() );
            lY = int( owner->getBottom() );
            break;        
        case Direction::LEFT:
            lX = int( owner->getLeft() );
            lY = int( owner->getBottom() );
            break;        
        case Direction::RIGHT:
            lX = int( owner->getRight() );
            lY = int( owner->getBottom() );
            break;        
   
    }        

    world->addParticleEffect( new BombEffect( lX, lY, world, owner, 50.0 ) );
    owner->decAttribute( Character::BOMBS, 1 );
    attackCounter = 20.0;         		
}
