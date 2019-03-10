#ifndef ENERGYATTACK_H
#define ENERGYATTACK_H

#include "attack.h" // inheriting class's header file
#include <OpenLayer.hpp>

/**
 * an energy attack ( throws an energyball )
 */
namespace game
{

    class EnergyAttack : public Attack
    {
        public:
            // class constructor
            EnergyAttack();
            // class destructor
            virtual ~EnergyAttack();

            virtual Attack* clone() const;

            virtual void aiAttack( Character* pDest, int pDistance,
                                   int pDistX, int pDistY );


            virtual void playerAttack();
        private:
            bool secondAttack;            
    };
}
#endif // ENERGYATTACK_H

