#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "core.h"

class LTexture
{
    public:
        LTexture();
        ~LTexture();
        bool loadFromFile(std::string path, int w, int h, SDL_Renderer* gRenderer);
        void free();
        void render(int x, int y, SDL_Renderer* gRenderer);

        int getWidth();
        int getHeight();

    private:
        SDL_Texture* mTexture;

        int mWidth;
        int mHeight;

};
#endif
