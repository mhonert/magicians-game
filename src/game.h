#ifndef GAME_H
#define GAME_H

#include "settings.h"
#include "resourcemanager.h"
#include "tilemanager.h"
#include "world.h"
#include "ingamecontrol.h"

/**
 * the game object sets up the game world (including all technical aspects, like OpenLayer, Allegro, localization )
 */
namespace game
{
    class Camera;
    class AbstractController;

    class Game
    {
    	public:
    		// class constructor
    		Game();
    		// class destructor
    		~Game();

            /// starts the game
    		void run();

        private:
            /// initializes the game (sets up the graphic mode, etc.)
            void init();
            /// clears all data used by the game
            void clear();

            void play();

            void menu();

            Settings settings;
            ResourceManager gameRes;
            ResourceManager menuRes;
            TileManager* tiles;
            World* world;
            InGameControl* inGameControl;
            AbstractController* controller;
            Camera* camera;

    };
}
#endif // GAME_H
