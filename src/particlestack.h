#ifndef PARTICLESTACK_H
#define PARTICLESTACK_H

#include "particle.h"
#include <vector>

/*
 * stores particles to optimize memory management
 */
namespace game
{
    typedef std::vector<Particle*> ParticleVec;

    class ParticleStack
    {
    	public:

    		// class destructor
    		~ParticleStack();
    		
    		/// returns a particle
            static Particle* getParticle();
            
            /// releases a particle
            static void releaseParticle( Particle* pParticle );
    		
    		static void Create( int pSize );
    		static void Destroy();
    		
        private:
    		/// class constructor
    		/// @param pSize The maximum particle count
    		ParticleStack( int pSize );            
            
            ParticleVec particles; 
            int initSize;
            
            static ParticleStack* Instance; 
    };

}
#endif // PARTICLESTACK_H
