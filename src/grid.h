#ifndef GRID_H
#define GRID_H
#include "textures.h"
#include "core.h"
#include <vector>

class LGrid
{
    public:
        LGrid(int w, int h);
        ~LGrid();
        void addBarrier(position pos);
        void showBarriers(SDL_Renderer* gRenderer);
        std::vector<position> getBarriers();
        void clearBarriers();
        bool isInsideBarriers(int x, int y);
        void setTexture(SDL_Renderer *gRenderer);
    private:
        std::vector<position> mSquares;
        std::vector<position> mBarriers;
        LTexture mTexture;
};

#endif