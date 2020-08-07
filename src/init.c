#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#include "structs.h"
#include "file_io.h"
#include "grids.h"

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

Button_TTF init_button_TTF(State *state, SDL_Renderer *renderer, char text[], u_int8_t parent_container, int row, int column)
{
    // Keep track of the total number of buttons
    state->GUI.num_buttons += 1;
    // state->containers[parent_container].num_child_components += 1;
    

    // Create a new Button_TTF
    Button_TTF button_TTF;

    // Position button according to "parent" container
    // (and save the information for later use)
    int x, y;
    int w, h;
    Int_Tuple text_size = get_text_size(state, text);

    // Colors
    SDL_Color button_color, text_color;
    text_color = state->colors.black;
    button_color = init_color(text_color.a - 122,
                            text_color.g - 122,
                            text_color.b - 122,
                            255);
    button_TTF.color = button_color;

    // Make rectangles
    w = state->containers[parent_container].rect.w / state->containers[parent_container].columns;
    printf("w, parent: %d, %d\n", w, state->containers[parent_container].rect.w);
    printf("child components of containers[%d]: %d\n", parent_container, state->containers[parent_container].num_child_components);
    h = state->containers[parent_container].rect.h / state->containers[parent_container].rows;
    x = state->containers[parent_container].rect.x + (column * w);
    y = state->containers[parent_container].rect.y + (row * h);
    
    button_TTF.rect = init_rect(x, y, w, h);

    // Never stretch the text, but shrink it if it is too large
    // for the button.
    u_int8_t margin = 6;
    text_size.a = fmin(text_size.a, w - 4 * margin);
    button_TTF.label.rect = init_rect(x + w / 2 - (text_size.a / 2),
                                      y + h / 2 - (text_size.b / 2),
                                      text_size.a,
                                      fmin(text_size.b, h));
    button_TTF.label.texture = init_text_texture(state, renderer, text, text_color);
    return button_TTF;
}

Button_TTF init_button_TTF_bordered(State *state, SDL_Renderer *renderer, char text[], u_int8_t parent_container)
{
    // Keep track of the total number of buttons
    state->GUI.num_buttons += 1;

    // Create a new Button_TTF
    Button_TTF button_TTF;

    // Position button according to "parent" container
    // (and save the information for later use)
    int x, y;
    int w, h;

    // Make rectangles
    w = (state->display_width / state->GUI.num_columns) / 2;
    h = (state->display_height / state->GUI.num_rows) / 2;
    x = state->containers[0].rect.x + (w / 2);
    y = state->containers[0].rect.y + (h / 2);
    button_TTF.rect = init_rect(x, y, w, h);

    // Never stretch the text, but shrink it if it is too large
    // for the button.
    Int_Tuple text_size = get_text_size(state, text);
    u_int8_t margin = 6;
    button_TTF.label.rect = init_rect(x + margin,
                                      y,
                                      fmin(text_size.a, w),
                                      fmin(text_size.b, h));
    button_TTF.label.texture = init_text_texture(state, renderer, text, state->colors.white);
    return button_TTF;
}

Button_TTF_Bordered init_button_border_TTF(State *state,
                                  SDL_Renderer *renderer,
                                  char text[],
                                  int border_thickness,
                                  int x, int y, int w, int h,
                                  u_int8_t parent_container)
{
    state->GUI.num_buttons_TTF_bordered += 1;

    // Create new button with border
    Button_TTF_Bordered button_TTF;
    button_TTF.parent_container = parent_container;
    
    button_TTF.parent_container = parent_container;
    x = state->containers[parent_container].rect.x + x;
    y = state->containers[parent_container].rect.y + y;
    button_TTF.rect = init_rect(x, y, w, h);

    // Create the border
    button_TTF.rect = init_rect(x, y, w, h);
    button_TTF.border_color = state->colors.black;

    // Create inner rect
    button_TTF.inner_rect = init_rect(x + border_thickness,
                                      y + border_thickness,
                                      w - (2*border_thickness),
                                      h - (2*border_thickness));
    button_TTF.rect_color = state->colors.white;                                      

    // Text label
    Int_Tuple text_size = get_text_size(state, text);
    u_int8_t margin = 2;
    button_TTF.label.rect = init_rect(button_TTF.inner_rect.x + margin,
                                      button_TTF.inner_rect.y - margin,
                                      fmin(text_size.a, button_TTF.inner_rect.w - margin),
                                      fmin(text_size.b, button_TTF.inner_rect.h - margin));
    button_TTF.label.texture = init_text_texture(state, renderer, text, state->colors.black);

    return button_TTF;                                      
}                         

Cell init_cell(int x, int y, int w, int h, SDL_Color color)
{
    Cell cell;
    cell.rect = init_rect(x, y, w, h);
    cell.color = color;

    return cell;
}

Grid init_grid_by_cells(State *state,
                              SDL_Color default_color,
                              int num_rows, int num_columns,
                              int x, int y, int cell_width, int cell_height,
                              u_int8_t parent_container)
{
    Grid grid;

    int x0 = state->containers[parent_container].rect.x + x;
    int y0 = state->containers[parent_container].rect.y + y;
    for (int row = 0; row < num_rows; ++row)
    {
        for (int column = 0; column < num_columns; ++column)
        {

            grid.matrix[row][column] = init_cell(x0 + column * cell_width,
                                     y0 + row * cell_height,
                                     cell_width,
                                     cell_height,
                                     default_color);
        }
    }

    grid.num_rows = num_rows;
    grid.num_columns = num_columns;
    grid.parent_container = parent_container;

    return grid;
}

Container init_container(State *state, SDL_Renderer *renderer, SDL_Color color, int x, int y, int w, int h)
{
    // Various GUI elements are positioned in relation to containers
    state->GUI.num_containers += 1;

    Container container;
    container.rect = init_rect(x, y, w, h);
    container.color = color;
    return container;
}

Container resize_container(Container input_container, int width, int height)
{
    input_container.rect = init_rect(input_container.rect.x,
                                     input_container.rect.y,
                                     width,
                                     height);
    return input_container;                                     
}

/**********************
 * GUI
 * *******************/

void init_container_layout(State *state, SDL_Renderer *renderer, int rows, int columns)
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
            state->containers[index].num_child_components = 0;                                                      
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
    state->colors.grey = init_color(40, 40, 40, 255);
    state->colors.white = init_color(255, 255, 255, 255);
    state->colors.blue = init_color(0, 0, 255, 255);

    

    /*
        GUI layout:

        
    */



    // Containers
    init_container_layout(state, renderer, rows, columns);

    // Components layout
    state->containers[4].rows = 1;
    state->containers[4].columns = 2;
    state->containers[4].num_child_components = 2;

    

    // Buttons
    state->buttons_TTF[0] = init_button_TTF(state, renderer, "Button 0", 4, 0, 0);
    state->buttons_TTF[1] = init_button_TTF(state, renderer, "Button 1", 4, 0, 1);                              
    

}