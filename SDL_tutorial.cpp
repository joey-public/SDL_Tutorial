#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
//#include <>
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool initSdl();
bool initWindow(SDL_Window* a_window);
bool initRenderer(SDL_Renderer* a_renderer);
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();
//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );


bool init(SDL_Window* a_window, SDL_Renderer* a_renderer)
{
    return initSdl() && initWindow(a_window) && initRenderer(a_renderer);
}

bool initSdl()
{
  //initilize SDL
  if(SDL_Init(SDL_INIT_VIDEO)<0)
  {
    printf("SDL could not initilize! SDL Error: %s\n", SDL_GetError());
    return false;
  }
  return true;
}

bool initWindow(SDL_Window* a_window)
{
  //Create a window, returns a pointer to an sdl window structure
  a_window = SDL_CreateWindow("SDL Tutorial", 
                            SDL_WINDOWPOS_UNDEFINED, 
                            SDL_WINDOWPOS_UNDEFINED, 
                            SCREEN_WIDTH, 
                            SCREEN_HEIGHT, 
                            SDL_WINDOW_SHOWN);
  if(a_window==NULL)
  {
    printf("Window could not be creates! SDL Error: %s\n", SDL_GetError());
    return false;
  }
  return true;
}

bool initRenderer(SDL_Renderer* a_renderer)
{
  return true;
}

int main( int argc, char* args[] )
{
  SDL_Window* main_window = NULL;
  SDL_Renderer* main_renderer = NULL;
  if(!init(main_window, main_renderer))  
  { 
    printf("Failed to Initilize!\n"); 
    return -1;
  }
  printf("Hello World!\n");
  return 0;
}
