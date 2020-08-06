#ifndef RENDER
#define RENDER

#include <SDL2/SDL.h>

// Debug
void print_rect(SDL_Rect rect, char name[]);

// Render components
void render_rect(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color);
void render_containers(SDL_Renderer *renderer, Container containers[], u_int8_t num_containers);
void render_button_TTF(SDL_Renderer *renderer, Button_TTF button, SDL_Rect parent_container_rect);
void render_button_TTF_bordered(SDL_Renderer *renderer,
                                Button_TTF_Bordered button,
                                SDL_Color border_color,
                                SDL_Color inner_color,
                                SDL_Rect parent_container_rect);
void render_text(State *state);
void render_cell(SDL_Renderer *renderer, Cell cell);
void render_grid(SDL_Renderer *renderer, Grid grid);
void render_buttons_TTF(State *state, SDL_Renderer *renderer, Button_TTF buttons[], u_int8_t num_buttons);
void render_buttons_TTF_bordered(State *state, SDL_Renderer *renderer, Button_TTF_Bordered buttons[], u_int8_t num_buttons);


// Render GUI
void render_GUI(State *state, SDL_Renderer *renderer);


#endif