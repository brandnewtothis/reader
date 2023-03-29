//initializing and shutdown functions
#include <SDL2/SDL.h>

//rendering images and graphics on screen/
#include <SDL2/SDL_image.h>

//for using sdl_delay() functions
#include <SDL2/SDL_timer.h>

#include <SDL2/SDL2_gfxPrimitives.h>

//Text
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdbool.h>

#include "display.h"

//Where text is displayed on
typedef struct {
    SDL_Rect console;
    Uint8 r, g, b, a; //Color and alpha of console
    TTF_Font *font;
    Uint8 fontSize;
    SDL_Color fontColor;
} Dialog_box;

//Screen
typedef struct{
   SDL_Renderer *renderer;
   SDL_Texture  *background;
   SDL_Texture  *text;
   SDL_Surface  *surface;
} Screen;

int Width;
int Height;
SDL_Window *Window;

Dialog_box Dialog;
Screen Main_screen;

void initialize_display(){
   //Basic Stuff
   Window                 = NULL; 
   Main_screen.renderer   = NULL;
   Main_screen.background = NULL;
   Main_screen.surface    = NULL;

   //Ui Elems
   //Console, where text should display on
   Dialog.console.x = 0; Dialog.console.y = 0;
   Dialog.console.w = 0; Dialog.console.h = 0;

   //Window Dimensions
   Width = 640; Height = 480;

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

   //Graphics card does rendering
   Main_screen.renderer = SDL_CreateRenderer(Window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 

   //Load Background texture 
   Main_screen.surface = IMG_Load("img/default.png");
   Main_screen.background = SDL_CreateTextureFromSurface(Main_screen.renderer,Main_screen.surface);
   //Darken Background
   SDL_SetTextureColorMod(Main_screen.background, 170, 170, 170);  
   //Sets transparency to Renderer
   SDL_SetRenderDrawBlendMode(Main_screen.renderer, SDL_BLENDMODE_BLEND);  

   update_console();

}

void initialize_dialogText(){
   //Text Color for System
   Dialog.font = NULL;
   //White text
   Dialog.fontColor.r = 255; Dialog.fontColor.g = 255; Dialog.fontColor.b = 255;
   //TODO Adjust fontsize based on screen resolution
   Dialog.fontSize = 28;

   if (TTF_Init() < 0) {
      printf("error initializing SDL_ttf: %s\n", TTF_GetError());
      exit(-1);
   }

   // Load font file
   #ifdef __linux__
   Dialog.font = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", Dialog.fontSize);
   #elif __APPLE__
   Dialog.font = TTF_OpenFont("/Library/Fonts/Arial.ttf", Dialog.fontSize);
   #elif _WIN32
   Dialog.font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", Dialog.fontSize);
   #endif
	
   if (Dialog.font == NULL) { 
      printf("error loading font file: %s\n", TTF_GetError());
      exit(-1);
   }
}

/* 
 * Change Consoles dimensions according to Width and Height of Window
 * 
 */
void update_console(){
   int console_width =  (int)(0.85 * Width);
   int console_height = (int)(0.85 * Height);

   // calculate the position of the top-left corner of the rectangle
   int console_x = (int)((Width - console_width) / 2);
   int console_y = (int)((Height - console_height) / 2);

   // set console location
   Dialog.console.x = console_x;     Dialog.console.y = console_y;
   Dialog.console.w = console_width; Dialog.console.h = console_height;
}

/*
 * Main loop of program
 *
 */
void display_driver(){
   SDL_Event event;
   bool running = true;

   //draw background
   SDL_RenderCopy(Main_screen.renderer,Main_screen.background,NULL,NULL);

   //draw console
   SDL_SetRenderDrawColor(Main_screen.renderer, 30, 30, 30, 140);
   SDL_RenderFillRect(Main_screen.renderer, &Dialog.console);

   //Draw Text
   SDL_CreateTexture(Main_screen.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);
   
  //XXX 
   const char* text[] = {"\"...\"","...That's right.","This text display kinda works","If what this says is true then... that means..!"};
   SDL_Surface* surfaces[3];

   for(int i = 0;i<4;i++){
      surfaces[i] = TTF_RenderText_Solid(Dialog.font,text[i],(SDL_Color){255,255,255});
   }

   SDL_Rect dstrect = {Dialog.console.x + 10,Dialog.console.y,surfaces[0]->w,surfaces[0]->h};

   int current_surface = 0;

   //Show 
   SDL_RenderPresent(Main_screen.renderer);

   //Main Driver
   while (running){
      while(SDL_PollEvent(&event)){		
         if(event.type == SDL_QUIT){
               running = false;
         }
	 else if(event.type == SDL_KEYDOWN){
            switch(event.key.keysym.sym){
	       case SDLK_SPACE:
	          current_surface++;
		  if(current_surface >= 4){
		     current_surface = 0;	  
		  }
		  dstrect.w = surfaces[current_surface]->w;
		  dstrect.h = surfaces[current_surface]->h;
		  SDL_DestroyTexture(Main_screen.text);
		  Main_screen.text = SDL_CreateTextureFromSurface(Main_screen.renderer,surfaces[current_surface]);
                  update_screen();
SDL_RenderCopy(Main_screen.renderer,Main_screen.text,NULL,&dstrect);
//Show
SDL_RenderPresent(Main_screen.renderer);


		  break;
	       default:
		  break;
	    }
	 }
      }


   }
}

void check_keys(SDL_Event event){
   


}

void update_screen(){
   //Clear Screen
   SDL_RenderClear(Main_screen.renderer);
   //Background
   SDL_RenderCopy(Main_screen.renderer,Main_screen.background,NULL,NULL);
   //Console
   SDL_SetRenderDrawColor(Main_screen.renderer, 30, 30, 30, 140);
   SDL_RenderFillRect(Main_screen.renderer, &Dialog.console); 
   //Text
 //  SDL_RenderCopy(Main_screen.renderer,Main_screen.text,NULL,&dstrect);
   //Show
   //SDL_RenderPresent(Main_screen.renderer);
}


void display_shutdown(){
   if(Main_screen.surface){
      SDL_FreeSurface(Main_screen.surface);
   }

   if(Main_screen.background){
      SDL_DestroyTexture(Main_screen.background);
   }
   if(Main_screen.renderer){
      SDL_DestroyRenderer(Main_screen.renderer);
   }

   if(Dialog.font){
      TTF_CloseFont(Dialog.font);
   }

   if(Window){
      SDL_DestroyWindow(Window);
   }

   TTF_Quit();
   SDL_Quit();
}
