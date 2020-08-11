#ifndef GUI_COMPONENTS
#define GUI_COMPONENTS

#include "structs.h"
#include "init.h"

Container init_container(State *state, SDL_Renderer *renderer, SDL_Color color, int x, int y, int w, int h);
Container resize_container(Container input_container, int width, int height);

Border init_border(SDL_Rect rect);
Button_TTF init_button_TTF(State *state, SDL_Renderer *renderer, char text[], u_int8_t parent_container, int row, int column);

Grid init_grid_by_cells(State *state,
                              SDL_Color default_color,
                              int num_rows, int num_columns,
                              int x, int y, int cell_width, int cell_height,
                              u_int8_t parent_container);

#endif