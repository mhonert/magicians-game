#include "keyboardcontroller.h"
#include <allegro.h>

using namespace game;

KeyboardController::KeyboardController()
{
    //ctor
    for ( int i = 0; i < LAST_ENTRY_MARKER; i++ )
    {
        keyLockStatus[i] = false;
    }
}

KeyboardController::~KeyboardController()
{
    //dtor
}

/// checks, if a key is pressed
bool KeyboardController::isKeyPressed( EnumKeys pKey ) const
{
    switch ( pKey )
    {
        case PREVIOUS:
            return key[KEY_A];
        case NEXT:
            return key[KEY_D];
        case ACTION:
            return key[KEY_LSHIFT];
        case EXIT:
            return key[KEY_ESC];
    }
    return false;
}

/// checks, if a key is locked
bool KeyboardController::isKeyLocked( EnumKeys pKey ) const
{
    return keyLockStatus[pKey];
}

/// locks a key
void KeyboardController::lockKey( EnumKeys pKey )
{
    keyLockStatus[pKey] = true;
}

/// checks, if a key is locked
void KeyboardController::unlockKey( EnumKeys pKey )
{
    keyLockStatus[pKey] = false;
}

/// returns the chosen direction of the controller-device
Direction::EnumDirections KeyboardController::getDirection() const
{
    Direction::EnumDirections lDir = Direction::NONE;
    if ( key[KEY_UP] )
    {
        if ( key[KEY_LEFT] )
            lDir = Direction::UP_LEFT;
        else if ( key[KEY_RIGHT] )
            lDir = Direction::UP_RIGHT;
        else
            lDir = Direction::UP;
    }
    else if ( key[KEY_DOWN] )
    {
        if ( key[KEY_LEFT] )
            lDir = Direction::DOWN_LEFT;
        else if ( key[KEY_RIGHT] )
            lDir = Direction::DOWN_RIGHT;
        else
            lDir = Direction::DOWN;
    }
    else if ( key[KEY_LEFT] )
    {
        lDir = Direction::LEFT;
    }
    else if ( key[KEY_RIGHT] )
    {
        lDir = Direction::RIGHT;
    }
    return lDir;
}
