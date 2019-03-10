#include "settings.h" // class's header file
    using namespace game;
#include "xmlelement.h"
#include <string>
    using namespace std;

int Settings::screenWidth = 640;
int Settings::screenHeight = 480;
bool Settings::fullscreen = false;    
bool Settings::highPerformanceCounter = false;
int Settings::language = 0;
bool Settings::saveEnergy = false;
float Settings::particlePercent = 1.0;
bool Settings::antialiasing = false;

// class constructor
Settings::Settings()
{
}

// class destructor
Settings::~Settings()
{
}

bool Settings::load( const char* pFile )
{
    bool lReadSuccessful = true;
    try
    {
        XmlElement lXml( pFile, "settings" );
    
        XmlElement lScreen( lXml.getFirstChild( "screen" ) );
        XmlElement lLanguage( lXml.getFirstChild( "language" ) );
        XmlElement lPerformance( lXml.getFirstChild( "performance" ) );
        XmlElement lTiming( lXml.getFirstChild( "timing" ) );        
        
        screenWidth = lScreen.getAttributeInt( "width" );
        screenHeight = lScreen.getAttributeInt( "height" );
        fullscreen = strcmp( lScreen.getAttribute( "fullscreen" ), "yes" ) == 0;
        language = lLanguage.getAttributeInt( "id" );
        saveEnergy = strcmp( lPerformance.getAttribute( "saveEnergy" ), "yes" ) == 0;
        particlePercent = float( lPerformance.getAttributeInt( "particlePercent" ) ) / 100.0;
        highPerformanceCounter = strcmp( lTiming.getAttribute( "useHighPerformanceCounter" ), "yes" ) == 0;
        antialiasing = strcmp( lPerformance.getAttribute( "antialiasing" ), "yes" ) == 0;
        
        Guarantee( particlePercent > .0, "particle percent must be higher than 0%" );
    }
    catch ( XmlException &e )
    {
        lReadSuccessful = false;
    }
    return lReadSuccessful;
}

