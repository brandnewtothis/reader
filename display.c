//initializing and shutdown functions
#include <SDL2/SDL.h>

//rendering images and graphics on screen/
#include <SDL2/SDL_image.h>

//for using sdl_delay() functions
#include <SDL2/SDL_timer.h>

//Text
#include <SDL_ttf.h>


#include <stdio.h>
#include <stdbool.h>

#include "display.h"

//Where text is displayed on
typedef struct {
    SDL_Rect console;
    Uint8 r, g, b, a; //Color and alpha of console
} Dialog_box;

SDL_Window   *Window;
SDL_Renderer *Renderer;
SDL_Texture  *Background;
SDL_Surface  *Screen;

int Width;
int Height;
int Framerate;

Dialog_box Dialog;

TTF_Font *Font;
SDL_Color FontColor;

void initialize_display(){

   //Basic Stuff
   Window     = NULL; 
   Renderer   = NULL;
   Background = NULL;
   Screen     = NULL;

   //Ui Elems
   //Console, where text should display on
   Dialog.console.x = 0; Dialog.console.y = 0;
   Dialog.console.w = 0; Dialog.console.h = 0;

   Width = 640;
   Height = 480;
   Framerate = 30;

   if (SDL_Init(SDL_INIT_VIDEO) == -1) {
      printf("error initializing SDL: %s\n", SDL_GetError());
      exit(1);
   }


   Window = SDL_CreateWindow("Reader - WIP",
                              SDL_WINDOWPOS_CENTERED,
	      	              SDL_WINDOWPOS_CENTERED,
			      Width,Height, SDL_WINDOW_SHOWN);

   if(Window == NULL){
      printf("Could not create window: %s\n",SDL_GetError());
      exit(1);
   }

   Renderer = SDL_CreateRenderer(Window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //Graphics card does rendering

   Screen = IMG_Load("img/default.png");
   Background = SDL_CreateTextureFromSurface(Renderer,Screen);
   
   SDL_SetTextureColorMod(Background, 100, 100, 100);  //Darken Background

   int console_width =  (int)(0.85 * Width);
   int console_height = (int)(0.85 * Height);

   // calculate the position of the top-left corner of the rectangle
   int console_x = (int)((Width - console_width) / 2);
   int console_y = (int)((Height - console_height) / 2);

   // set console location
   Dialog.console.x = console_x; Dialog.console.y = console_y;
   Dialog.console.w = console_width; Dialog.console.h = console_height;

   //Sets transparency to Renderer
   SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);


}

void initialize_dialogText(){
   //Text Color for System
   Font = NULL;
   FontColor.r = 0; FontColor.g = 0; FontColor.b = 0;

   if (TTF_Init() < 0) {
      printf("error initializing SDL_ttf: %s\n", TTF_GetError());
      exit(-1);
   }

   // Load font file
   #ifdef __linux__
   Font = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", 24);
   #elif __APPLE__
   Font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 24);
   #elif _WIN32
   Font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 24);
   #endif
	
   if (Font == NULL) { 
      printf("error loading font file: %s\n", TTF_GetError());
      exit(-1);
   }

   FontColor.r = 220; FontColor.g = 220; FontColor.b = 220;
   // Create a surface with text
   SDL_Surface* text_surface = TTF_RenderText_Blended(Font,"Hello World",FontColor);
	
   //Create a texture from the surfac  
   SDL_Texture* text_texture = SDL_CreateTextureFromSurface(Renderer, text_surface);
   // Render the texture onto the Dialogue.console 
   SDL_Rect text_rect = { Dialog.console.x + 10, Dialog.console.y + 10, 0, 0 };
   SDL_QueryTexture(text_texture, NULL, NULL, &text_rect.w, &text_rect.h);
   SDL_RenderCopy(Renderer, text_texture, NULL, &text_rect);
 
   // Clean up resources 
//   SDL_FreeSurface(text_surface);
//   SDL_DestroyTexture(text_texture);
}


void display_driver(){
   SDL_Event event;
   bool running = true;

   //draw background
   SDL_RenderCopy(Renderer,Background,NULL,NULL);

   //draw console
   SDL_SetRenderDrawColor(Renderer, 30, 30, 30, 140);
   SDL_RenderFillRect(Renderer, &Dialog.console);

   //Show 
   SDL_RenderPresent(Renderer);

//   Uint32 lastTick = SDL_GetTicks();

   //char *texts[] = { "Hello", "World", "How", "Are", "You?" };

   //Main Driver
   while (running){
      while(SDL_PollEvent(&event)){		
         if(event.type == SDL_QUIT){
               running = false;
         }
      }
/*
      Uint32 curTick = SDL_GetTicks();
      Uint32 diff = curTick - lastTick;
      float elapsed = diff / 1000.0f;
      display_update(elapsed);
      lastTick = curTick;
*/
   }
}

void display_update(float elapsed){


}

void display_shutdown(){
   if(Screen){
      SDL_FreeSurface(Screen);
   }

   if(Background){
      SDL_DestroyTexture(Background);
   }
   if(Renderer){
      SDL_DestroyRenderer(Renderer);
   }

   if(Font){
      TTF_CloseFont(Font);
   }

   if(Window){
      SDL_DestroyWindow(Window);
   }

   SDL_Quit();
}
