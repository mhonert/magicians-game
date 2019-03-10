#include "game.h" // class's header file
    using namespace game;
#include <OpenLayer.hpp>
#include "debug.h"
#include "localize.h"
    using namespace localization;
#include "hero.h"
#include "camera.h"
#include <string>
    using namespace std;
#include "particlestack.h"
#include "FrameRateControl.h"
#include "direction.h"
#include "keyboardcontroller.h"


// class constructor
Game::Game()
{
    init();
}

// class destructor
Game::~Game()
{
    clear();
}

void Game::run()
{
    play();
    //menu();
}

void Game::play()
{
    world->create();
    inGameControl->setHero( world->getHero() );
    Hero* hero = world->getHero();
    bool running = true;
    float pDelta;
    FrameRateControl::Start( 70.0 );

    while ( running )
    {
        pDelta = FrameRateControl::NewFrameStarted();
        running = inGameControl->update( pDelta );

        // update the game world and see which events occur
        switch ( world->update( pDelta ) )
        {
            case World::HERO_DIED:
                running = false;
                break;

            case World::LEVEL_COMPLETED:
                world->create();
                continue;
                break;
        }

        // center the camera to the hero, if possible
        int lX = MID( 0,
                      int( hero->getX() ) - Settings::screenWidth / 2 + hero->getWidth() / 2,
                      int( world->getMaxX() ) );

        int lY = MID( 0,
                      int( hero->getY() ) - Settings::screenHeight / 2 + hero->getHeight() / 2,
                      int( world->getMaxY() ) );

        camera->setPosition( lX, lY );

        if ( Settings::saveEnergy )
            rest( 1 );

        world->draw( camera );
        inGameControl->draw();
        ol::Canvas::Refresh();
    }
    allegro_message( localize( "game over" ) );
}

void Game::menu()
{
    float pDelta;
    bool running = true;
    FrameRateControl::Start( 70.0 );

    while ( running )
    {
        pDelta = FrameRateControl::NewFrameStarted();

        int x = mouse_x;
        int y = mouse_y;

        if ( Settings::saveEnergy )
            rest( 2 );

        if ( mouse_b == 1 )
            running = false;

        ol::Canvas::Refresh();
    }


}

void Game::init()
{
    Guarantee( settings.load( "xml/settings.xml" ), "settings could not be loaded!" );
    Guarantee( Localize::Init( "xml/localize.xml" ), "localization-file could not be loaded!" );
    Localize::SetLanguage( settings.language );

    Guarantee( ol::Setup::SetupProgram( true, true ), "program initialization failed!" );
    Guarantee( ol::Setup::SetupScreen( settings.screenWidth, settings.screenHeight, settings.fullscreen ),
               "graphicmode could not be set up!" );
    ol::Settings::StoreMemoryBitmaps( false );
    ol::Settings::SetAntialiasing( Settings::antialiasing );
    FrameRateControl::UseHighPerformanceCounter( Settings::highPerformanceCounter );

    tiles = new TileManager( &gameRes );

    world = new World( &gameRes, tiles );

    controller = new KeyboardController();

    inGameControl = new InGameControl( &gameRes, controller );

    camera = new Camera();
    camera->setPosition( 0, 0 );

    ParticleStack::Create( int(10000.0 * Settings::particlePercent) );
    Direction::Init();
    // initiate the fonts
    ol::TextRenderer* lFont = new ol::TextRenderer( "fonts/verdana.ttf", 24, 24 );
    gameRes.manage( lFont, ResourceManager::BIG_FONT );

    lFont = new ol::TextRenderer( *lFont, 12, 12 );
    gameRes.manage( lFont, ResourceManager::SMALL_FONT );

    lFont = new ol::TextRenderer( *lFont, 10, 10 );
    gameRes.manage( lFont, ResourceManager::VERY_SMALL_FONT );
}

void Game::clear()
{
    delete camera;
    delete inGameControl;
    delete world;
    delete tiles;
    world = NULL;
    tiles = NULL;
    ParticleStack::Destroy();
    Localize::Clear();
}

