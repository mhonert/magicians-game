#ifndef PARALYSEATTACK_H
#define PARALYSEATTACK_H

#include "attack.h" // inheriting class's header file
#include <OpenLayer.hpp>

/**
 * a paralyse attack ( paralyses a character )
 */
namespace game
{

    class ParalyseAttack : public Attack
    {
        public:
            // class constructor
            ParalyseAttack();
            // class destructor
            virtual ~ParalyseAttack();

            virtual Attack* clone() const;

            virtual void aiAttack( Character* pDest, int pDistance,
                                   int pDistX, int pDistY );


            virtual void playerAttack();
    };
}
#endif // PARALYSEATTACK_H

