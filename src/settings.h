#ifndef SETTINGS_H
#define SETTINGS_H

/**
 * reads the current settings from an xml-file
 */

namespace game
{

    class Settings
    {
    	public:
    		Settings();
    		~Settings();

            static int screenWidth;
            static int screenHeight;
            static bool fullscreen;
            static bool highPerformanceCounter;
            static bool antialiasing;
            static bool saveEnergy;  
            static int language;
            static float particlePercent;
        
            bool load( const char* pFile );
    };

}

#endif // SETTINGS_H
