#include "apple.h"

LApple::LApple(int x, int y)
{
    mX = x;
    mY = y;
}

LApple::~LApple(){
    mX = 0;
    mY = 0;
    mAppleTexture.free();
}

void LApple::setTexture(SDL_Renderer* gRenderer){
    mAppleTexture.loadFromFile("img/apple.png", 32, 32, gRenderer);
}

void LApple::show(SDL_Renderer* gRenderer){
    mAppleTexture.render(mX*32, mY*32, gRenderer);
}

void LApple::setCoords(int x, int y){
    mX = x;
    mY = y;
}

int LApple::getX(){
    return mX;
}

int LApple::getY(){
    return mY;
}

