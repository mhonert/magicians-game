#ifndef MAP_H
#define MAP_H

#include "tilemanager.h"
#include "debug.h"

/**
 * a tile-map
 */
namespace game
{
    class World;

    class Map
    {
    	public:
    		// class constructor
    		Map( TileManager* pTiles );
    		// class destructor
    		~Map();
    		
    		/// draws the map
            void draw( float pX, float pY );
    	
            /// creates a new random map
            void create();
            
            inline int getMaxX() const { return maxX; }
            inline int getMaxY() const { return maxY; }
            
            /// loads a map from a bitmap
            void loadMap( const char* pFile, World* pWorld );
            
            /// returns the information, if the tile at pixel-position pX, pY is walkable
            /// pixel-position will be translated to map-coordinates
            bool isWalkable( int pX, int pY ) const;
            
            int getTileIdAt( int pX, int pY ) const;
            
            /// explodes the tile at the given position
            /// currently changes a rock to a broken rock
            void explodeTileAt( int pX, int pY );
            
    	private:
            /// loads all neccessary tiles
            void init();
            // clears the map
            void clear();

            /// corrects all errors on the map
            void correctMap();
            
            /// adds transitions to the map
            void smoothMap();
            
            /// adds different landscapes to the map
            void addLandscapes( int pCount, int pSize, int pId );

            /// calculates the visible tiles per screen and reserves memory
            /// for the map
            void prepareMap();
            
            TileManager* tiles;
            Tile** tilemap;
            Tile** tiletrans;
            Tile** tiletrans1;
            
            
            int width;
            int height;
            
            int tilesPerScrX;
            int tilesPerScrY;
            
            int maxX;
            int maxY;
            
    	
    };

}
#endif // MAP_H
