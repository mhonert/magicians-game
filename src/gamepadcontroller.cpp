#include "gamepadcontroller.h"
#include <allegro.h>
#include "debug.h"

using namespace game;

GamepadController::GamepadController()
{
    //ctor
    for ( int i = 0; i < LAST_ENTRY_MARKER; i++ )
    {
        keyLockStatus[i] = false;
    }

    // try to install the joystick
    Guarantee ( install_joystick(JOY_TYPE_AUTODETECT) != 0, "gamepad could not be initialized!" );
}

GamepadController::~GamepadController()
{
    //dtor
    remove_joystick();
}

/// checks, if a key is pressed
bool GamepadController::isKeyPressed( EnumKeys pKey ) const
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
bool GamepadController::isKeyLocked( EnumKeys pKey ) const
{
    return keyLockStatus[pKey];
}

/// locks a key
void GamepadController::lockKey( EnumKeys pKey )
{
    keyLockStatus[pKey] = true;
}

/// checks, if a key is locked
void GamepadController::unlockKey( EnumKeys pKey )
{
    keyLockStatus[pKey] = false;
}

/// returns the chosen direction of the controller-device
Direction::EnumDirections GamepadController::getDirection() const
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


