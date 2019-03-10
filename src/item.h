#ifndef ITEM_H
#define ITEM_H

#include <OpenLayer.hpp>
#include "gameentity.h" // inheriting class's header file

/**
 * a item in the game
 */
namespace game
{
    class World;
    class ResourceManager;
    class ol::Bitmap;

    class Item : public GameEntity
    {
    	public:
    		Item();
    		~Item();

            enum EnumItems
            {
                HEART = 0,
                EXIT = 1,
                BOMB = 2,
                MANA = 3,
                CASE = 4
            };

            /// creates a clone of this item
            virtual GameEntity* clone();

            /// loads the graphic for this item
            void loadGraphics( const char* pFile, ResourceManager* pResource );

            virtual void draw( float pOffsX, float pOffsY );

            /// updates the object
            virtual bool update( float pDelta );

            void setWorld( World* pWorld )
            {
                world = pWorld;
            }

            inline void setType( int pValue )
            {
                type = pValue;
            }

            int getType() const { return type; }

            ol::Bitmap* getBitmap() const { return bitmap; }

        protected:
            World* world;
            ol::Bitmap* bitmap;
            int type;
    };
}

#endif // ITEM_H
