#ifndef XPEFFECT_H
#define XPEFFECT_H

#include "particleeffect.h" // inheriting class's header file

/**
 * shows the experience points the hero got for beating an enemy
 */
#include <OpenLayer.hpp>
 
namespace game
{ 
    class ResourceManager;
    class XpEffect : public ParticleEffect
    {
    	public:
    		// class constructor
    		XpEffect( float pX, float pY, int pValue, ResourceManager* pResource );
    		// class destructor
    		~XpEffect();
            /// draws the fire effect
            virtual void draw( float pOffsX, float pOffsY );
            
            /// updates the fire effect
            virtual bool update( float pDelta );  
            
        private:
            float x;
            float y;
            char text[16];
            float alpha;
            ol::TextRenderer* olTextRenderer;
    };
}


#endif // XPEFFECT_H
