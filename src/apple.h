#include "textures.h"
#ifndef APPLE_H
#define APPLE_H
class LApple
{
    public:
        LApple(int x, int y);
        ~LApple();
    
        void setTexture(SDL_Renderer* gRenderer);
        void setCoords(int x, int y);
        void show(SDL_Renderer* gRenderer);

        int getX();
        int getY();
    private:
        int mX;
        int mY;
        LTexture mAppleTexture;
};
#endif
