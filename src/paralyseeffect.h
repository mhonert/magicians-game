#ifndef PARALYSEEFFECT_H
#define PARALYSEEFFECT_H

#include "particleeffect.h" // inheriting class's header file

/**
 * a paralyse effect
 */
namespace game
{
    class Character;
    class World;
    class Particle;

    class ParalyseEffect : public ParticleEffect
    {
        public:
            // class constructor
            ParalyseEffect( World* pWorld, float pX, float pY, int pDirection, float pParalyseTime, Character* pOrigin );
            // class destructor
            virtual ~ParalyseEffect();

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
            float paralyseTime;

            bool lifeEnd;

            Character* origin;
            Character* target;
            World* world;
    };

}
#endif // PARALYSEEFFECT_H

