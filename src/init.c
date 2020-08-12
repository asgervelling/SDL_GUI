#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#include "structs.h"
#include "file_io.h"
#include "GUI_components.h"

SDL_Rect init_rect(int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    return rect;
}

/**********************
 * Text
 * *******************/

void init_font(State *state)
{  
    TTF_Font *font;
    font=TTF_OpenFont("resources/arial.ttf", 20);
    if(!font) 
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
        SDL_Quit();
    }
    state->font = font;
}

SDL_Texture* init_text_texture(State *state, SDL_Renderer *renderer, char text[], SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(state->font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

/********************
Smaller components
********************/

SDL_Color init_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;

    return color;
}

SDL_Color change_color(SDL_Color input_color, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    // Change the input_color by rgba values
    SDL_Color color;
    color.r = input_color.r - r;
    color.g = input_color.g - g;
    color.b = input_color.b - b;
    color.a = input_color.a - a;

    return color;
}

Int_Tuple get_text_size(State *state, char text[])
{
    // get the width and height of a string as it would be rendered in a loaded font
    //TTF_Font *font;
    int w,h;
    TTF_SizeText(state->font, text ,&w,&h);
    Int_Tuple tuple;
    tuple.a = w;
    tuple.b = h;
    return tuple;
}

/**********************
 * GUI
 * *******************/

void init_GUI_layout(State *state, SDL_Renderer *renderer, int rows, int columns)
{
    int rgba_value = 40;
    SDL_Color container_color;

    // Containers
    int index = 0;
    SDL_Rect container_dest;
    container_dest.w = state->display_width / columns;
    container_dest.h = state->display_height / rows;
    container_dest.x = 0;
    container_dest.y = 0;
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < columns; ++col)
        {
            // Positioning
            container_dest.x = col * container_dest.w;
            container_dest.y = row * container_dest.h;

            // int index shades of grey
            rgba_value += 6;
            if (rgba_value > 255)
            {
                rgba_value = rgba_value - 255;
            }

            // init container
            container_color = init_color(rgba_value, rgba_value, rgba_value, rgba_value);
            state->containers[index] = init_container(state,
                                                      renderer,
                                                      container_color,
                                                      container_dest.x,
                                                      container_dest.y,
                                                      container_dest.w,
                                                      container_dest.h);                                           
            ++index;   
        }
    }
}

void init_GUI(State *state, SDL_Renderer *renderer, int rows, int columns)
{
    // The GUI struct should only hold information about
    // the number of each of its components.
    // By keeping the components seperate, they become
    // more reusable.
    state->GUI.num_containers = 0;
    state->GUI.num_buttons = 0;
    state->GUI.num_buttons_TTF_bordered = 0;
    state->GUI.num_rows = rows;
    state->GUI.num_columns = columns;
    state->display_width = 960;
    state->display_height = 640;

    // Colors
    state->colors.black = init_color(0, 0, 0, 255);
    state->colors.grey = init_color(150, 150, 150, 255);
    state->colors.white = init_color(255, 255, 255, 255);
    state->colors.blue = init_color(0, 0, 255, 255);

    /****************************************************************************
        GUI layout:

        A GUI has rows and columns of containers.
        A container has rows and columns of GUI components such as buttons, text fields, etc.
        The sizes are done automatically for each container and GUI component.
    *****************************************************************************/

    // Containers
    init_GUI_layout(state, renderer, rows, columns);

    // Components layout
    state->containers[0].rows = 2;
    state->containers[0].columns = 1;

    state->containers[1].rows = 1;
    state->containers[1].columns = 1;

    state->containers[4].rows = 1;
    state->containers[4].columns = 2;

    // Buttons
    state->buttons_TTF[0] = init_button_TTF(state, renderer, "Button 0", 0, 0, 0); // Container 0, row 0, column 0
    state->buttons_TTF[1] = init_button_TTF(state, renderer, "Button 1", 0, 1, 0);
    state->buttons_TTF[2] = init_button_TTF(state, renderer, "Button 2", 1, 0, 0);
    state->buttons_TTF[3] = init_button_TTF(state, renderer, "Button 3", 4, 0, 0);
    state->buttons_TTF[4] = init_button_TTF(state, renderer, "Button 4", 4, 0, 1);

    
    

}

