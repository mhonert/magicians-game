#include "localize.h"

using namespace localization;

// Initialization of the static class members
TranslationMap Localize::Translations[256];
int Localize::Language = 0;


bool Localize::Init( const char* pFile )
{
    bool lReadSuccessful = true;
    try
    {
        XmlElement xml( pFile, "translation" );
    
        XmlElement languages( xml.getFirstChild( "languages" ) );
        XmlElement texts( xml.getFirstChild( "texts" ) );
        
        texts.iterateChildren( "text" );
        while ( texts.isNext() )
        {
            XmlElement text( texts.nextChild() );
            const char* code = text.getAttribute("code");
            
            text.iterateChildren( "language" );
            while( text.isNext() )
            {
                XmlElement language( text.nextChild() );
                int id = language.getAttributeInt( "id" );
                const char* translation = language.getValue();
                Translations[ id ][ code ] = strdup(translation);
            }
        }        
    }
    catch ( XmlException &e )
    {
        lReadSuccessful = false;
    }
    return lReadSuccessful;
}

void Localize::Clear()
{
    for ( int i = 0; i < 255; i++ )
    {
        for ( TranslationItor itor = Translations[i].begin();
              itor != Translations[i].end(); ++itor )
        {
            //delete itor->second;                
        }   
        Translations[i].clear(); 
    }
}
