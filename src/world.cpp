#include "world.h" // class's header file
    using namespace game;
#include "enemy.h"
#include "hero.h"
#include "camera.h"
#include "item.h"
#include "particleeffect.h"
#include "attack.h"
#include "fireattack.h"
#include "bombattack.h"
#include "energyattack.h"
#include "paralyseattack.h"

// class constructor
World::World( ResourceManager* pResources, TileManager* pTiles )
{
    resources = pResources;
    tiles = pTiles;
    init();
}

// class destructor
World::~World()
{
	clear();
}

void World::init()
{
    tilemap = new Map( tiles );
    hero = NULL;
    levelComplete = false;

    // create the attack repository
    Attack* lAttack = new FireAttack();
    lAttack->loadIcon( "icons/fire.bmp", resources );
    attackRepository[ Attack::FIRE ] = lAttack;

    lAttack = new BombAttack();
    lAttack->loadIcon( "icons/bomb.bmp", resources );
    attackRepository[ Attack::BOMB ] = lAttack;

    lAttack = new EnergyAttack();
    lAttack->loadIcon( "icons/energy.bmp", resources );
    attackRepository[ Attack::ENERGY ] = lAttack;

    lAttack = new ParalyseAttack();
    lAttack->loadIcon( "icons/paralyse.bmp", resources );
    attackRepository[ Attack::PARALYSE ] = lAttack;

    // create the character repository
    Hero* lHero = new Hero();
    lHero->setWorld( this );
    lHero->loadGraphics( "character/nwizard.bmp", resources );
    lHero->setSpeed( 2.5 );
    lHero->setBoundingBox( 39, 45, 39, 18 );
    lHero->setAttribute( Character::LEVEL, 1 );
    lHero->setAttribute( Character::LIFE, 50 );
    lHero->setAttribute( Character::MANA, 50 );
    lHero->setAttribute( Character::BOMBS, 0 );
    lHero->setAttribute( Character::EXPERIENCE, 0 );

    //lHero->addAttack( createAttack( Attack::PARALYSE ) );
    lHero->addAttack( createAttack( Attack::FIRE ) );
    lHero->addAttack( createAttack( Attack::ENERGY ) );
    lHero->addAttack( createAttack( Attack::BOMB ) );

    lHero->chooseAttack( 0 );

    characterRepository[ Character::HERO ] = lHero;

    Enemy* enemy = new Enemy();
    enemy->setWorld( this );
    enemy->loadGraphics( "character/nwizard2.bmp", resources );
    enemy->setSpeed( 1.5 );
    enemy->setBoundingBox( 39, 45, 39, 18 );
    enemy->setAttribute( Character::MAX_LIFE, 10 );
    enemy->setAttribute( Character::LIFE, 10 );
    enemy->setAttribute( Character::XP_VALUE, 20 );
    enemy->setAttack( createAttack( Attack::ENERGY ) );
    characterRepository[ Character::EVIL_WIZARD ] = enemy;

    enemy = new Enemy();
    enemy->setWorld( this );
    enemy->loadGraphics( "character/gnome.bmp", resources );
    enemy->setSpeed( 2.25 );
    enemy->setBoundingBox( 32, 18, 30, 20 );
    enemy->setAttribute( Character::MAX_LIFE, 5 );
    enemy->setAttribute( Character::LIFE, 5 );
    enemy->setAttribute( Character::XP_VALUE, 5 );
    enemy->setAttack( createAttack( Attack::BOMB ) );
    characterRepository[ Character::GNOME ] = enemy;

    enemy = new Enemy();
    enemy->setWorld( this );
    enemy->loadGraphics( "character/bmagician.bmp", resources );
    enemy->setSpeed( 1.5 );
    enemy->setBoundingBox( 32, 32, 31, 25 );
    enemy->setAttribute( Character::MAX_LIFE, 15 );
    enemy->setAttribute( Character::LIFE, 15 );
    enemy->setAttribute( Character::XP_VALUE, 15 );
    enemy->setAttack( createAttack( Attack::FIRE ) );
    characterRepository[ Character::BATTLE_MAGICIAN ] = enemy;

    enemy = new Enemy();
    enemy->setWorld( this );
    enemy->loadGraphics( "character/reptile.bmp", resources );
    enemy->setSpeed( .5 );
    enemy->overwriteAnimSpeed( 0.15 );
    enemy->setBoundingBox( 35, 25, 35, 35 );
    enemy->setAttribute( Character::MAX_LIFE, 25 );
    enemy->setAttribute( Character::LIFE, 20 );
    enemy->setAttribute( Character::XP_VALUE, 10 );
    enemy->setAttack( createAttack( Attack::PARALYSE ) );
    characterRepository[ Character::REPTILE ] = enemy;

    // create the item repository
    Item* lItem = new Item();
    lItem->setWorld( this );
    lItem->setType( Item::HEART );
    lItem->loadGraphics( "items/heart.png", resources );
    lItem->setBoundingBox( 5, 7, 7, 9 );
    itemRepository[ Item::HEART ] = lItem;

    lItem = new Item();
    lItem->setWorld( this );
    lItem->setType( Item::EXIT );
    lItem->loadGraphics( "items/exit.png", resources );
    lItem->setBoundingBox( 7, 6, 9, 8 );
    itemRepository[ Item::EXIT ] = lItem;

    lItem = new Item();
    lItem->setWorld( this );
    lItem->setType( Item::BOMB );
    lItem->loadGraphics( "items/bomb.png", resources );
    lItem->setBoundingBox( 8, 8, 7, 7 );
    itemRepository[ Item::BOMB ] = lItem;
    resources->remember( lItem->getBitmap(), ResourceManager::BOMB );

    lItem = new Item();
    lItem->setWorld( this );
    lItem->setType( Item::MANA );
    lItem->loadGraphics( "items/mana.png", resources );
    lItem->setBoundingBox( 7, 10, 9, 5 );
    itemRepository[ Item::MANA ] = lItem;

}

