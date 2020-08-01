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

void put_text_on_button(State *state, SDL_Renderer *renderer, Button_TTF button, char text[])
{
    SDL_Surface *temp = TTF_RenderText_Solid(state->font,
                                             "hej",
                                             state->colors.white);
    
    // state->buttons[btn_file].label.texture = SDL_CreateTextureFromSurface(renderer, temp);
    button.label.texture = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);
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
    if(TTF_SizeText(state->font, text ,&w,&h))
    {
        printf("TTF_SizeText: %s\n", TTF_GetError());
        SDL_Quit();
    } else 
    {
        printf("width=%d height=%d\n",w,h);
    }
    Int_Tuple tuple;
    tuple.a = w;
    tuple.b = h;
    return tuple;
}

Button_TTF init_button_TTF(State *state, SDL_Renderer *renderer, char text[], int x, int y, int w, int h)
{
    Button_TTF button_TTF;
    button_TTF.rect = init_rect(x, y, w, h);
    int margin = 6;
    
    // init the text here
    Int_Tuple text_size = get_text_size(state, text);
    button_TTF.label.rect = init_rect(x + margin,
                                      y,
                                      fmin(text_size.a, w),
                                      fmin(text_size.b, h));
    button_TTF.label.texture = init_texture(state, renderer, text);

    return button_TTF;
}

/**********************
 * GUI
 * *******************/

void init_GUI(State *state, SDL_Renderer *renderer)
{
    // Colors
    state->colors.black = init_color(0, 0, 0, 255);
    state->colors.white = init_color(255, 255, 255, 255);
    state->colors.blue = init_color(0, 0, 255, 255);

    // GUI components
    state->buttons[btn_file] = init_button_TTF(state, renderer, "text", 200, 200, 132, 32);   
}