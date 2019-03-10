#ifndef ACTIONOWNER_H
#define ACTIONOWNER_H

#include "debug.h"
#include <string>
#include <map>

namespace game
{
    class AbstractAction;
    typedef std::map<const char*, AbstractAction*> AbstractActionMap;

    /// the ActionOwner can contain/use many Actions (AbstractAction)
    class ActionOwner
    {
        public:
            ActionOwner();
            virtual ~ActionOwner();

            /// checks, if the action is available
            inline bool hasAction( const char* pActionName ) const
            {
                return actionMap.find( pActionName ) != actionMap.end();
            }

            /// adds a new action
            void addAction( AbstractAction* pAction );

            /// returns an action
            inline AbstractAction* getAction( const char* pActionName )
            {
                Assert( actionMap.find( pActionName ) != actionMap.end(),
                        "getAction: action does not exist!" );
                return actionMap[ pActionName ];
            }

            void removeAction( const char* pActionName );

        protected:
            AbstractActionMap actionMap;
        private:
    };

}
#endif // ACTIONOWNER_H
