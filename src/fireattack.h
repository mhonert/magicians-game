#ifndef FIREATTACK_H
#define FIREATTACK_H

#include "attack.h" // inheriting class's header file
#include <OpenLayer.hpp>

/**
 * a fire attack ( throws a fireball )
 */
namespace game
{ 
 
    class FireAttack : public Attack
    {
    	public:
    		// class constructor
    		FireAttack();
    		// class destructor
    		virtual ~FireAttack();
    		
    		virtual Attack* clone() const;
    		
            virtual void aiAttack( Character* pDest, int pDistance, 
                                   int pDistX, int pDistY );

    		
    		virtual void playerAttack();  		
    };
}
#endif // FIREATTACK_H
