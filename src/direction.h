#ifndef DIRECTION_H
#define DIRECTION_H


namespace game
{
    /**
     * stores the direction-information
     */
    class Direction
    {
    	public:
    		// class destructor
    		~Direction() {};

    		// directions
            enum EnumDirections
    		{
                DOWN        = 0,
                DOWN_RIGHT  = 1,
                RIGHT       = 2,
                UP_RIGHT    = 3,
                UP          = 4,
                UP_LEFT     = 5,
                LEFT        = 6,
                DOWN_LEFT   = 7,
                NONE        = 8,
                DIR_COUNT   = 8,
            };

            static void Init();

            static int InvertDir( int pDir );

      		static float dirX[9];
    		static float dirY[9];

    		static int iDirX[9];
    		static int iDirY[9];

        private:
    		// class constructor
    		Direction() {};



    };

}
#endif // DIRECTION_H
