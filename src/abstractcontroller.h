#if !defined(ABSTRACTCONTROLLER_H)
#define ABSTRACTCONTROLLER_H

#include "direction.h"

namespace game
{
    /** abstract base class for all key-based controller-types (keyboard, gamepad, etc.)
     */
    class AbstractController
    {
        public:
            AbstractController();
            virtual ~AbstractController();

            /// possible keys
            enum EnumKeys
            {
                PREVIOUS,
                NEXT,
                EXIT,
                ACTION,
                LAST_ENTRY_MARKER
            };

            /// checks, if a key is pressed
            virtual bool isKeyPressed( EnumKeys pKey ) const = 0;
            /// checks, if a key is locked
            virtual bool isKeyLocked( EnumKeys pKey ) const = 0;
            /// locks a key
            virtual void lockKey( EnumKeys pKey ) = 0;
            /// checks, if a key is locked
            virtual void unlockKey( EnumKeys pKey ) = 0;
            /// returns the chosen direction of the controller-device
            virtual Direction::EnumDirections getDirection() const = 0;

        protected:
        private:
    };
}
#endif // ABSTRACTCONTROLLER_H
