#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include <map>
#include "resourcemanager.h"
/**
 * manages tiles
 */
namespace game
{

    class Tile;
    typedef std::multimap<int, Tile*> TileMap;
    typedef TileMap::iterator TileItor;
    typedef std::pair<int, Tile*> TilePair;

    class TileManager
    {
    	public:
    		// class constructor
    		TileManager( ResourceManager* pResourceManager );
    		// class destructor
    		~TileManager();
    		void clear();
            void begin( const char* pFile, int pPrecedence, bool pWalkable );
    		void addTransition( const char* pFile, int pPrecedence );
    		void end();
            
            Tile* getTile( int pId );
            Tile* getTile( int pFromPrecedence, int pToPrecedence, int pCorner, int pSide );
    		
        private:
            void init();
            
            TileMap tiles;    		
            int curPrecedence;
            bool curWalkable;
            
            ResourceManager* resources;
    };

}
#endif // TILEMANAGER_H
