#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "structs.h"

void render_rect(SDL_Renderer *renderer, Rect rect, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer,
                           color.r,
                           color.g,
                           color.b,
                           color.a);
    SDL_Rect dest = {rect.x,
                     rect.y,
                     rect.w,
                     rect.h};
    SDL_RenderFillRect(renderer, &dest);
}

/*

Now do somehting like

void render_button(parent_container = some container)
{
    position = relative to parent container
}

*/

void render_text(State *state)
{
    return;   
}

void render_GUI(State *state, SDL_Renderer *renderer)
{
    return;
}