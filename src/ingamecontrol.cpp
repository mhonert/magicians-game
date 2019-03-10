#include "ingamecontrol.h" // class's header file
    using namespace game;
#include "hero.h"
#include <allegro.h>
#include "debug.h"
#include "direction.h"
#include <OpenLayer.hpp>
#include "settings.h"
#include "attack.h"
#include "resourcemanager.h"
#include "frameratecontrol.h"
#include "abstractcontroller.h"

// class constructor
InGameControl::InGameControl( ResourceManager* pResource, AbstractController* pController )
{
	curAttack = 0;
	attackIcon = NULL;
	chooseAttack = false;
	showAttacksCnt = .0;
	resource = pResource;
	controller = pController;

    lifeCol[0] = ol::Rgba( 192, 0, 0 );
    lifeCol[1] = ol::Rgba( 128, 0, 64 );
    lifeCol[2] = ol::Rgba( 128, 0, 64 );
    lifeCol[3] = ol::Rgba( 192, 0, 0 );

    manaCol[0] = ol::Rgba( 0, 0, 192 );
    manaCol[1] = ol::Rgba( 64, 0, 128 );
    manaCol[2] = ol::Rgba( 64, 0, 128 );
    manaCol[3] = ol::Rgba( 0, 0, 192 );

    xpCol[0] = ol::Rgba( 210, 190, 30 );
    xpCol[1] = ol::Rgba( 160, 140, 20 );
    xpCol[2] = ol::Rgba( 160, 140, 20 );
    xpCol[3] = ol::Rgba( 210, 190, 30 );

    updateTextCnt = .0;
    sprintf( fps, "FPS: ----" );

}

// class destructor
InGameControl::~InGameControl()
{
	// nothing to do yet
}

void InGameControl::setHero( Hero* pHero )
{
    hero = pHero;
    attackIcon = ( ( *hero->getAttacks() )[ curAttack ] )->getIcon();
    bombIcon = resource->getOlBitmap( ResourceManager::BOMB );
    smallFont = resource->getOlTextRenderer( ResourceManager::SMALL_FONT );
    verySmallFont = resource->getOlTextRenderer( ResourceManager::VERY_SMALL_FONT );
    sprintf( level, "%i", hero->getAttribute( Character::LEVEL ) );
    sprintf( life, "%i / %i",
             hero->getAttribute( Character::LIFE ),
             hero->getAttribute( Character::MAX_LIFE ) );
    sprintf( mana, "%i / %i",
             hero->getAttribute( Character::MANA ),
             hero->getAttribute( Character::MAX_MANA ) );
}


bool InGameControl::update( float pDelta )
{
    Assert( hero, "hero is not set!" );
    Assert( controller, "controller is not set!" );

    // attack
    if ( controller->isKeyPressed( AbstractController::ACTION ) )
    {
        hero->setAttacking( true );
    }
    else
    {
        hero->setAttacking( false );
    }

    // choose an attack
    if ( chooseAttack )
    {
        showAttacksCnt -= pDelta;
        if ( showAttacksCnt < .0 )
        {
            showAttacksCnt = .0;
            chooseAttack = false;
        }
    }

    // choose the previous weapon of the list
    if ( ! controller->isKeyLocked( AbstractController::NEXT ) )
    {
        if ( controller->isKeyPressed( AbstractController::NEXT ) )
        {
            controller->lockKey( AbstractController::NEXT );
            const AttackVec* lAttacks = hero->getAttacks();
            curAttack = (curAttack + 1) % lAttacks->size();
            hero->chooseAttack( curAttack );
            attackIcon = ( ( *hero->getAttacks() )[ curAttack ] )->getIcon();
            chooseAttack = true;
            showAttacksCnt = 50.0;
        }
    }
    else
    {
        if ( ! controller->isKeyPressed( AbstractController::NEXT ) )
            controller->unlockKey( AbstractController::NEXT );
    }

    // choose the next weapon of the list
    if ( ! controller->isKeyLocked( AbstractController::PREVIOUS ) )
    {
        if ( controller->isKeyPressed( AbstractController::PREVIOUS ) )
        {
            controller->lockKey( AbstractController::PREVIOUS );
            const AttackVec* lAttacks = hero->getAttacks();
            curAttack = curAttack - 1;
            if ( curAttack < 0 )
                curAttack = lAttacks->size() - 1;
            hero->chooseAttack( curAttack );
            attackIcon = ( ( *hero->getAttacks() )[ curAttack ] )->getIcon();
            chooseAttack = true;
            showAttacksCnt = 50.0;
        }
    }
    else
    {
        if ( ! controller->isKeyPressed( AbstractController::PREVIOUS ) )
            controller->unlockKey( AbstractController::PREVIOUS );
    }

    // move the hero
    int lDirection = controller->getDirection();
    if ( lDirection != Direction::NONE )
    {
        hero->changeDirection( lDirection );
        hero->setMoving( true );
    }
    else
    {
        hero->setMoving( false );
    }

    // exit
    if ( controller->isKeyPressed( AbstractController::EXIT ) )
        return false;

    // update all text-strings
    updateTextCnt += pDelta;
    if ( updateTextCnt > 10.0 )
    {
        updateTextCnt = .0;
        sprintf( level, "%i", hero->getAttribute( Character::LEVEL ) );
        sprintf( fps, "FPS: %4i", int( FrameRateControl::GetFps() ) );
        sprintf( life, "%i / %i",
                 hero->getAttribute( Character::LIFE ),
                 hero->getAttribute( Character::MAX_LIFE ) );
        sprintf( mana, "%i / %i",
                 hero->getAttribute( Character::MANA ),
                 hero->getAttribute( Character::MAX_MANA ) );
    }

    return true;
}

