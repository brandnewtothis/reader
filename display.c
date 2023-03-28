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

typedef struct {
    SDL_Rect console;
    Uint8 r, g, b, a;
} Dialog_box;

Dialog_box Dialogue;

int X;
int Y;
int Framerate;

void initialize_display(){

   //Basic Stuff
   Window     = NULL; 
   Renderer   = NULL;
   Background = NULL;
   Screen     = NULL;

   //Ui Elems
   //Console, where text should display on
   Dialogue.console.x = 0; Dialogue.console.y = 0;
   Dialogue.console.w = 0; Dialogue.console.h = 0;
  
   X = 1080;
   Y = 720;
   Framerate = 30;

   if (SDL_Init(SDL_INIT_VIDEO) == -1) {
      printf("error initializing SDL: %s\n", SDL_GetError());
      exit(-1);
   }

   Window = SDL_CreateWindow("Reader - WIP",
                              SDL_WINDOWPOS_CENTERED,
	      	              SDL_WINDOWPOS_CENTERED,
			      X,Y, SDL_WINDOW_SHOWN);

   if(Window == NULL){
      printf("Could not create window: %s\n",SDL_GetError());
      exit(-1);
   }

   Renderer = SDL_CreateRenderer(Window, -1,SDL_RENDERER_ACCELERATED);

   Screen = IMG_Load("img/default.png");
   Background = SDL_CreateTextureFromSurface(Renderer,Screen);
   
   //Darken Background
   SDL_SetTextureColorMod(Background, 100, 100, 100);

   int console_width =  (int)(0.8 * X);
   int console_height = (int)(0.8 * Y);

   // calculate the position of the top-left corner of the rectangle
   int console_x = (int)((X - console_width) / 2);
   int console_y = (int)((Y - console_height) / 2);
   // set the color and alpha of the rectangle
   SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 244);
   Dialogue.console.x = console_x;
   Dialogue.console.y = console_y;
   Dialogue.console.w = console_width;
   Dialogue.console.h = console_height;



SDL_SetRenderDrawColor(Renderer, 100, 100, 100, 150);


   SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);
   // draw the rectangle
//   SDL_RenderFillRect(Renderer, &Console);
//   SDL_RenderPresent(Renderer);
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

      SDL_RenderCopy(Renderer,Background,NULL,NULL);

      // draw console
      SDL_SetRenderDrawColor(Renderer, 30, 30, 30, 140);
      SDL_RenderFillRect(Renderer, &Dialogue.console);
      SDL_RenderPresent(Renderer);

   }
}

void display_exit(){

   SDL_FreeSurface(Screen);
   SDL_DestroyTexture(Background);
   SDL_DestroyRenderer(Renderer);
   SDL_DestroyWindow(Window);
   SDL_Quit();
}
