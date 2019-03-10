#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include "abstractcontroller.h"

namespace game
{
    /// a concrete controller: the keyboard
    class KeyboardController : public AbstractController
    {
        public:
            KeyboardController();
            virtual ~KeyboardController();

            /// checks, if a key is pressed
            virtual bool isKeyPressed( EnumKeys pKey ) const;
            /// checks, if a key is locked
            virtual bool isKeyLocked( EnumKeys pKey ) const;
            /// locks a key
            virtual void lockKey( EnumKeys pKey );
            /// checks, if a key is locked
            virtual void unlockKey( EnumKeys pKey );
            /// returns the chosen direction of the controller-device
            virtual Direction::EnumDirections getDirection() const;
        protected:
            bool keyLockStatus[ LAST_ENTRY_MARKER ];
        private:
    };
}
#endif // KEYBOARDCONTROLLER_H
