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

Button_TTF init_button_TTF(State *state, SDL_Renderer *renderer, char text[], int x, int y, int w, int h, u_int8_t parent_container)
{
    // Keep track of the total number of buttons
    state->GUI.num_buttons += 1;

    // Create a new Button_TTF
    Button_TTF button_TTF;

    // Position button according to "parent" container
    // (and save the information for later use)
    button_TTF.parent_container = parent_container;
    x = state->containers[parent_container].rect.x + x;
    y = state->containers[parent_container].rect.y + y;
    button_TTF.rect = init_rect(x, y, w, h);

    u_int8_t margin = 6;
    
    // Never stretch the text, but shrink it if it is too large
    // for the button.
    Int_Tuple text_size = get_text_size(state, text);
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

/**********************
 * GUI
 * *******************/

void init_GUI(State *state, SDL_Renderer *renderer)
{
    // The GUI struct should only hold information about
    // the number of each of its components.
    // By keeping the components seperate, they become
    // more reusable.
    state->GUI.num_containers = 0;
    state->GUI.num_buttons = 0;
    state->GUI.num_buttons_TTF_bordered = 0;

    // Colors
    state->colors.black = init_color(0, 0, 0, 255);
    state->colors.grey = init_color(100, 100, 100, 255);
    state->colors.white = init_color(255, 255, 255, 255);
    state->colors.blue = init_color(0, 0, 255, 255);

    /*
        GUI components
    */

    // Containers do not have children,
    // but each element further down in the tree hold an 'int parent_container'
    // which is a pointer to the array subscript of that container.
    state->containers[0] = init_container(state,
                                          renderer,
                                          state->colors.grey,
                                          0,
                                          0,
                                          320,
                                          640);
    state->containers[1] = init_container(state,
                                          renderer,
                                          state->colors.white,
                                          320,
                                          0,
                                          640,
                                          640);

    // Buttons
    state->buttons_TTF[btn_file] = init_button_TTF(state, renderer, "File", 0, 0, 132, 32, 0);
    state->buttons_TTF[btn_file_open] = init_button_TTF(state, renderer, "Open", 0, 0, 132, 32, 1);

    state->buttons_TTF_bordered[0] = init_button_border_TTF(state, renderer, "Test jaaaaaaaaaaaaa", 4, 0, 100, 132, 32, 1);

    // Colorful grid
    state->grid = init_grid_by_cells(state,
                                     state->colors.blue,
                                     8, 8,
                                     0, 32,
                                     32, 32,
                                     0);
    
    test_grid_colors(state);
    // File IO
    read_file(state, "GUI_files/testfile.txt");
                                   
}