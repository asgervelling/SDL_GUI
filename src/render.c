#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "structs.h"

void print_rect(SDL_Rect rect, char name[])
{
    printf("Rect for %s:\n"
           "x: %d, y: %d\n"
           "w: %d, h: %d\n\n", name,
                             rect.x,
                             rect.y,
                             rect.w,
                             rect.h);
}

void render_rect(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer,
                           color.r,
                           color.g,
                           color.b,
                           color.a);
    SDL_RenderFillRect(renderer, &rect);
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

void render_button_TTF(SDL_Renderer *renderer, Button_TTF button)
{
    // Button
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &button.rect);

    // Text
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    // SDL_RenderCopy(renderer, button.label.texture, NULL, &button.label.rect);
    // SDL_RenderCopy(renderer, button.label.texture, NULL, &button.label.rect);
    SDL_RenderFillRect(renderer, &button.label.rect);
    
}

void render_GUI(State *state, SDL_Renderer *renderer)
{
    render_button_TTF(renderer, state->buttons[btn_file]);
    SDL_RenderCopy(renderer, state->buttons[btn_file].label.texture, NULL, &state->buttons[btn_file].label.rect);
    

    
}