#ifndef INIT
#define INIT

Int_Tuple get_text_size(State *state, char text[]);

// GUI components
SDL_Color init_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
SDL_Color change_color(SDL_Color input_color, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

SDL_Rect init_rect(int x, int y, int w, int h);
SDL_Texture* init_text_texture(State *state, SDL_Renderer *renderer, char text[], SDL_Color color);
                                                                                         
void init_font(State *state);

// GUI
void init_GUI_layout(State *state, SDL_Renderer *renderer, int rows, int columns);
void init_GUI(State *state, SDL_Renderer *renderer, int rows, int columns);

#endif