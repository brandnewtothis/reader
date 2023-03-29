//SDL implementation
#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL2/SDL.h>


void initialize_display();
void initialize_dialogText();
void update_console();
void update_screen();
void check_keys(SDL_Event event);
void display_driver();
void display_shutdown();

#endif