void World::clear()
{
    tiles->clear();
    resources->clear();
    delete tilemap;
    tilemap = NULL;

    resetObjects();
    // clear the attack repository
    for ( AttackMapItor itor = attackRepository.begin();
          itor != attackRepository.end(); ++itor )
    {
        delete itor->second;
    }
    attackRepository.clear();

    // clear the character repository
    for ( CharacterMapItor itor = characterRepository.begin();
          itor != characterRepository.end(); ++itor )
    {
        delete itor->second;
    }
    characterRepository.clear();

    // clear the item repository
    for ( ItemMapItor itor = itemRepository.begin();
          itor != itemRepository.end(); ++itor )
    {
        delete itor->second;
    }
    itemRepository.clear();

}

Attack* World::createAttack( int pId )
{
    Assert( attackRepository.find( pId ) != attackRepository.end(),
            "attack with this ID does not exist!" );
    return (attackRepository[ pId ])->clone();
}


int World::getMaxX() const
{
    return tilemap->getMaxX();
}

int World::getMaxY() const
{
    return tilemap->getMaxY();
}

void World::resetObjects()
{
    CharacterItor citor = character.begin();
    while ( citor != character.end() )
    {
        delete *citor;
        citor = character.erase( citor );
    }

    ParticleItor pitor = particles.begin();
    while ( pitor != particles.end() )
    {
        delete *pitor;
        pitor = particles.erase( pitor );
    }

    ItemItor iitor = items.begin();
    while ( iitor != items.end() )
    {
        delete *iitor;
        iitor = items.erase( iitor );
    }
    hero = NULL;
    levelComplete = false;
}

void World::create()
{
    resetObjects();
    tilemap->loadMap( "maps/0001.bmp", this );

    /*
    hero = (Hero*) characterRepository[ Character::HERO ]->clone();
    character.push_front( hero );

    Item* lItem = (Item*) itemRepository[ Item::HEART ]->clone();
    lItem->setPosition( 700, 300 );
    items.push_front( lItem );

    int lMaxX = tilemap->getMaxX() - 128;
    int lMaxY = tilemap->getMaxY() - 128;
    Enemy* enemy1 = (Enemy*) characterRepository[ Character::ENEMY1 ];
    for ( int i = 0; i < 15; i++ )
    {
        Enemy* enemy = (Enemy*) enemy1->clone();
        enemy->setPosition( rand() % lMaxX + 64, rand() % lMaxY + 64 );
        character.push_front( enemy );
    }
    */

}

void World::draw( Camera* pCamera )
{
    float lX = pCamera->getX();
    float lY = pCamera->getY();

    // draw the landscape
    tilemap->draw( lX, lY );

    // draw the items
    for ( ItemItor itor = items.begin();
          itor != items.end(); ++itor )
    {
        (*itor)->draw( lX, lY );
    }

    // draw the characters
    for ( CharacterItor itor = character.begin();
          itor != character.end(); ++itor )
    {
        (*itor)->draw( lX, lY );
    }


    // draw the particle-effects
    for ( ParticleItor itor = particles.begin();
          itor != particles.end(); ++itor )
    {
        (*itor)->draw( lX, lY );
    }

}

World::EnumWorldEvents World::update( float pDelta )
{
    // update all characters
    CharacterItor citor = character.begin();
    while ( citor != character.end() )
    {
        if ( ! (*citor)->update( pDelta ) )
        {
            if ( *citor == hero )
            {
                return HERO_DIED;
            }
            else
            {
                delete *citor;
                citor = character.erase( citor );
            }
        }
        else
            citor++;
    }
    // sort the list of characters by their y - positions
    character.sort( SortGameEntitiesByY() );

    // update all particle-effects
    ParticleItor pitor = particles.begin();
    while ( pitor != particles.end() )
    {
        if ( ! (*pitor)->update( pDelta ) )
        {
            delete *pitor;
            pitor = particles.erase( pitor );
        }
        else
            pitor++;
    }
    // update all items
    ItemItor iitor = items.begin();
    while ( iitor != items.end() )
    {
        if ( ! (*iitor)->update( pDelta ) )
        {
            delete *iitor;
            iitor = items.erase( iitor );
        }
        else
            iitor++;
    }

    if ( levelComplete )
        return LEVEL_COMPLETED;

    return NOTHING;
}

void World::addParticleEffect( ParticleEffect* pEffect )
{
    particles.push_front( pEffect );
}

void World::createCharacter( int pId, int pX, int pY )
{
    Assert( characterRepository.find( pId ) != characterRepository.end(),
            "character with this id does not exist!" );

    Character* lChar = (Character*) characterRepository[ pId ]->clone();
    lChar->setPosition( pX, pY );
    character.push_front( lChar );

    if ( pId == Character::HERO )
    {
        Guarantee( ! hero, "there is already a hero on this map!" );
        char i[1024];
        //sprintf( i, "%i, %i", hero->getPoints(), hero->getLife() );
        //allegro_message( i );
        hero = (Hero*) lChar;
    }
}

void World::createItem( int pId, int pX, int pY )
{
    Assert( itemRepository.find( pId ) != itemRepository.end(),
            "item with this id does not exist!" );

    Item* lItem = (Item*) itemRepository[ pId ]->clone();
    lItem->setPosition( pX, pY );
    items.push_front( lItem );
}

void World::levelCompleted()
{
    levelComplete = true;
}


