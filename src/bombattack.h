#ifndef BOMBATTACK_H
#define BOMBATTACK_H

#include "attack.h" // inheriting class's header file
#include <OpenLayer.hpp>

/**
 * // attacking with bombs
 */
namespace game
{

    class BombAttack : public Attack
    {
    	public:
    		// class constructor
    		BombAttack();
    		// class destructor
    		~BombAttack();
    		
    		virtual Attack* clone() const;
    		
            virtual void aiAttack( Character* pDest, int pDistance, 
                                   int pDistX, int pDistY );

    		
    		virtual void playerAttack();     		
    };

}
#endif // BOMBATTACK_H
