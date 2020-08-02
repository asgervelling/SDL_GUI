#ifndef INIT
#define INIT

int get_text_size(State *state, char text[]);

// GUI components
SDL_Color init_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
SDL_Rect init_rect(int x, int y, int w, int h);
Container init_container(State *state, SDL_Renderer *renderer, SDL_Color color, int x, int y, int w, int h);
SDL_Texture* init_text_texture(State *state, SDL_Renderer *renderer, char text[], SDL_Color color);
Button_TTF init_button_TTF(State *state,
                           SDL_Renderer *renderer,
                           char text[],
                           int x,
                           int y,
                           int w,
                           int h,
                           u_int8_t parent_container);
Button_TTF_Bordered init_button_border_TTF(State *state,
                                  SDL_Renderer *renderer,
                                  char text[],
                                  int border_thickness,
                                  int x, int y, int w, int h,
                                  u_int8_t parent_container);                           
void init_font(State *state);

// GUI
void init_GUI(State *state, SDL_Renderer *renderer);

#endif