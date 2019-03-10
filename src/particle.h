#ifndef PARTICLE_H
#define PARTICLE_H

/**
 * a particle for a particle effect ( e.g. explosion, magic, fire )
 */

#include <OpenLayer.hpp>

namespace game
{

    class Particle
    {
    	public:
    		// class constructor
    		Particle() {}
    		// class destructor
    		~Particle() {}
 
            inline void draw( float pOffsX, float pOffsY ) const
            {
                ol::Circle( ol::Vec2D( x - pOffsX, y - pOffsY ), size, 1.0, .3 ).Draw( color );
            }

            float x;
            float y;
            float life;
            float size;
            float dirX;
            float dirY;
            ol::Rgba color;
    };

}

#endif // PARTICLE_H
