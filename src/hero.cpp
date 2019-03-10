#include "hero.h" // class's header file
    using namespace game;

#include "attack.h"

// class constructor
Hero::Hero()
{
    points = 0;
    attacking = false;
}

// class destructor
Hero::~Hero()
{
    for ( int i = 0; i < attacks.size(); i++ )
    {
        delete attacks[i];    
    }
    attacks.clear();
}

GameEntity* Hero::clone()
{
    Hero* tmp = new Hero( *this );
    tmp->isClone = true;
    tmp->points = 0;
    tmp->attacks.clear();
    for ( int i = 0; i < attacks.size(); i++ )
    {
        tmp->addAttack( (attacks[i])->clone() );    
    }
    tmp->chooseAttack( 0 );
    
    return tmp;
}

void Hero::getsAttacked( int pDamage, Character* pBy )
{
    decAttribute( LIFE, pDamage );
}


bool Hero::update( float pDelta )
{
    Assert( attack, "no attack assigned!" ); 
    bool retValue;
    retValue = Character::update( pDelta );
    
    attack->update( pDelta );
    if ( attacking && paralysed == 0 )
    {
        attack->playerAttack();
        //world->addParticleEffect( new MagicShield( this ) );
    }
    
    retValue = attributes[ LIFE ] > 0;
    return retValue;
}

void Hero::addAttack( Attack* pAttack )
{
    pAttack->setOwner( this );
    pAttack->setWorld( world );    
    attacks.push_back( pAttack );
}


const AttackVec* Hero::getAttacks()
{
    return &attacks;
}

void Hero::chooseAttack( int pIndex )
{
    Assert( pIndex >= 0 && pIndex < attacks.size(), "attack-index does not exist!" );
    attack = attacks[ pIndex ];    
}

