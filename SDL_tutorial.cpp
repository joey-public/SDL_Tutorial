#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
//#include <>
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//TODO: create setup() function -> initalized sdl, window, and renderer, returns true or false
bool setup(SDL_Window** a_window, SDL_Renderer** a_renderer);
bool initSdl();
bool initWindow(SDL_Window** a_window);
bool initRenderer(SDL_Renderer**, SDL_Window* a_window);

//TODO: Get Basic Game Loop
bool processInput(); //handle user input, return false iff the game should quit
void update();
void render();
//TODO: create close() fucntion that deletes everything

bool setup(SDL_Window** a_window, SDL_Renderer** a_renderer)
{
  bool sdl_initilized = initSdl();
  bool sdl_window_initilized = initWindow(a_window);
  bool sdl_renderer_initilized = initRenderer(a_renderer, *a_window);
  return sdl_initilized && sdl_window_initilized && sdl_renderer_initilized;
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

bool initWindow(SDL_Window** a_window)
{
  //pass a pointer to the main window (which has type SDL_Window*) 
  //sojust a pointer to a pointer
  //Create a window, returns a pointer to an sdl window structure
  //Need to derefrence the passed pointer to properly set the window
  *a_window = SDL_CreateWindow("SDL Tutorial", 
                              SDL_WINDOWPOS_CENTERED, 
                              SDL_WINDOWPOS_CENTERED, 
                              SCREEN_WIDTH, 
                              SCREEN_HEIGHT, 
                              SDL_WINDOW_SHOWN);
  if(*a_window == NULL)
  {
    printf("Window could not be creates! SDL Error: %s\n", SDL_GetError());
    return false;
  }
  return true;
}

bool initRenderer(SDL_Renderer** a_renderer, SDL_Window* a_window)
{
  //create a renderer
  //(window, driver_code{-1=default}, flags)
  *a_renderer = SDL_CreateRenderer(a_window, 
                                  -1, 
                                  SDL_RENDERER_ACCELERATED); 
  if(*a_renderer == NULL)
  {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return false;
  }
  return true;
}

bool processInput()
{
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type)
  {
    case SDL_QUIT: 
      return false;
  }
  return true;
}

int main( int argc, char* args[] )
{
  SDL_Window* main_window = NULL;
  SDL_Surface* main_window_surface = NULL;
  SDL_Renderer* main_renderer = NULL;
  bool setup_sucessful = setup(&main_window, &main_renderer);
  if (!setup_sucessful)
  {
    printf("Setup Failed\n");
    return -1;
  }
  //temp code to make screen white as a test
  main_window_surface = SDL_GetWindowSurface(main_window);
  SDL_FillRect( main_window_surface, 
                NULL,  
                SDL_MapRGB( main_window_surface->format, 0xFF, 0xFF, 0xFF ) );
  SDL_UpdateWindowSurface(main_window);
  //main loop
  bool game_is_running = true;
  while(game_is_running)
  {
    game_is_running = processInput(); 
  }
  //destroy everything
  SDL_DestroyRenderer(main_renderer);
  SDL_DestroyWindow(main_window);
  SDL_Quit();

  printf("Thansks for playing :)\n");
  return 0;
}
