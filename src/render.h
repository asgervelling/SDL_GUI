#ifndef RENDER
#define RENDER

#include <SDL2/SDL.h>

void render_rect(SDL_Renderer *renderer, Rect rect, SDL_Color color);
void render_text(State *state);
void render_GUI(State *state, SDL_Renderer *renderer);


#endif