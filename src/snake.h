#ifndef SNAKE_H
#define SNAKE_H

#include "core.h"
#include "textures.h"
#include "apple.h"
#include <vector>

class LSnakePiece{
    public:
        LSnakePiece(int x, int y);
        ~LSnakePiece();
        void move(int x, int y);
        int getX();
        int getY();
    private:
        int mX;
        int mY;
};

class LSnake
{
    public:
        LSnake(int x, int y);
        ~LSnake();
        
        bool move(int ticks);
        void changeDir(direction dir);

        bool checkEat(LApple *apple);
        void eat();
        bool checkCollision(std::vector<position> barriers);
        bool inside(int x, int y);
        
        void setTexture(SDL_Renderer *gRenderer);
        void show(SDL_Renderer* gRenderer);

        int getSize();
        
    private:
        std::vector<LSnakePiece> mBody;
        int mHeadX;
        int mHeadY;
        bool canChange;
        direction mDirection;
        LTexture mBodyTexture;
};
#endif
