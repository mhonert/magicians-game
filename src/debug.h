#ifndef DEBUG_H
#define DEBUG_H

/**
 * The Assert macro will only be evaluated in debug mode.
 * Its purpose is to discover bugs (e.g. null checks).
 *
 * The Guarantee macro on the other hand will always be evaluated
 * and should be used to discover unexpected runtime errors (e.g.
 * if a user deletes an important configuration file).
 */

    // *** Enable debug mode:
    //#define _DEBUG_

    extern bool HandleAssert( bool, const char*, int, char* );
    #ifdef _DEBUG_
        #define Assert( expression, description ) \
            if ( HandleAssert( int(expression), description, __LINE__, __FILE__ ) ) \
            { \
                exit(-1);\
            }
    #else
        #define Assert( expression, description )
    #endif
    #define Guarantee( expression, description ) \
        if ( HandleAssert( int(expression), description, __LINE__, __FILE__ ) ) \
        { \
            exit(-1);\
        }
#endif
