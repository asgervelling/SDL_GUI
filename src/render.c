#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "structs.h"
#include "init.h"

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

void render_button_TTF(SDL_Renderer *renderer, Button_TTF button, SDL_Rect parent_container_rect)
{
    // Button
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &button.rect);    
}

void render_button_TTF_bordered(SDL_Renderer *renderer,
                                Button_TTF_Bordered button,
                                SDL_Color border_color,
                                SDL_Color inner_color,
                                SDL_Rect parent_container_rect)
{
    // Border
    SDL_SetRenderDrawColor(renderer,
                           border_color.r,
                           border_color.g,
                           border_color.b,
                           border_color.a);
    SDL_RenderFillRect(renderer, &button.rect);

    // Inner rect
    SDL_SetRenderDrawColor(renderer,
                           inner_color.r,
                           inner_color.g,
                           inner_color.b,
                           inner_color.a);
    SDL_RenderFillRect(renderer, &button.inner_rect);

    print_rect(button.rect, "border");
    print_rect(button.inner_rect, "inner rect");
}

void render_containers(SDL_Renderer *renderer, Container containers[], u_int8_t num_containers)
{
    for (int i = 0; i < num_containers; ++i)
    {
        render_rect(renderer,
                    containers[i].rect,
                    containers[i].color);
    }
}

void render_buttons_TTF(State *state, SDL_Renderer *renderer, Button_TTF buttons[], u_int8_t num_buttons)
{
    for (int i = 0; i < num_buttons; ++i)
    {
        render_button_TTF(renderer, buttons[i], state->containers[buttons[i].parent_container].rect);
        
        // Text
        if (SDL_RenderCopy(renderer,
                           buttons[i].label.texture,
                           NULL,
                           &buttons[i].label.rect) < 0)
        {
            printf("SDL_RenderCopy: %s\n", SDL_GetError());
            SDL_Quit();
        }
    }
}

void render_buttons_TTF_bordered(State *state, SDL_Renderer *renderer, Button_TTF_Bordered buttons[], u_int8_t num_buttons)
{
    for (int i = 0; i < num_buttons; ++i)
    {
        render_button_TTF_bordered(renderer, buttons[i],
                                             state->buttons_TTF_bordered[i].border_color,
                                             state->buttons_TTF_bordered[i].rect_color,
                                             state->containers[buttons[i].parent_container].rect);

        // Text
        if (SDL_RenderCopy(renderer,
                           buttons[i].label.texture,
                           NULL,
                           &buttons[i].label.rect) < 0)
        {
            printf("SDL_RenderCopy: %s\n", SDL_GetError());
            SDL_Quit();
        }
    }
}

void render_GUI(State *state, SDL_Renderer *renderer)
{
    render_containers(renderer,
                      state->containers,
                      state->GUI.num_containers);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    render_buttons_TTF(state,
                       renderer,
                       state->buttons_TTF,
                       state->GUI.num_buttons);
    render_buttons_TTF_bordered(state,
                                renderer,
                                state->buttons_TTF_bordered,
                                state->GUI.num_buttons_TTF_bordered);                       
                           
}