#ifndef ATTACK_H
#define ATTACK_H

#include <OpenLayer.hpp>
/**
 * base-class for different attacks (e.g. fire, sword, ...)
 * contains methods for ai-characters and for the hero
 */
namespace game
{
    class Character;
    class World;
    class ResourceManager;

    class Attack
    {
    	public:
    		// class constructor
    		Attack();

    		// class destructor
    		virtual ~Attack();

    		// all attacks
    		enum EnumAttacks
    		{
                FIRE = 0,
                BOMB = 1,
                ENERGY = 2,
                PARALYSE = 3
            };

    		/// ai-character does an attack
            virtual void aiAttack( Character* pDest, int pDistance,
                                   int pDistX, int pDistY ) = 0;

            /// player does an attack
    		virtual void playerAttack() = 0;

    		virtual Attack* clone() const = 0;

    		/// sets the owner of this attack
            inline void setOwner( Character* pOwner )
            {
                owner = pOwner;
            }

            /// sets a reference to the game world
            inline void setWorld( World* pWorld )
            {
                world = pWorld;
            }

            /// updates the attack-counter
            inline void update( float pDelta )
            {
                if ( attackCounter > .0 )
                {
                    attackCounter -= pDelta;
                    if ( attackCounter < 0 )
                        attackCounter = .0;
                }
            }

            /// loads the icon from a file
            void loadIcon( const char* pFile, ResourceManager* pResource );

            /// gets the icon for this attack
            inline ol::Bitmap* getIcon() const
            {
                return bitmap;
            }

        protected:
            Character* owner;
            World* world;
            float attackCounter;
            ol::Bitmap* bitmap;
    };

}

#endif // ATTACK_H
