#include "energyattack.h" // class's header file
    using namespace game;
#include "debug.h"
#include "world.h"
#include "energybullet.h"
#include "character.h"

// class constructor
EnergyAttack::EnergyAttack()
{
    secondAttack = false;
}

// class destructor
EnergyAttack::~EnergyAttack()
{
    // nothing to do, yet
}

Attack* EnergyAttack::clone() const
{
    Attack* tmp = new EnergyAttack( *this );
    return tmp;
}

void EnergyAttack::aiAttack( Character* pDest, int pDistance,
                           int pDistX, int pDistY )
{
    Assert( owner, "no owner of this attack is set!" );
    if ( attackCounter > .0 )
    {
        if ( attackCounter < 175.0 && ! secondAttack )
        {
            world->addParticleEffect( new EnergyBullet( world, owner->getCenterX(), owner->getCenterY(), owner->getDirection(), 125, owner ) );            
            secondAttack = true;
        }    
        return;
    }

    if ( pDistance < ( 350 * 350 ) )
    {
        world->addParticleEffect( new EnergyBullet( world, owner->getCenterX(), owner->getCenterY(), owner->getDirection(), 150, owner ) );
        secondAttack = false;
        attackCounter = 200.0;
    }
}

void EnergyAttack::playerAttack()
{
    Assert( owner, "no owner of this attack is set!" );
    if ( attackCounter > .0 || owner->getAttribute( Character::MANA ) < 2 )
        return;

    world->addParticleEffect( new EnergyBullet( world, owner->getCenterX(), owner->getCenterY(), owner->getDirection(), 150, owner ) );
    attackCounter = 50.0;
    owner->decAttribute( Character::MANA, 4 );
}

