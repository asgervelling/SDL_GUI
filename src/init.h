#ifndef INIT
#define INIT

SDL_Color init_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
Rect init_rect(Rect rect, int x, int y, int w, int h);
Button_TTF init_button_TTF(int x,
                           int y,
                           int w,
                           int h);
void init_font(State *state);
void put_text_on_button(State *state, SDL_Renderer *renderer, Button_TTF button, char text[]);

void init_GUI(State *state, SDL_Renderer *renderer);

#endif