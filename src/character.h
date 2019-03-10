#ifndef CHARACTER_H
#define CHARACTER_H

#include <OpenLayer.hpp>
#include "gameentity.h"
#include "resourcemanager.h"

#include "map.h"
#include "world.h"

/**
 * an abstract character in the game
 */
namespace game
{
    class World;

    class Character: public GameEntity
    {
    	public:
    		// class constructor
    		Character();

    		// class destructor
    		virtual ~Character();

            // character types
            enum
            {
                HERO = 0,
                EVIL_WIZARD = 1,
                GNOME = 2,
                BATTLE_MAGICIAN = 3,
                REPTILE = 4
            };
            /// change the characters direction
    		void changeDirection( int pDir );
    		/// switches moving on or off
    		inline void setMoving( bool pMoving )
    		{
                moving = pMoving;
            }

            /// loads the graphics of the character
            void loadGraphics( const char* pFile, ResourceManager* pResource );

            /// draws the character
            virtual void draw( float pOffsX, float pOffsY );

            /// updates the character
            virtual bool update( float pDelta );

            /// sets the speed of the character
            void setSpeed( float pSpeed );

            /// sets a reference to the game world
            void setWorld( World* pWorld )
            {
                world = pWorld;
            }

            virtual void getsAttacked( int pDamage, Character* pBy ) = 0;

            inline Character* getLastCollision() const
            {
                return lastCollision;
            }

            inline int getDirection() const { return direction; }

            // attributes
            enum
            {
                LIFE = 0,
                MAX_LIFE = 1,
                MANA = 2,
                MAX_MANA = 3,
                BOMBS = 4,
                EXPERIENCE = 5,
                XP_VALUE = 6,
                LEVEL = 7,
                NEXT_LEVEL_XP = 8,
                PREVIOUS_LEVEL_XP = 9,
                ATTRIBUTE_COUNT = 10
            };

            // gets an attribute
            inline int getAttribute( int pId ) const
            {
                Assert( pId >= 0 && pId < ATTRIBUTE_COUNT,
                        "invalid attribute ID!" );

                return attributes[ pId ];
            }

            // sets an attribute
            void setAttribute( int pId, int pValue );

            // increases an attribute value
            void incAttribute( int pId, int pValue );

            // decreases an attribute value
            // minimum is 0
            void decAttribute( int pId, int pValue );


            // must be called after setting the speed!
            inline void overwriteAnimSpeed( float pSpeed )
            {
                animSpeed = pSpeed;
            }

            void setParalysed( bool pValue )
            {
                if ( pValue )
                    paralysed++;
                else
                    paralysed--;
            }

        protected:
            void init();
            void clear();

            ol::Bitmap** bitmap;
            ol::Bitmap* curBitmap;
            float speed;
            float animCounter;
            int direction;
            bool moving;

            float animSpeed;

            int paralysed;

            float oldX;
            float oldY;
            bool isClone;

            World* world;
            Character* lastCollision;

            int attributes[ ATTRIBUTE_COUNT ];

    };

}
#endif // CHARACTER_H
