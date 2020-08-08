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

Border init_border(SDL_Rect rect, int border_thickness)
{
    // Gives the input rectangle a border. Works on any rectangle
    Border border;

    // Colors of the borders
    SDL_Color border_color_0, border_color_1;
    border_color_0 = init_color(0, 0, 0, 255);
    border_color_1 = init_color(border_color_0.r + 120,
                                border_color_0.g + 120,
                                border_color_0.b + 120,
                                255);
    border.colors[top] = border_color_0;
    border.colors[right] = border_color_0;
    border.colors[bottom] = border_color_1;
    border.colors[left] = border_color_1;

    // Dimensions
    int x, y;
    int w, h;

    x = rect.x;
    y = rect.y;
    w = rect.w;
    h = rect.h;

    border.rects[top] = init_rect(x, y, w, border_thickness);
    border.rects[bottom] = init_rect(x,
                                     y + h - border_thickness,
                                     w - border_thickness,
                                     border_thickness);
    border.rects[left] = init_rect(x, y + border_thickness, border_thickness, h);
    border.rects[right] = init_rect(x + w - border_thickness,
                                    y,
                                    border_thickness,
                                    h);
    return border;
}

Button_TTF init_button_TTF(State *state, SDL_Renderer *renderer, char text[], u_int8_t parent_container, int row, int column)
{
    // Keep track of the total number of buttons
    state->GUI.num_buttons += 1;    

    // Create a new Button_TTF
    Button_TTF button_TTF;

    // Position button according to "parent" container
    // (and save the information for later use)
    int x, y;
    int w, h;
    Int_Tuple text_size = get_text_size(state, text);

    // Colors
    SDL_Color button_color, text_color, text_shadow_color;
    text_color = state->colors.black;
    text_shadow_color = init_color(0, 0, 0, 40);
    button_color = init_color(state->containers[parent_container].color.r - 122,
                            state->containers[parent_container].color.g - 122,
                            state->containers[parent_container].color.b - 122,
                            255);
    button_TTF.color = button_color;

    // Size the buttons according to the number of rows and columns in a container
    w = state->containers[parent_container].rect.w / state->containers[parent_container].columns;
    h = state->containers[parent_container].rect.h / state->containers[parent_container].rows;
    x = state->containers[parent_container].rect.x + (column * w);
    y = state->containers[parent_container].rect.y + (row * h);
    
    // Make the rectangle with a border
    button_TTF.rect = init_rect(x, y, w, h);
    button_TTF.border = init_border(button_TTF.rect, 4);
                                       

    // TEXT:
    // Never stretch the text, but shrink it if it is too large
    // for the button.
    u_int8_t margin = 6;
    
    // Text
    int x_label, y_label, w_label, h_label;
    text_size.a = fmin(text_size.a, w - 4 * margin);
    x_label = x + w / 2 - (text_size.a / 2);
    y_label = y + h / 2 - (text_size.b / 2);
    w_label = text_size.a;
    h_label = fmin(text_size.b, h);
    button_TTF.label.rect = init_rect(x_label, y_label, w_label, h_label);
    button_TTF.label.texture = init_text_texture(state, renderer, text, text_color);

    // Text shadow
    button_TTF.label.rect_shadow = init_rect(x_label + 2,
                                             y_label + 2,
                                             w_label,
                                             h_label);
    button_TTF.label.texture_shadow = init_text_texture(state, renderer, text, text_shadow_color);                                             
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
    state->colors.grey = init_color(40, 40, 40, 255);
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

