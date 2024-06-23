#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Global Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT, 
    KEY_PRESS_SURFACE_UP,   
    KEY_PRESS_SURFACE_DOWN,   
    KEY_PRESS_SURFACE_LEFT,   
    KEY_PRESS_SURFACE_RIGHT,   
    KEY_PRESS_SURFACE_TOTAL   
};

//Global Variables 
//gVarName convention for gloabal variables
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;
SDL_Surface* gPNGSurface = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

//function declarations
bool init();
bool loadMedia();
SDL_Surface* loadSurface(std::string path);
SDL_Texture* loadTexture(std::string path);
void myClose();//apparently cannot use C for this 

//SDL requires the int argc and char* args[] arguments 
int main(int argc, char* args[])
{
    bool renderTexture = false;
    if(!init())
    {
        printf("Failed to initilize!\n");
    }
    else
    {
        if(!loadMedia())
        {
            printf("Failed to load Media!\n");
        }
        else
        {
            bool quit = false;
            SDL_Event e;
            // gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
            gCurrentSurface = gPNGSurface; 
            //event loop
            while(!quit)
            {
                while(SDL_PollEvent(&e) != 0)
                {
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN)
                    {
                        renderTexture = false;
                        switch(e.key.keysym.sym)
                        {
                            case SDLK_UP:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                            break;
                            case SDLK_DOWN:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                            break;
                            case SDLK_LEFT:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                            break;
                            case SDLK_RIGHT:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                            break;
                            case SDLK_j:
                            gCurrentSurface = gPNGSurface;
                            break;
                            case SDLK_k:
                            renderTexture = true;
                            break;
                            default:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                        }
                    }
                }
                if(!renderTexture)
                {
                    SDL_Rect strecthRect; strecthRect.x = 0; strecthRect.y = 0; strecthRect.w = SCREEN_WIDTH/2;
                    strecthRect.h = SCREEN_HEIGHT/2;
                    // SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
                    SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &strecthRect);
                    SDL_UpdateWindowSurface(gWindow);
                }
                else
                {
                    SDL_RenderClear(gRenderer);
                    SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
                    SDL_RenderPresent(gRenderer);
                }
            }
        }
    }
    myClose();
    return 0;
}

// function implementations
bool init()
{
    bool success = true;
    //Init SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initilize! SDL_Error: %s\n",
               SDL_GetError());
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("SDL Tutorial", 
                                    SDL_WINDOWPOS_UNDEFINED, 
                                    SDL_WINDOWPOS_UNDEFINED, 
                                    SCREEN_WIDTH, 
                                    SCREEN_HEIGHT, 
                                    SDL_WINDOW_SHOWN);
        if(gWindow==NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", 
                   SDL_GetError());
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, 
                                            SDL_RENDERER_ACCELERATED);
            if(gRenderer==NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", 
                       SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags))
            {
                printf("SDL_image could not init!\n SDL_image Error: %s\n",
                           IMG_GetError());
                success = false;
            }
            else
            {
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;
    //load PNG texture
    gTexture = loadTexture("images/texture.png");
    if(gTexture == NULL)
    {
        printf("Failed to load texture image!\n");
        success = false;
    }
    //load png surface
    gPNGSurface = loadSurface("images/loaded.png");
    if(gPNGSurface == NULL)
    {
        printf("Failed to load png image!\n");
        success = false;
    }
    //load default surface
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("images/press.bmp");
    if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
    {
        printf("Failed to load default image!\n");
        success = false;
    }
    //Load up surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "images/up.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        printf( "Failed to load up image!\n" );
        success = false;
    }
    //Load down surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "images/down.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
        printf( "Failed to load down image!\n" );
        success = false;
    }
    //Load left surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "images/left.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
    {
        printf( "Failed to load left image!\n" );
        success = false;
    }
    //Load right surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "images/right.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        printf( "Failed to load right image!\n" );
        success = false;
    }
    return success;
}

SDL_Surface* loadSurface(std::string path)
{
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        printf("Unable to load image %s!\n SDL Error: %s\n", 
               path.c_str(), SDL_GetError());
    }
    //convert loadedSurface to optimizedSurface
    else
    {
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if(optimizedSurface==NULL)
        {
            printf("Unable to optimize image %s!\nSDL Error: %s\n", 
                   path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}

SDL_Texture* loadTexture(std::string path)
{
    //loading TEsture using SDL_IMG
    SDL_Texture* newTexture = IMG_LoadTexture(gRenderer, path.c_str());
    if(newTexture==NULL)
    {
        printf("Unable to create texture from %s!\n SDL Error: %s\n", 
        path.c_str(), IMG_GetError());
    }
    return newTexture;
    //old way of loading Texture with SDL
    // SDL_Texture* newTexture = NULL;
    // SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    // if(loadedSurface==NULL)
    // {
    //     printf("Unable to load image %s!\n SDL_image Error: %s\n", 
    //            path.c_str(), IMG_GetError());
    // }
    // else
    // {
    //     newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    //     if(newTexture==NULL)
    //     {
    //         printf("Unable to create texture from %s!\n SDL Error: %s\n", 
    //                path.c_str(), SDL_GetError());
    //     }
    //     SDL_FreeSurface(loadedSurface);
    // }
    // return newTexture;
}

void myClose()
{
    for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++){
        SDL_FreeSurface(gKeyPressSurfaces[i]);
        gKeyPressSurfaces[i] = NULL;
    }

    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    SDL_FreeSurface(gPNGSurface);
    gPNGSurface = NULL;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}