void InGameControl::draw()
{
    // show the attacks
    float y = Settings::screenHeight - 40.0;
    float x = 16.0;
    if ( chooseAttack )
    {
        const AttackVec* lAttacks = hero->getAttacks();
        for ( int i = 0; i < lAttacks->size(); i++ )
        {
            ol::Bitmap* lBmp = ( (*lAttacks)[ i ] )->getIcon();
            if ( i != curAttack )
                lBmp->Blit( x, y, .25 );
            x += 34.0;
        }

        attackIcon->Blit( float( curAttack * 34.0 + 16.0 ), y - 8.0 );
    }
    else
    {
        attackIcon->Blit( x, y );
    }

    // show the health
    int healthRatio = hero->getAttribute( Character::LIFE ) * 100
                      / hero->getAttribute( Character::MAX_LIFE );

    ol::Rect( 16.0, 12.0, float(healthRatio), 10.0 ).Draw( lifeCol );
    ol::Rect( 16.0, 12.0, 100.0, 10.0 ).DrawOutline( ol::Rgba::BLACK );

    // show the mana
    int manaRatio = hero->getAttribute( Character::MANA ) * 100
                      / hero->getAttribute( Character::MAX_MANA );

    ol::Rect( 16.0, 26.0, float(manaRatio), 10.0 ).Draw( manaCol );
    ol::Rect( 16.0, 26.0, 100.0, 10.0 ).DrawOutline( ol::Rgba::BLACK );

    // show the experience
    int xpRatio = ( hero->getAttribute( Character::EXPERIENCE ) - hero->getAttribute( Character::PREVIOUS_LEVEL_XP ) ) * 100
                    / ( hero->getAttribute( Character::NEXT_LEVEL_XP ) - hero->getAttribute( Character::PREVIOUS_LEVEL_XP ) );

    x = float( ( Settings::screenWidth - 100 ) / 2 );
    ol::Rect( x, 12.0, float(xpRatio), 10.0 ).Draw( xpCol );
    ol::Rect( x, 12.0, 100.0, 10.0 ).DrawOutline( ol::Rgba::BLACK );

    // show bomb count
    y = .0;
    x = 120.0;
    for ( int i = 0; i < hero->getAttribute( Character::BOMBS ); i++ )
    {
        bombIcon->BlitStretched( x, 6.0 + y, 20.0, 20.0 );
        if ( i & 1 )
        {
            x += 16.0;
            y = .0;
        }
        else
        {
            y = 14.0;
        }
    }

    // show frames per second

    //x = Settings::screenWidth - smallFont->FirstLineWidth( fps ) - 16.0;
    x = Settings::screenWidth - 64.0;
    smallFont->SetColor( ol::Rgba::WHITE );
    smallFont->Print( fps, int(x), 20 );

    ol::Rgba lCol( 255, 255, 255 );
    // show the level

    x = Settings::screenWidth / 2.0; //float( ( Settings::screenWidth - verySmallFont->FirstLineWidth( level ) ) / 2.0 );
    verySmallFont->SetColor( lCol );
    verySmallFont->Print( level, int(x), 20 );

    // show the life

    x = 68.0; //float( 68.0 - ( verySmallFont->FirstLineWidth( life ) / 2.0 ) );
    verySmallFont->SetColor( lCol );
    verySmallFont->Print( life, int(x), 20 );

    // show the mana

    x = 68.0; //float( 68.0 - (verySmallFont->FirstLineWidth( mana ) / 2.0 ) );
    verySmallFont->SetColor( lCol );
    verySmallFont->Print( mana, int(x), 35 );

}
