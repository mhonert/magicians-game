#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "actionowner.h"
#include "stateowner.h"

/**
 * abstract base-class for characters and items
 */
namespace game
{

    struct BoundingBox
    {
        int offsetLeft;
        int offsetTop;
        int offsetRight;
        int offsetBottom;
    };

    class GameEntity: public ActionOwner, public StateOwner
    {
    	public:
            GameEntity();

            virtual ~GameEntity();

            // returns a clone of this object
            virtual GameEntity* clone() = 0;

            /// draws the object relative to the given offset
            virtual void draw( float pOffsX, float pOffsY ) = 0;
            /// updates the object
            virtual bool update( float pDelta ) = 0;
            /// checks for collisions
            virtual bool collides( GameEntity* pOpponent );

            /// sets the object's position
            inline void setPosition( float pX, float pY )
            {
                x = pX;
                y = pY;
            }

            inline float getX() const { return x; }
            inline float getY() const { return y; }
            inline int getWidth() const { return width; }
            inline int getHeight() const { return height; }

            inline int getLeft() const { return int(x) + box.offsetLeft; }
            inline int getTop() const { return int(y) + box.offsetTop; }
            inline int getRight() const { return int(x) + width - box.offsetRight; }
            inline int getBottom() const { return int(y) + height - box.offsetBottom; }


            inline int getCenterX() const { return ( getLeft() + getRight() ) / 2; }
            inline int getCenterY() const { return ( getTop() + getBottom() ) / 2; }

            void setBoundingBox( int pOffsetLeft, int pOffsetTop,
                                 int pOffsetRight, int pOffsetBottom )
            {
                box.offsetLeft = pOffsetLeft;
                box.offsetTop = pOffsetTop;
                box.offsetRight = pOffsetRight;
                box.offsetBottom = pOffsetBottom;
            }

            /** the possible states of this object:
             *  ACTIVE   -> actions can be invoked
             *  INACTIVE -> calls to actions will be ignored
             *  DELETED  -> actions can be removed
             */
            enum OwnerStateEnum
            {
                ACTIVE,
                INACTIVE,
                DELETED
            };

            /// returns the state of this object
            inline OwnerStateEnum getOwnerState() const { return ownerState; }

        protected:
            float x;
            float y;
            int width;
            int height;
            bool isClone;

            OwnerStateEnum ownerState;

            BoundingBox box;

    };


    class SortGameEntitiesByY
    {
        public:
            inline bool operator()( GameEntity *a, GameEntity *b ) const
            {
                return a->getBottom() < b->getBottom();
            }
    };
}
#endif // GAMEENTITY_H
