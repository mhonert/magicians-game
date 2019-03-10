#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

namespace game
{
    /// an abstract action
    class AbstractAction
    {
        class GameEntity;

        public:
            /// standard constructor
            AbstractAction();

            /// destructor
            virtual ~AbstractAction();

            /// returns the unique name of the current action
            inline const char* getName() const { return actionName; }

            /// sets the GameEntity, to which this action belongs
            inline void setOwner( GameEntity* pOwner ) { belongsTo = pOwner; }

            /// gets the GameEntity, to which this action belongs
            inline GameEntity* getOwner() const { return belongsTo; }
        protected:
            GameEntity* belongsTo;
            const char* actionName;

        private:
    };

}
#endif // ABSTRACTACTION_H
