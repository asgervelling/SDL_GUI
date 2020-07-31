#ifndef STRUCTS
#define STRUCTS
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**********
 * GUI
 * *******/

typedef struct
{
    Uint8 r, g, b, a;
} Color;

typedef struct
{
    SDL_Color black;
    SDL_Color white;
    SDL_Color blue;
} Colors;

typedef struct
{
    SDL_Rect rect;
    SDL_Texture *texture;
} Label;

/**********
 * BUTTONS
 * *******/

typedef struct
{
    SDL_Rect rect;
    SDL_Texture *texture;
} Button_IMG;

typedef struct
{
    SDL_Rect rect;
    Label label;
} Button_TTF;

enum Buttons
{
    btn_file,
    btn_file_open,
    btn_file_save
};

/**********
 * GUI Rectangles
 * *******/

typedef struct
{
    SDL_Rect rect;
} Container;

typedef struct
{
    SDL_Rect rect;
} Graphic_User_Interface;

/**********
 * ANIMATION
 * *******/
typedef struct
{
    int frame;
    int current_anim;
} Animation_Helper;

/**********
 * STATE
 * *******/
typedef struct
{
    // GUI
    Graphic_User_Interface GUI;
    Button_TTF buttons[1];

    // Animation
    Animation_Helper GUI_anim;

    // Font
    TTF_Font *font;

    // Rendering
    SDL_Renderer *renderer;
    Colors colors;
} State;

#endif