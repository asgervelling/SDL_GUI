#ifndef INIT
#define INIT

int get_text_size(State *state, char text[]);

// GUI components
SDL_Color init_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
SDL_Color change_color(SDL_Color input_color, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

SDL_Rect init_rect(int x, int y, int w, int h);
Container init_container(State *state, SDL_Renderer *renderer, SDL_Color color, int x, int y, int w, int h);
Container resize_container(Container input_container, int width, int height);
SDL_Texture* init_text_texture(State *state, SDL_Renderer *renderer, char text[], SDL_Color color);

Button_TTF init_button_TTF(State *state, SDL_Renderer *renderer, char text[], u_int8_t parent_container, int row, int column);
Button_TTF_Bordered init_button_border_TTF(State *state,
                                  SDL_Renderer *renderer,
                                  char text[],
                                  int border_thickness,
                                  int x, int y, int w, int h,
                                  u_int8_t parent_container);  

Grid init_grid_by_cells(State *state,
                              SDL_Color default_color,
                              int num_rows, int num_columns,
                              int x, int y, int cell_width, int cell_height,
                              u_int8_t parent_container);
                                                                                         
void init_font(State *state);

// GUI
void init_GUI(State *state, SDL_Renderer *renderer, int rows, int columns);

#endif