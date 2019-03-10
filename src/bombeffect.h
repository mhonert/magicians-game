#ifndef BOMBEFFECT_H
#define BOMBEFFECT_H

#include "particleeffect.h" // inheriting class's header file
#include <OpenLayer.hpp>

namespace game
{
    class World;
    class Particle;
    class Character;

    /**
     * Shows a bomb, which explodes after a few seconds
     */
    class BombEffect : public ParticleEffect
    {
    	public:
    		// class constructor
    		BombEffect( float pX, float pY, World* pWorld, Character* pOrigin, float pTime );
    		// class destructor
    		virtual ~BombEffect();

            /// draws the fire effect
            virtual void draw( float pOffsX, float pOffsY );

            /// updates the fire effect
            virtual bool update( float pDelta );

        private:
            Particle** particles;
            int initSize;
            float lifeTime;
            bool damaged;
            bool exploded;
            World* world;
            ol::Bitmap* bitmap;
            Character* origin;

            float x;
            float y;
    };

}
#endif // BOMBEFFECT_H
