
//initializing and shutdown functions
#include <SDL2/SDL.h>

//rendering images and graphics on screen/
#include <SDL2/SDL_image.h>

//for using SDL_Delay() functions
#include <SDL2/SDL_timer.h>

#include <stdio.h>


void initialize_display(){

   if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      printf("error initializing SDL: %s\n", SDL_GetError());
   }

   SDL_Window* window = SDL_CreateWindow("GAME",
  	                               SDL_WINDOWPOS_CENTERED,
				       SDL_WINDOWPOS_CENTERED,
				       0, 1000, 0);
   if(window == NULL){
      printf("Could not create window: %s\n",SDL_GetError());
      exit(-1);
   }

   SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
   SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}
