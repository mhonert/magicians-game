#include "particlestack.h" // class's header file
    using namespace game;
#include "debug.h"

ParticleStack* ParticleStack::Instance = NULL; 

// class constructor
ParticleStack::ParticleStack( int pSize )
{
	initSize = pSize;
    for ( int i = 0; i < pSize; i++ )
	{
        particles.push_back( new Particle() );    
    }
}

// class destructor
ParticleStack::~ParticleStack()
{
    Assert( particles.size() == initSize, "not all particles have been released!" );
    Assert( Instance, "particle stack is not initialized!" );
	
    for ( int i = 0; i < particles.size(); i++ )
	   delete particles[i];
    particles.clear();

}


Particle* ParticleStack::getParticle()
{
    Assert( Instance, "particle stack is not initialized!" );
    Particle* ret;
    if ( Instance->particles.size() > 0 )
    {
        ret = Instance->particles.back();
        Instance->particles.pop_back();
    }
    else
    {
        ret = NULL;
    }
    return ret;
}

void ParticleStack::releaseParticle( Particle* pParticle )
{
    Instance->particles.push_back( pParticle );
}

void ParticleStack::Create( int pSize )
{
    Assert( Instance == NULL, "particle stack is already initialized!" );
    Instance = new ParticleStack( pSize );    
}

void ParticleStack::Destroy()
{
    Assert( Instance, "particle stack is not initialized!" );
    delete Instance;
    Instance = NULL;  
}

