#ifndef TILE_H
#define TILE_H

#include <OpenLayer.hpp>

/**
 * a tile is part of the map
 */
namespace game
{

    class Tile
    {
    	public:
    		// class constructor
    		Tile( ol::Bitmap* pBitmap, bool pWalkable, int pId );
    		// class destructor
    		~Tile();
    		
            // the different tile-types
            enum 
            {
                WATER   = 0,
                SAND    = 1,
                GRASS   = 2,
                ROCK    = 3,
                MAX_LANDSCAPE   = 16,
                // special tiles
                BROKEN_ROCK     = 17
            };    		
    		
    		/// draws the tile
            void draw( float pX, float pY ) const;
    		/// @returns true, if the tile is walkable
            inline bool isWalkable() const { return walkable; }
    		
    		inline int getId() const { return id; }
    		
    		void drawFast( float pX, float pY ) const;
    		
        private:
            ol::Bitmap* bitmap;
            bool walkable;    
            int id;		
    };

}
#endif // TILE_H
