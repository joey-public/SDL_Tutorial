//Using SDL and standard IO
//includes
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

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

//function declarations
bool init();
bool loadMedia();
SDL_Surface* loadSurface(std::string path);
void myClose();//apparently cannot use C for this 

//SDL requires the int argc and char* args[] arguments 
int main(int argc, char* args[])
{
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
            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
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
                            default:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                        }
                    }
                }
                SDL_Rect strecthRect;
                strecthRect.x = 0;
                strecthRect.y = 0;
                strecthRect.w = SCREEN_WIDTH/2;
                strecthRect.h = SCREEN_HEIGHT/2;
                // SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
                SDL_BlitScaled(gCurrentSurface, NULL, gScreenSurface, &strecthRect);
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }
    myClose();
    return 0;
}

// function implementations
bool init()
{
    //Init SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initilize! SDL_Error: %s\n", SDL_GetError());
        return false;
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
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return true;
}

bool loadMedia()
{
    bool success = true;
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
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == NULL)
    {
        printf("Unable to load image %s!\n SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    //convert loadedSurface to optimizedSurface
    else
    {
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if(optimizedSurface==NULL)
        {
            printf("Unable to optimize image %s!\nSDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}

void myClose()
{
    for(int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++){
        SDL_FreeSurface(gKeyPressSurfaces[i]);
        gKeyPressSurfaces[i] = NULL;
    }

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}
