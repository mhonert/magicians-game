#ifndef ENEMY_H
#define ENEMY_H

#include "character.h" // inheriting class's header file

/**
 * a computer-controlled character
 */
 
namespace game
{
    class Attack; 
    
    class Enemy: public Character
    {
    	public:
    		// class constructor
    		Enemy();

    		// class destructor
    		virtual ~Enemy();

            // creates a clone of this enemy
            virtual GameEntity* clone();
            
            virtual void draw( float pOffsX, float pOffsY );            
    		
    		/// updates the enemy
            virtual bool update( float pDelta );
            
            virtual void getsAttacked( int pDamage, Character* pBy ); 
            
            /// sets the current attack of this enemy
            /// an enemy can only have one attack
            void setAttack( Attack* pAttack );
            
        private:
            void turnToOptimalDirection( int pDistX, int pDistY );
            
            float rethinkCnt;
            
            bool dies;
            
            float dieCounter;
            float alpha;
            
            Attack* attack;
   
    };

}

#endif // ENEMY_H
