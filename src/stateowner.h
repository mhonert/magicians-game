#ifndef STATEOWNER_H
#define STATEOWNER_H

#include <map>
#include "debug.h"

namespace game
{
    class AbstractState;
    typedef std::map<const char*, AbstractState*> AbstractStateMap;

    /// the StateOwner can contain/use many Actions (AbstractState)
    class StateOwner
    {
        public:
            StateOwner();
            virtual ~StateOwner();

            /// checks, if the state is available
            inline bool hasState( const char* pStateName ) const
            {
                return stateMap.find( pStateName ) != stateMap.end();
            }

            /// adds a new state
            void addState( AbstractState* pState );

            /// returns a state
            inline AbstractState* getState( const char* pStateName )
            {
                Assert( stateMap.find( pStateName ) != stateMap.end(),
                        "getState: state does not exist!" );
                return stateMap[ pStateName ];
            }

            void removeState( const char* pStateName );

        protected:
            AbstractStateMap stateMap;
        private:
    };

}

#endif // STATEOWNER_H
