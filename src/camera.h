#ifndef CAMERA_H
#define CAMERA_H

namespace game
{
    /**
     * stores the camera-position
     */
    class Camera
    {
    	public:
    		// class constructor
    		Camera();
    		// class destructor
    		~Camera();

            inline float getX() const { return x; }
            inline float getY() const { return y; }

            inline void setPosition( int pX, int pY )
            {
                x = pX;
                y = pY;
            }

        private:
            float x;
            float y;
    };

}
#endif // CAMERA_H
