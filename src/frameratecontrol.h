#ifndef FRAMERATECONTROL_H
#define FRAMERATECONTROL_H

#ifdef WIN32
    #define HIGH_PERFORMANCE_COUNTER
#endif
#ifdef WIN64
    #define HIGH_PERFORMANCE_COUNTER
#endif

#ifdef HIGH_PERFORMANCE_COUNTER
    #include <allegro.h>
    #include <winalleg.h>
#endif    

/**
 * controls the framerate
 */
namespace game
{

    class FrameRateControl
    {
    	public:
    		// class destructor
    		~FrameRateControl() {};

            
            static void Start( float pFPS );
            static float NewFrameStarted();
            inline static void UseHighPerformanceCounter( bool pValue )
            {
                highPerformanceCounter = pValue;
            }
            
            inline static float GetDeltaTime()
            {
                return deltaTime;
            }
            
            inline static float GetFps()
            {
                return fps;
            }
                
        private:
    		// class constructor
    		FrameRateControl() {};
    		
    		static bool highPerformanceCounter;
    		
    		static float deltaTime;
    		
    		static float expectedFPS;
    		
    		static float fps;
    		
    		static bool firstFrame;
    		
    		#ifdef HIGH_PERFORMANCE_COUNTER
                static LARGE_INTEGER counter; 
                static float frequency;   		
    		#endif
    };
}
#endif // FRAMERATECONTROL_H
