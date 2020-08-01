#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#include "structs.h"

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
    font=TTF_OpenFont("resources/monogram.ttf", 36);
    if(!font) 
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
        SDL_Quit();
    }
    state->font = font;
    printf("Font loaded succesfully\n");
}

SDL_Texture* init_texture(State *state, SDL_Renderer *renderer, char text[])
{
    SDL_Surface *surface = TTF_RenderText_Solid(state->font, text, state->colors.white);
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

    printf("Parent container: %d\n\tParent container position: (%d, %d)\n\tButton position: (%d, %d)\n\n",
            parent_container,
            state->containers[parent_container].rect.x,
            state->containers[parent_container].rect.y,
            x, y);

    int margin = 6;
    
    // Never stretch the text, but shrink it if it is too large
    // for the button.
    Int_Tuple text_size = get_text_size(state, text);
    button_TTF.label.rect = init_rect(x + margin,
                                      y,
                                      fmin(text_size.a, w),
                                      fmin(text_size.b, h));
    button_TTF.label.texture = init_texture(state, renderer, text);

    return button_TTF;
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

    // Colors
    state->colors.black = init_color(0, 0, 0, 255);
    state->colors.grey = init_color(100, 100, 100, 255);
    state->colors.white = init_color(255, 255, 255, 255);
    state->colors.blue = init_color(0, 0, 255, 255);

    /*
        GUI components
    */

    // Containers
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
}