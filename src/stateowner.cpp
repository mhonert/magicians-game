#include "stateowner.h"
#include "abstractstate.h"

using namespace game;

StateOwner::StateOwner()
{
    //ctor
}

StateOwner::~StateOwner()
{
    //dtor
}

/// adds a new state
void StateOwner::addState( AbstractState* pState )
{
    const char* lName = pState->getName();
    Guarantee( stateMap.find( lName ) == stateMap.end(),
               "state does already exists!" );
    stateMap[ lName ] = pState;
}

/// removes an existing state -> doesn't throw an error, when the state does not exist
void StateOwner::removeState( const char* pStateName )
{
    // only attempt to erase the action, when it exists
    if ( stateMap.find( pStateName ) != stateMap.end() )
    {
        stateMap.erase( pStateName );
    }
}



