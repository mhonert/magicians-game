#include "paralyseattack.h" // class's header file
    using namespace game;
#include "debug.h"
#include "world.h"
#include "paralyseeffect.h"
#include "character.h"

// class constructor
ParalyseAttack::ParalyseAttack()
{
    // nothing to do, yet
}

// class destructor
ParalyseAttack::~ParalyseAttack()
{
    // nothing to do, yet
}

Attack* ParalyseAttack::clone() const
{
    Attack* tmp = new ParalyseAttack( *this );
    return tmp;
}

void ParalyseAttack::aiAttack( Character* pDest, int pDistance,
                           int pDistX, int pDistY )
{
    Assert( owner, "no owner of this attack is set!" );
    if ( attackCounter > .0 )
        return;

    if ( pDistance < ( 350 * 350 ) )
    {
        world->addParticleEffect( new ParalyseEffect( world, owner->getCenterX(), owner->getCenterY(), owner->getDirection(), 300.0, owner ) );
        attackCounter = 150.0;
    }
}

void ParalyseAttack::playerAttack()
{
    Assert( owner, "no owner of this attack is set!" );
    if ( attackCounter > .0 || owner->getAttribute( Character::MANA ) < 2 )
        return;

    world->addParticleEffect( new ParalyseEffect( world, owner->getCenterX(), owner->getCenterY(), owner->getDirection(), 1000.0, owner ) );
    attackCounter = 50.0;
    owner->decAttribute( Character::MANA, 2 );
}
