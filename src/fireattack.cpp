#include "fireattack.h" // class's header file
    using namespace game;
#include "debug.h"
#include "world.h"
#include "firebullet.h"
#include "character.h"

// class constructor
FireAttack::FireAttack()
{
    // nothing to do, yet
}

// class destructor
FireAttack::~FireAttack()
{
	// nothing to do, yet
}

Attack* FireAttack::clone() const
{
    Attack* tmp = new FireAttack( *this );
    return tmp;
}

void FireAttack::aiAttack( Character* pDest, int pDistance, 
                           int pDistX, int pDistY )
{
    Assert( owner, "no owner of this attack is set!" );
    if ( attackCounter > .0 )
        return;    
        
    if ( pDistance < ( 350 * 350 ) )
    {
        world->addParticleEffect( new FireBullet( world, owner->getCenterX(), owner->getCenterY(), owner->getDirection(), 100, owner ) );
        attackCounter = 150.0;              
    }
}
    		
void FireAttack::playerAttack()
{
    Assert( owner, "no owner of this attack is set!" );
    if ( attackCounter > .0 || owner->getAttribute( Character::MANA ) < 2 )
        return;    

    world->addParticleEffect( new FireBullet( world, owner->getCenterX(), owner->getCenterY(), owner->getDirection(), 100, owner ) );
    attackCounter = 50.0;    
    owner->decAttribute( Character::MANA, 2 );
}
