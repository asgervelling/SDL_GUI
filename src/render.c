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
        for (int x = x_origo; x < x_max; ++x)
        {
            diff = x - x_origo;
            SDL_RenderDrawLine(renderer, x, y_origo, x, y_max - diff);
        }
    }
    if (right_angle == top_right)
    {
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
            diff = x - x_origo;
            SDL_RenderDrawLine(renderer, x, y_max, x, y_origo + diff);
        }
    }

    if (right_angle == bottom_right)
    {
        for (int x = x_origo; x < x_max; ++x)
        {
            diff = x - x_origo;
            SDL_RenderDrawLine(renderer, x, y_max, x, y_max - diff);
        }
    }    
}

void render_border_corners(SDL_Renderer *renderer, Border border, int border_thickness)
{
    Uint8 r, g, b, a;

    // Top border
    r = border.colors[top].r;
    g = border.colors[top].g;
    b = border.colors[top].b;
    a = border.colors[top].a;
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    render_triangle(renderer,
                    border.rects[top].x - border_thickness, border.rects[top].y,
                    border.rects[top].x, border.rects[top].y,
                    border.rects[top].x, border.rects[top].y + border_thickness,
                    top_right);
    
    render_triangle(renderer,
                    border.rects[top].x + border.rects[top].w, border.rects[top].y,
                    border.rects[top].x + border.rects[top].w + border_thickness, border.rects[top].y,
                    border.rects[top].x + border.rects[top].w, border.rects[top].y + border_thickness,
                    top_left);

    // Bottom border
    r = border.colors[bottom].r;
    g = border.colors[bottom].g;
    b = border.colors[bottom].b;
    a = border.colors[bottom].a;
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    render_triangle(renderer,
                    border.rects[bottom].x - border_thickness, border.rects[bottom].y,
                    border.rects[bottom].x, border.rects[bottom].y,
                    border.rects[bottom].x, border.rects[bottom].y + border.rects[bottom].h,
                    bottom_right);
    
    render_triangle(renderer,
                    border.rects[bottom].x + border.rects[bottom].w, border.rects[bottom].y,
                    border.rects[bottom].x + border.rects[bottom].w + border_thickness, border.rects[bottom].y,
                    border.rects[bottom].x + border.rects[bottom].w, border.rects[bottom].y + border.rects[bottom].y + border_thickness,
                    bottom_left);
    
                    
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

    // Corners
    render_border_corners(renderer, button.border, 4);

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

    print_rect(state->buttons_TTF[0].border.rects[top], "top border");
    print_rect(state->buttons_TTF[0].border.rects[bottom], "bottom border");
    print_rect(state->buttons_TTF[0].border.rects[left], "left border");
    print_rect(state->buttons_TTF[0].border.rects[right], "right border");



}                           