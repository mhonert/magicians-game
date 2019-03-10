#include <string>
    using namespace std;
#include "game.h"    
using namespace game;
#include <allegro.h>

int main() 
{
    Game game;
    game.run();
	return 0;
}
END_OF_MAIN()

// Checks whether the assertion (evaluated to pExpression) is true.
// Writes an error message and shows an error message dialog if the assertion is false.
bool HandleAssert( bool pExpression, const char* pDescription, int pLine, char* pFile )
{
    if ( ! pExpression )
    {
		char* error = new char[ strlen( pDescription ) + strlen( pFile ) + 256  ];
        
        sprintf
        ( 
            error, 
            "Error: \"%s\" \n in file: \"%s\" \n in line: \"%i\"",
            pDescription, pFile, pLine 
        );
        
        allegro_message( error );
        return true;
    }
    return false;
}
