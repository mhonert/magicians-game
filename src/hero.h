#ifndef HERO_H
#define HERO_H

#include "character.h" // inheriting class's header file

/**
 * a character controlled by the player ( the hero )
 */

#include <vector>

namespace game
{
    class Attack;
    typedef std::vector<Attack*> AttackVec;

    class Hero : public Character
    {
    	public:
    		/// class constructor
    		Hero();
    		/// class destructor
    		virtual ~Hero();

            /// clones the hero
            virtual GameEntity* clone();

    		/// updates the hero
            virtual bool update( float pDelta );

            /// will be called, when the hero gets attacked
            virtual void getsAttacked( int pDamage, Character* pBy );

            /// switches attacking on or off
    		inline void setAttacking( bool pAttacking )
    		{
                attacking = pAttacking;
            }

            /// return the current points of the hero
            inline int getPoints() const { return points; }

            /// increase the hero's points
            inline void increasePoints( int pValue )
            {
                points += pValue;
            }

            /// adds the ability for a certain attack
            void addAttack( Attack* pAttack );

            /// get all available attacks
            const AttackVec* getAttacks();

            /// chooses an attack from the possible attacks (getAttacks)
            void chooseAttack( int pIndex );

        private:

            int points;
            bool attacking;

            AttackVec attacks;
            Attack* attack;

    };

}
#endif // HERO_H
