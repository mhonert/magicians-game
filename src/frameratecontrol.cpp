#include "frameratecontrol.h" // class's header file
    using namespace game;
#include <OpenLayer.hpp>
    using namespace ol;


bool FrameRateControl::highPerformanceCounter = false;
float FrameRateControl::deltaTime = 1.0;
float FrameRateControl::expectedFPS = 70.0;
float FrameRateControl::fps = 70.0;
bool FrameRateControl::firstFrame = true;

#ifdef HIGH_PERFORMANCE_COUNTER
    LARGE_INTEGER FrameRateControl::counter;
    float FrameRateControl::frequency = .1;
#endif     

void FrameRateControl::Start( float pFPS )
{
    #ifdef HIGH_PERFORMANCE_COUNTER
        if ( ! highPerformanceCounter )
        {
            FpsCounter::Start( pFPS );
            return;
        }
        LARGE_INTEGER lFrequency;
        if ( ! QueryPerformanceFrequency( &lFrequency ) )
        {
            // can't use the high performance counter
            highPerformanceCounter = false;
            FpsCounter::Start( pFPS );
            return;
        }
        frequency = float( lFrequency.QuadPart );

        expectedFPS = pFPS;
        deltaTime = 1.0;    
        fps = expectedFPS;
        firstFrame = true;
    #else
        FpsCounter::Start( pFPS );   
    #endif
}

float FrameRateControl::NewFrameStarted()
{
    #ifdef HIGH_PERFORMANCE_COUNTER
        if ( ! highPerformanceCounter )
        {
            deltaTime = FpsCounter::NewFrameStarted();
            fps = FpsCounter::GetFps();
        }
        else
        {        
            if ( firstFrame )
            {    
                QueryPerformanceCounter( &counter );            
                firstFrame = false;
            }
            else
            {
                LARGE_INTEGER lCurCounter;
                QueryPerformanceCounter( &lCurCounter );
                float diff = float( lCurCounter.QuadPart - counter.QuadPart ) / frequency; 
                if ( diff == .0 )
                {
                    diff = .00001;
                    allegro_message( "!" );
                    exit(0);
                }
                fps = 1.0 / diff;
                deltaTime = expectedFPS / fps;  
                counter = lCurCounter;
            }
        }
    #else
        deltaTime = FpsCounter::NewFrameStarted();
        fps = FpsCounter::GetFps();        
    #endif    
    return deltaTime;
}


