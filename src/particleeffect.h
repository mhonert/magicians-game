#ifndef PARTICLEEFFECT_H
#define PARTICLEEFFECT_H

/**
 * abstract particle effect
 */
namespace game
{

    class ParticleEffect
    {
    	public:
    		// class constructor
    		ParticleEffect() {}
    		// class destructor
    		virtual ~ParticleEffect() {}

            /// draws the particle effect
            virtual void draw( float pOffsX, float pOffsY ) = 0;
            
            /// updates the particle effect
            virtual bool update( float pDelta ) = 0;
    		
    };

}
#endif // PARTICLEEFFECT_H
