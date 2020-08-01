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
    /*
    state->font = TTF_OpenFont("resources/monogram.ttf", 12);
    if (!state->font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
    */

    
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
    SDL_Color cool = {0, 0, 0, 0};
    SDL_Surface *temp = TTF_RenderText_Solid(state->font,
                                             "test text",
                                             cool);
    
    
    button.label.texture = SDL_CreateTextureFromSurface(renderer, temp);
    printf("                test label rect: %d %d %d %d\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n",
                                                    state->buttons[btn_file].label.rect.x,
                                                    state->buttons[btn_file].label.rect.y,
                                                    state->buttons[btn_file].label.rect.w,
                                                    state->buttons[btn_file].label.rect.h);
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

    SDL_Surface* surface_text = TTF_RenderText_Solid(state->font, "yeeees", state->colors.black);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface_text);
    state->buttons[0].label.texture = message;

    // put_text_on_button(state, renderer, state->buttons[btn_file], "File");

    /*
    SDL_Color cool = {0, 0, 0, 255};
    SDL_Surface *temp = TTF_RenderText_Blended(state->font,
                                             "test",
                                             cool);
    
    
    state->buttons[btn_file].label.texture = SDL_CreateTextureFromSurface(renderer, temp);
    if(!state->buttons[btn_file].label.texture)
    {
        printf("!texture (init_GUI())\n");
    }
    printf("                test label rect: %d %d %d %d\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n",
                                                    state->buttons[btn_file].label.rect.x,
                                                    state->buttons[btn_file].label.rect.y,
                                                    state->buttons[btn_file].label.rect.w,
                                                    state->buttons[btn_file].label.rect.h);
    SDL_FreeSurface(temp);
    */
}