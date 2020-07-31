#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "structs.h"

Rect init_rect(int x, int y, int w, int h)
{
    Rect rect;
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
    state->font = TTF_OpenFont("resources/monogram.ttf", 36);
}

void put_text_on_button(State *state, SDL_Renderer *renderer, Button_TTF button, char text[])
{
    int margin = 6;
    SDL_Surface *temp = TTF_RenderText_Blended(state->font, text, state->colors.black);
    button.label.rect = init_rect(button.rect.x + margin,
                                  button.rect.y + margin,
                                  button.rect.w - 2*margin,
                                  button.rect.h - 2*margin);
    button.label.texture = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);
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
    button_TTF.margin = 6;
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
    put_text_on_button(state, renderer, state->buttons[btn_file], "File");
    
}