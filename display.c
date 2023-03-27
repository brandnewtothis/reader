//initializing and shutdown functions
#include <SDL2/SDL.h>

//rendering images and graphics on screen/
#include <SDL2/SDL_image.h>

//for using sdl_delay() functions
#include <SDL2/SDL_timer.h>

#include <stdio.h>
#include <stdbool.h>


SDL_Window   *Window;
SDL_Renderer *Renderer;
SDL_Texture  *Background;
SDL_Surface  *Screen;

int X;
int Y;
int Framerate;

void initialize_display(){

   Window     = NULL; 
   Renderer   = NULL;
   Background = NULL;
   Screen     = NULL;
   
   X = 640;
   Y = 480;
   Framerate = 30;

   if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
      printf("error initializing SDL: %s\n", SDL_GetError());
      exit(-1);
   }

   Window = SDL_CreateWindow("HELLO WORLD",
                              SDL_WINDOWPOS_CENTERED,
	      	              SDL_WINDOWPOS_CENTERED,
			      X,Y, SDL_WINDOW_SHOWN);

   if(Window == NULL){
      printf("Could not create window: %s\n",SDL_GetError());
      exit(-1);
   }

   Renderer = SDL_CreateRenderer(Window, -1,SDL_RENDERER_ACCELERATED);

   Screen = SDL_LoadBMP("img/hello.bmp");
   Background = SDL_CreateTextureFromSurface(Renderer,Screen);
   SDL_Delay(2000);

}

void display_driver(){
   SDL_Event event;

   bool running = true;

   while (running){
      while (SDL_PollEvent(&event)) {
         switch(event.type){
	    case SDL_QUIT:
	       running = false;

	 }
      }

   }
}

void display_exit(){
   SDL_DestroyRenderer(Renderer);
   SDL_DestroyWindow(Window);
   SDL_Quit();
}
