#include "actionowner.h"

#include "abstractaction.h"

using namespace game;

ActionOwner::ActionOwner()
{
    //ctor
}

ActionOwner::~ActionOwner()
{
    //dtor
}

/// adds a new action
void ActionOwner::addAction( AbstractAction* pAction )
{
    const char* lName = pAction->getName();
    Guarantee( actionMap.find( lName ) == actionMap.end(),
               "action does already exists!" );
    actionMap[ lName ] = pAction;
}

/// removes an existing action -> doesn't throw an error, when the action does not exist
void ActionOwner::removeAction( const char* pActionName )
{
    // only attempt to erase the action, when it exists
    if ( actionMap.find( pActionName ) != actionMap.end() )
    {
        actionMap.erase( pActionName );
    }
}


