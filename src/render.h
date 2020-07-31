#ifndef RENDER
#define RENDER

#include <SDL2/SDL.h>

// Debug
void print_rect(SDL_Rect rect);

// Render components
void render_rect(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color);
void render_button_TTF(SDL_Renderer *renderer, Button_TTF button);
void render_text(State *state);

// Render GUI
void render_GUI(State *state, SDL_Renderer *renderer);


#endif