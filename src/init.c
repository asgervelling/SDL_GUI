#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

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
    font=TTF_OpenFont("resources/monogram.ttf", 16);
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
                                             state->colors.black);
    
    // state->buttons[btn_file].label.texture = SDL_CreateTextureFromSurface(renderer, temp);
    button.label.texture = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);
}

SDL_Texture* init_texture(State *state, SDL_Renderer *renderer, char text[])
{
    SDL_Surface *surface = TTF_RenderText_Solid(state->font, text, state->colors.black);
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

Button_TTF init_button_TTF(int x, int y, int w, int h)
{
    Button_TTF button_TTF;
    button_TTF.rect = init_rect(x, y, w, h);
    int margin = 6;
    button_TTF.label.rect = init_rect(x + margin,
                                      y + margin,
                                      w - 2 * margin,
                                      h - 2 * margin);
    // init the text here
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
    state->buttons[btn_file] = init_button_TTF(200, 200, 132, 32);
    state->buttons->label.texture = init_texture(state, renderer, "Goddag eiii");
   
}