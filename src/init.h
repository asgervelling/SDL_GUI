#ifndef INIT
#define INIT

SDL_Color init_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
SDL_Rect init_rect(SDL_Rect rect, int x, int y, int w, int h);
SDL_Texture* init_texture(State *state, SDL_Renderer *renderer, char text[]);
int get_text_size(State *state, char text[]);
Button_TTF init_button_TTF(State *state,
                           SDL_Renderer *renderer,
                           char text[],
                           int x,
                           int y,
                           int w,
                           int h);
void init_font(State *state);
void put_text_on_button(State *state, SDL_Renderer *renderer, Button_TTF button, char text[]);

void init_GUI(State *state, SDL_Renderer *renderer);

#endif