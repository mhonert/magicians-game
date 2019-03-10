/** @description This class is used to make localization easy
 *  Class is static to allow direct access from all methods in the game.
 *  hint: You can use the macro "localize( code )" instead of
 *  "Localize::Get( code )"

 *  @author mhonert
 *  @version 1.0
 */

#ifndef LOCALIZE_H
#define LOCALIZE_H

#include "xmlelement.h"
#include "debug.h"

#define localize( code ) localization::Localize::Get( code )

#include <map>
#include <string>
namespace localization
{
    using namespace std;
    typedef map<string, const char*> TranslationMap;
    typedef TranslationMap::iterator TranslationItor;

    class Localize
    {
        public:
            ~Localize() {}

            /** reads the translation-map from an xml-file
             * @param pFile Name of the localization-XML-file
             * @returns false, if the language-file could not be read
             */
            static bool Init( const char* pFile );

            /// clears the translation map
            static void Clear();

            /** sets the active language ID
             * @param pID The ID of the language (no check for existance is performed!)
             */
            inline static void SetLanguage( int pID )
            {
                Language = pID;
            }

            /** gets a text, identified by the current language and the given code
             * @param pCode The code, which shall be localized
             * @return const char* The localized string
             */
            inline static const char* Get( const char* pCode )
            {
                Assert( Translations, "static member Translations is not initialized" );
                Assert( Translations[Language].find( pCode ) != Translations[Language].end(),
                        "translation for this code does not exist!" );
                return Translations[Language][ pCode ];
            }

        protected:
        private:
            // constructor is private, because this class does only contain
            // static methods and members
            Localize() {}

            // STL-map with all Translations (read from an XML-file)
            static TranslationMap Translations[256];
            // active language ID
            static int Language;


    };
}
#endif // LOCALIZE_H
