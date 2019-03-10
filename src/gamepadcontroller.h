#ifndef GAMEPADCONTROLLER_H
#define GAMEPADCONTROLLER_H

#include "abstractcontroller.h"

namespace game
{
    /// a concrete controller: the gamepad
    class GamepadController : public AbstractController
    {
        public:
            GamepadController();
            virtual ~GamepadController();
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
    };
}
#endif // GAMEPADCONTROLLER_H
