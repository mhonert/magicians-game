#ifndef LEVELUPEFFECT_H
#define LEVELUPEFFECT_H

#include "particleeffect.h" // inheriting class's header file

#include <OpenLayer.hpp>
/**
 * effect, when the hero levels up
 */
namespace game
{
    class ResourceManager;
    
    class LevelUpEffect : public ParticleEffect
    {
    	public:
    		// class constructor
    		LevelUpEffect( float pX, float pY, ResourceManager* pResource );
    		// class destructor
    		~LevelUpEffect();
            /// draws the fire effect
            virtual void draw( float pOffsX, float pOffsY );
            
            /// updates the fire effect
            virtual bool update( float pDelta );  
            
        private:
            float x;
            float y;
            char text[32];
            float alpha;
            ol::TextRenderer* olTextRenderer;
    };

}
#endif // LEVELUPEFFECT_H
