#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

/**
 * manages ressources like Allegro BITMAPS, etc.
 * ( currently very simple, without dynamic loading )
 */

#include <list>
#include <string>
#include "OpenLayer.hpp"
#include <allegro.h>
#include <map>
 
namespace game
{ 
    typedef std::list<BITMAP*> AllegroBitmapList;
    typedef AllegroBitmapList::iterator AllegroBitmapItor;
    
    typedef std::list<ol::Bitmap*> OlBitmapList;
    typedef OlBitmapList::iterator OlBitmapItor;
    
    typedef std::map<int, ol::Bitmap*> OlBitmapMap;
    
    typedef std::map<int, ol::TextRenderer*> OlTextRendererMap;
    typedef OlTextRendererMap::iterator OlTextRendererItor;

    class ResourceManager
    {
    	public:
    		// class constructor
    		ResourceManager();
    		// class destructor
    		~ResourceManager();
    		
    		// ol-bitmap resource-IDs
    		enum
    		{
                BOMB = 0   
            };
            
            // font resource-IDs
            enum
            {
                VERY_SMALL_FONT = 0,
                SMALL_FONT = 1,
                MEDIUM_FONT = 2,
                BIG_FONT = 3  
            };
    		
    		/// frees all objects ( can't be reloaded! )
            void clear();
            /// unloads all objects ( can later be reloaded )
    		void unload();
    		/// reloads all objects
    		void reload();
    		/// registers an Allegro Bitmap
            void manage( BITMAP* pBitmap );
            /// registers an OpenLayer Bitmap
            void manage( ol::Bitmap* pBitmap );
            
            /// registers an OpenLayer Bitmap by Id
            void remember( ol::Bitmap* pBitmap, int pId );
    		
    		/// gets an OpenLayer Bitmap by Id
    		ol::Bitmap* getOlBitmap( int pId );
    		
            /// registers an OpenLayer TextRenderer by Id
            void manage( ol::TextRenderer* pText, int pId );
    		
    		/// gets an OpenLayer TextRenderer by Id
    		ol::TextRenderer* getOlTextRenderer( int pId );    		
    	private:
            void init();
            
            AllegroBitmapList allegroBitmaps;
            OlBitmapList olBitmaps;	
            OlBitmapMap olBitmapMap;
            OlTextRendererMap olTextRendererMap;
    };
}

#endif // RESOURCEMANAGER_H
