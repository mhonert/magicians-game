#ifndef FIREBULLET_H
#define FIREBULLET_H

#include "particleeffect.h" // inheriting class's header file

/**
 * a fire bullet
 */
namespace game
{
    class Character;
    class World;
    class Particle;
    
    class FireBullet : public ParticleEffect
    {
    	public:
    		// class constructor
    		FireBullet( World* pWorld, float pX, float pY, int pDirection, float pLife, Character* pOrigin );
    		// class destructor
    		virtual ~FireBullet();
    		
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
#endif // FIREBULLET_H
