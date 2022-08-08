#include "grid.h"

LGrid::LGrid(int w, int h)
{
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            int x = j * SQUARE_SIZE;
            int y = i * SQUARE_SIZE;
            position pos = {x, y};
            mSquares.push_back(pos);
        }
    }
}

LGrid::~LGrid()
{

}

void LGrid::showBarriers(SDL_Renderer* gRenderer)
{
    for(int i = 0; i < mBarriers.size(); i++)
    {
        mTexture.render(mBarriers[i].x*SQUARE_SIZE, mBarriers[i].y*SQUARE_SIZE, gRenderer);
    }
}

void LGrid::addBarrier(position pos)
{
    mBarriers.push_back(pos);
}

std::vector<position> LGrid::getBarriers()
{
    return mBarriers;
}

void LGrid::clearBarriers()
{
    mBarriers.clear();
}

bool LGrid::isInsideBarriers(int x, int y)
{
    for(int i = 0; i < mBarriers.size(); i++)
    {
        if(x == mBarriers[i].x && y == mBarriers[i].y)
        {
            return true;
        }
    }
    return false;
}

void LGrid::setTexture(SDL_Renderer *gRenderer)
{
    mTexture.loadFromFile("img/barrier.png", 32, 32, gRenderer);
}
