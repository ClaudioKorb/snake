#include "snake.h"

LSnake::LSnake(int x, int y)
{
    mHeadX = x;
    mHeadY = y;
    mDirection = LEFT;
    LSnakePiece head(mHeadX, mHeadY);
    mBody.push_back(head);
}

LSnake::~LSnake()
{
    mHeadX = 0;
    mHeadY = 0;
    mBodyTexture.free();
}

void LSnake::setTexture(SDL_Renderer *gRenderer)
{
    mBodyTexture.loadFromFile("img/snake.png", 32, 32, gRenderer);
}

void LSnake::show(SDL_Renderer *gRenderer)
{
    for(int i = 0; i < mBody.size(); i++)
    {
        mBodyTexture.render(mBody[i].getX()*32, mBody[i].getY()*32, gRenderer);
    }
}

bool LSnake::move(int ticks)
{
    int newX = mHeadX;
    int newY = mHeadY;

    if(ticks == 3)
    {
        switch (mDirection)
        {   
            case UP:
                newY = mHeadY - 1;
                break;
            case RIGHT: //RIGHT
                newX = mHeadX + 1;
                break;
            case DOWN: //DOWN
                newY = mHeadY + 1;
                break;
            case LEFT: //LEFT
                newX = mHeadX - 1;      
                break;
            default:
                break;

        }

        for(int i = mBody.size(); i >= 1; i--)
        {
            mBody[i].move(mBody[i-1].getX(), mBody[i-1].getY());
        }

        mBody[0].move(newX, newY);
        mHeadX = mBody[0].getX();
        mHeadY = mBody[0].getY();
        canChange = true;
        return true;
    }

    return false;

}

void LSnake::changeDir(direction dir)
{
    if(!canChange) return;
    switch (dir)
    {
        case UP:
            if(mDirection == DOWN) return;
            break;
        case LEFT:
            if(mDirection == RIGHT) return;
            break;
        case RIGHT:
            if(mDirection == LEFT) return;
            break;
        case DOWN:
            if(mDirection == UP) return;
            break;
        default:
            break;
    }
    mDirection = dir;
    canChange = false;

}


bool LSnake::checkEat(LApple *apple)
{
    if(apple->getX() == mHeadX && apple->getY() == mHeadY)
    {
        eat();
        return true;
    }
    return false;
}

void LSnake::eat()
{
    LSnakePiece newPiece(mBody.back().getX(), mBody.back().getY());
    mBody.push_back(newPiece);
}

bool LSnake::checkCollision()
{
    if(mHeadX == -1 || mHeadY == -1 || mHeadX == 20 || mHeadY == 15)
    {
        return true;
    }
    
    if(mBody.size() < 3) return false;
    
    for(int i = 1; i < mBody.size(); i++)
    {
        if(mHeadX == mBody[i].getX() && mHeadY == mBody[i].getY())
        {
            return true;
        }
    }


    return false;
}

bool LSnake::inside(int x, int y)
{
    for(int i = 0; i < mBody.size(); i++)
    {
        if(x == mBody[i].getX() && y == mBody[i].getY())
        {
            return true;
        }
    }
    return false;
}

int LSnake::getSize()
{
    return mBody.size();
}


LSnakePiece::LSnakePiece(int x, int y)
{
    mX = x;
    mY = y;
}

LSnakePiece::~LSnakePiece()
{

}

int LSnakePiece::getX()
{
    return mX;
}

int LSnakePiece::getY()
{
    return mY;
}

void LSnakePiece::move(int x, int y)
{
    mX = x;
    mY = y;
}
