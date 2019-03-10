#ifndef ENERGYBULLET_H
#define ENERGYBULLET_H

#include "particleeffect.h" // inheriting class's header file

/**
 * an energy bullet
 */
namespace game
{
    class Character;
    class World;
    class Particle;

    class EnergyBullet : public ParticleEffect
    {
        public:
            // class constructor
            EnergyBullet( World* pWorld, float pX, float pY, int pDirection, float pLife, Character* pOrigin );
            // class destructor
            virtual ~EnergyBullet();

            /// draws the fire effect
            virtual void draw( float pOffsX, float pOffsY );

            /// updates the fire effect
            virtual bool update( float pDelta );
        protected:

            Particle** particles;
            int initSize;

            float x;
            float y;
            float speed;
            int direction;
            float dirX;
            float dirY;
            float life;

            bool lifeEnd;

            Character* origin;
            World* world;
    };

}
#endif // ENERGYBULLET_H
