#ifndef INGAMECONTROL_H
#define INGAMECONTROL_H

#include <OpenLayer.hpp>

/**
 * controls the user input
 */
namespace game
{
    class Hero;
    class ResourceManager;
    class AbstractController;

    class InGameControl
    {
    	public:
    		// class constructor
    		InGameControl( ResourceManager* pResource, AbstractController* pController );
    		// class destructor
    		~InGameControl();

    		/// sets the hero
            void setHero( Hero* pHero );
            bool update( float pDelta );

            /// draws the "in-game-interface"
            void draw();

        private:
            Hero* hero;
            int curAttack;
            bool chooseAttack;
            float showAttacksCnt;
            ol::Bitmap* bombIcon;
            ol::Bitmap* attackIcon;
            ResourceManager* resource;
            ol::Rgba lifeCol[4];
            ol::Rgba manaCol[4];
            ol::Rgba xpCol[4];
            ol::TextRenderer* smallFont;
            ol::TextRenderer* verySmallFont;
            AbstractController* controller;

            float updateTextCnt;
            char fps[12];
            char level[32];
            char life[64];
            char mana[64];
    };

}
#endif // INGAMECONTROL_H
