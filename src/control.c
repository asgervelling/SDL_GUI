#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "structs.h"
#include "init.h"

// Mouse control
int mouse_hovering(State *state, int bx, int by, int bw, int bh)
{
    int ax = state->control.mouse.x;
    int ay = state->control.mouse.y;

    if (ax >= bx &&
        ax <= bx + bw &&
        ay >= by &&
        ay <= by + bh)
    {
        return 1;
    }
    return 0;
}

int mouse_hovering_rect(State *state, SDL_Rect target_rect)
{
    if (mouse_hovering(state,
                       target_rect.x,
                       target_rect.y,
                       target_rect.w,
                       target_rect.h))
    {
        return 1;
    }
    return 0;
}

void change_color_on_hover(State *state)
{
    for (int i = 0; i < state->GUI.num_containers; ++i)
    {
        if (mouse_hovering_rect(state, state->containers[i].rect))
        {
            printf("container %d\n", i);
            state->control.mouse.hovering_rect = state->containers[i].rect;

            SDL_Color active_color = change_color(state->containers[i].color,
                                                  1, 1, 1, 0);
            state->containers[i].color = active_color;
            
        }
    }
}
void mouse_process(State *state)
{
    // get mouse position
    SDL_GetMouseState(&state->control.mouse.x, &state->control.mouse.y);

    // change_color_on_hover(state);
    
    
}