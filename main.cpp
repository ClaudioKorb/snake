#include <vector>
#include "src/textures.h"
#include "src/apple.h"
#include "src/snake.h"
#include "src/timer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 15;
const int SQUARE_SIZE = 32;
int SCREEN_FPS = 30;
int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

//Function to init SDL
bool init();

//Function used to load images and other media
bool loadMedia();

//Function used to quit SDL and free memory
void close();

bool validPosition(int x, int y);

//Function used to load textures
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

LTexture gBackgroundTexture;
LTexture gGameOverTexture;

LApple* gApple = new LApple((rand() % GRID_WIDTH - 1), (rand() % GRID_HEIGHT - 1));
LSnake* gSnake = new LSnake(10, 10);

bool init(){
    bool success = true;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0){
        printf("SDL couldn't initialize. SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else{
        if( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") ){
            printf("Warning: Linear texture filtering not enabled!\n");
        }

        //Creating window
        gWindow = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(!gWindow){
            printf("Could not create window. SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else{
            //Creating renderer
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(!gRenderer){
                printf("Could not create renderer. SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else{
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if( !(IMG_Init(imgFlags) & imgFlags) ){
                    printf("SDL_image could not initialize. SDL Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia(){
    bool success = true;
    gApple->setTexture(gRenderer);
    gSnake->setTexture(gRenderer);
    if( !gBackgroundTexture.loadFromFile("img/background.png", NULL, NULL, gRenderer) ){
        printf("Failed to load background texture image\n");
        success = false;
    }

    if( !gGameOverTexture.loadFromFile("img/game_over.png", NULL, NULL, gRenderer) ){
        printf("Failed to load game over image\n");
        success = false;
    }

    return success;
}

void close(){

    gBackgroundTexture.free();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;
    
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]){
    if( !init() ){
        printf("Unable to init\n");
    }
    else{
        if( !loadMedia() ){
            printf("Unable to load media\n");
        }
        else{
            LTimer fpsTimer;
            LTimer capTimer;

            bool quit = false;

            SDL_Event e;

            int countedFrames = 0;
            fpsTimer.start();

            int snakeMoveTicks = 0;

            bool end = false;

            while( !quit ){

                capTimer.start();
                while( SDL_PollEvent(&e) != 0 )
                {
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN)
                    {
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_UP:
                            case SDLK_w:
                                gSnake->changeDir(UP);
                                break;
                            case SDLK_RIGHT:
                            case SDLK_d:
                                gSnake->changeDir(RIGHT);
                                break;
                            case SDLK_DOWN:
                            case SDLK_s:
                                gSnake->changeDir(DOWN);
                                break;
                            case SDLK_LEFT:
                            case SDLK_a:
                                gSnake->changeDir(LEFT);
                                break;
                            case SDLK_RETURN:
                            case SDLK_SPACE:
                                end = false;
                                gApple = new LApple((rand() % GRID_WIDTH - 1), (rand() % GRID_HEIGHT - 1));
                                gSnake = new LSnake(10, 10);
                                gApple->setTexture(gRenderer);
                                gSnake->setTexture(gRenderer);
                                break;
                            default:
                                break;
                        }
                    }
                }

                if(!end)
                {
                    float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
                    if(avgFPS > 2000000){
                        avgFPS = 0;
                    }

                    if(gSnake->checkEat(gApple)) {
                        int newX = rand() % (GRID_WIDTH - 1);
                        int newY = rand() % (GRID_HEIGHT - 1);
                        bool isInvalid = gSnake->inside(newX, newY);
                        while(isInvalid)
                        {
                            newX = rand() % (GRID_WIDTH - 1);
                            newY = rand() % (GRID_HEIGHT - 1);
                            isInvalid = gSnake->inside(newX, newY);
                        }

                        gApple->setCoords(newX, newY);
                    }  

                    gSnake->show(gRenderer);
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);
                    
                    gBackgroundTexture.render(0, 0, gRenderer);
                    gApple->show(gRenderer);
                    gSnake->show(gRenderer);

                    SDL_RenderPresent(gRenderer);
                    ++countedFrames;

                    int frameTicks = capTimer.getTicks();
                    int(frameTicks < SCREEN_TICK_PER_FRAME);
                    {
                        SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
                    }
                    
                    snakeMoveTicks++;
                    if(gSnake->move(snakeMoveTicks)) snakeMoveTicks = 0;
                    if(gSnake->checkCollision()) end = true;

                }
                else{
                    gBackgroundTexture.render(0, 0, gRenderer);
                    gGameOverTexture.render(0, 0, gRenderer);
                    SDL_RenderPresent(gRenderer);
                }
            }
        }
    }
    close();
    return 0;
}