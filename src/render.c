#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "math.h"

#include "structs.h"
#include "init.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

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

void render_triangle(SDL_Renderer *renderer, int ax, int ay, int bx, int by, int cx, int cy, int right_angle)
{
    int x_origo, y_origo;
    int x_max, y_max;
    int diff;

    // Find origo
    x_origo = MIN(ax, bx);
    x_origo = MIN(x_origo, cx);
    y_origo = MIN(ay, by);
    y_origo = MIN(y_origo, cy);

    // Find the point at the other end of the hypotenuse
    x_max = MAX(ax, bx);
    x_max = MAX(x_max, cx);
    y_max = MAX(ay, by);
    y_max = MAX(y_max, cy);

    if (right_angle == top_left)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for (int x = x_origo; x < x_max; ++x)
        {
            diff = x - x_origo;
            SDL_RenderDrawLine(renderer, x, y_origo, x, y_max - diff);
        }
    }
    if (right_angle == top_right)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for (int x = x_origo; x < x_max; ++x)
        {
            diff = x - x_origo; // Same for x and y
            SDL_RenderDrawLine(renderer, x, y_origo, x, y_origo + diff);
            
        }
    }
    if (right_angle == bottom_left)
    {
        for (int x = x_origo; x < x_max; ++x)
        {
            SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
            diff = x - x_origo;
            SDL_RenderDrawLine(renderer, x, y_max, x, y_origo + diff);
        }
    }

    if (right_angle == bottom_right)
    {
        for (int x = x_origo; x < x_max; ++x)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            diff = x - x_origo;
            SDL_RenderDrawLine(renderer, x, y_max, x, y_max - diff);
        }
    }

    
}

void render_button_TTF(SDL_Renderer *renderer, Button_TTF button)
{
    // First the actual button
    SDL_SetRenderDrawColor(renderer, button.color.r, button.color.g, button.color.b, button.color.a);
    SDL_RenderFillRect(renderer, &button.rect); 

    // Then the border, four rectangles
    for (int i = 0; i < 4; ++i)
    {
        SDL_SetRenderDrawColor(renderer,
                               button.border.colors[i].r,
                               button.border.colors[i].g,
                               button.border.colors[i].b,
                               button.border.colors[i].a);
        SDL_RenderFillRect(renderer, &button.border.rects[i]);                               
    }


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
}

void render_buttons_TTF(State *state, SDL_Renderer *renderer, Button_TTF buttons[], u_int8_t num_buttons)
{
    for (int i = 0; i < num_buttons; ++i)
    {
        render_button_TTF(renderer, buttons[i]);
        
        // Text shadow
        if (SDL_RenderCopy(renderer,
                           buttons[i].label.texture_shadow,
                           NULL,
                           &buttons[i].label.rect_shadow) < 0)
        {
            printf("SDL_RenderCopy: %s\n", SDL_GetError());
            SDL_Quit();
        }

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

void render_cell(SDL_Renderer *renderer, Cell cell)
{
    render_rect(renderer, cell.rect, cell.color);
}

void render_grid(SDL_Renderer *renderer, Grid grid)
{
    for (int row = 0; row < grid.num_rows; ++row)
    {
        for (int column = 0; column < grid.num_columns; ++column)
        {
            render_cell(renderer, grid.matrix[row][column]);
        }
    }
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

void render_GUI(State *state, SDL_Renderer *renderer)
{
    render_containers(renderer,
                      state->containers,
                      state->GUI.num_containers);
    
    render_buttons_TTF(state,
                       renderer,
                       state->buttons_TTF,
                       state->GUI.num_buttons);

    render_grid(renderer, state->grid);



    render_triangle(renderer, 0, 0, 40, 40, 0, 40, bottom_left);
}                           