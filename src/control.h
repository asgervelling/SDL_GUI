#ifndef CONTROL
#define CONTROL

#include "structs.h"

int mouse_hovering(State *state, int bx, int by, int bw, int bh);
int mouse_hovering_rect(State *state, SDL_Rect target_rect);
void change_color_on_hover(State *state);
int mouse_process(State *state);

#endif