#ifndef WORLD_H
#define WORLD_H

/**
 * contains all game-objects (like the map, characters, items)
 */

#include "resourcemanager.h"
#include "tilemanager.h"
#include <list>
#include <map>
#include "debug.h"

namespace game
{

    class Character;
    class Hero;
    class Camera;
    class ParticleEffect;
    class Item;
    class Map;
    class Attack;

    typedef std::list<Character*> CharacterList;
    typedef CharacterList::iterator CharacterItor;

    typedef std::map<int, Character*> CharacterMap;
    typedef CharacterMap::iterator CharacterMapItor;

    typedef std::list<ParticleEffect*> ParticleList;
    typedef ParticleList::iterator ParticleItor;

    typedef std::map<int, Item*> ItemMap;
    typedef ItemMap::iterator ItemMapItor;

    typedef std::list<Item*> ItemList;
    typedef ItemList::iterator ItemItor;

    typedef std::map<int, Attack*> AttackMap;
    typedef AttackMap::iterator AttackMapItor;

    class World
    {
    	public:
    		// class constructor
    		World( ResourceManager* pResources, TileManager* pTiles );
    		// class destructor
    		~World();

            // EVENTS
            enum EnumWorldEvents
            {
                NOTHING         = 0,
                HERO_DIED       = 1,
                LEVEL_COMPLETED = 2
            };

            /// creates a new game-world (loads the map, adds characters and items)
            void create();
            void draw( Camera* pCamera );

            /// returns the id of an event, which occured
            /// ( e.g. when the hero dies )
            EnumWorldEvents update( float pDelta );

            inline Hero* getHero() const { return hero; }

            int getMaxX() const;
            int getMaxY() const;

            inline Map* getMap() const
            {
                Assert( tilemap, "tilemap is not initialized!" );
                return tilemap;
            }

            inline CharacterList* getCharacter() const
            {
                return const_cast<CharacterList*>( &character );
            }

            void addParticleEffect( ParticleEffect* pEffect );

            /// adds a character to the game world
            void createCharacter( int pId, int pX, int pY );

            /// adds an item to the game world
            void createItem( int pId, int pX, int pY );

            void levelCompleted();

            inline ResourceManager* getResourceManager() const
            {
                return resources;
            }

            /// creates a new attack
            Attack* createAttack( int pId );

        private:
            /// loads all resources, the character-repository, etc.
    		void init();
    		/// clears all resources
    		void clear();
    		/// clears all repositories and resets the map
    		void resetObjects();

    		ResourceManager* resources;
    		TileManager* tiles;

    		CharacterMap characterRepository;
    		ItemMap itemRepository;
    		AttackMap attackRepository;

    		Hero* hero;
    		Map* tilemap;
    		CharacterList character;
    		ItemList items;
    		ParticleList particles;

    		bool levelComplete;
    };

}
#endif // WORLD_H
