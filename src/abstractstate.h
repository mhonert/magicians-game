#ifndef ABSTRACTSTATE_H
#define ABSTRACTSTATE_H

namespace game
{
    /// an abstract state
    class AbstractState
    {
        class GameEntity;

        public:
            /// standard constructor
            AbstractState();

            /// destructor
            virtual ~AbstractState();

            /// returns the unique name of the current state
            inline const char* getName() const { return actionName; }

            /// sets the GameEntity, to which this state belongs
            inline void setOwner( GameEntity* pOwner ) { belongsTo = pOwner; }

            /// gets the GameEntity, to which this state belongs
            inline GameEntity* getOwner() const { return belongsTo; }
        protected:
            GameEntity* belongsTo;
            const char* actionName;

        private:
    };

}

#endif // ABSTRACTSTATE_H
