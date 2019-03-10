#include "direction.h" // class's header file
    using namespace game;

float Direction::dirX[9];
float Direction::dirY[9];

int Direction::iDirX[9];
int Direction::iDirY[9];

void Direction::Init()
{
    iDirX[ DOWN ] = 0;
    iDirY[ DOWN ] = 1;

    iDirX[ UP ] = 0;
    iDirY[ UP ] = -1;

    iDirX[ RIGHT ] = 1;
    iDirY[ RIGHT ] = 0;

    iDirX[ LEFT ] = -1;
    iDirY[ LEFT ] = 0;
 
    iDirX[ UP_LEFT ] = -1;
    iDirY[ UP_LEFT ] = -1;    

    iDirX[ UP_RIGHT ] = 1;
    iDirY[ UP_RIGHT ] = -1; 

    iDirX[ DOWN_RIGHT ] = 1;
    iDirY[ DOWN_RIGHT ] = 1; 
    
    iDirX[ DOWN_LEFT ] = -1;
    iDirY[ DOWN_LEFT ] = 1;         
    
    iDirX[ NONE ] = 0;
    iDirY[ NONE ] = 0;    
    
    for ( int i = 0; i < 9; i++ )
    {
        float x = float( iDirX[i] );
        float y = float( iDirY[i] );
        if ( x != .0 && y != .0 )
        {
            x *= .75;
            y *= .75;
        }
        dirX[i] = x;
        dirY[i] = y;
    }
        
    
}

int Direction::InvertDir( int pDir )
{
    int lDir = NONE;
    switch ( pDir )
    {
        case DOWN:      lDir = UP; break;
        case UP:        lDir = DOWN; break;
        case RIGHT:     lDir = LEFT; break;
        case LEFT:      lDir = RIGHT; break;
        case UP_LEFT:   lDir = DOWN_RIGHT; break;
        case UP_RIGHT:  lDir = DOWN_LEFT; break;
        case DOWN_RIGHT:lDir = UP_LEFT; break;
        case DOWN_LEFT: lDir = UP_RIGHT; break;
    }
    return lDir;
}

