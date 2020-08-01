#ifndef STRUCTS
#define STRUCTS
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct
{
    int a, b;
} Int_Tuple;

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

    // Simulate OOP for easier positioning
    u_int8_t parent_container;
} Button_TTF;

typedef struct
{
    SDL_Rect rect;
    u_int8_t border_thickness;
    u_int8_t parent_container;    
} Button_TTF_Bordered;


enum Buttons
{
    btn_file,
    btn_file_open,
    btn_file_save,
};

/**********
 * GUI Rectangles
 * *******/

typedef struct
{
    SDL_Rect rect;
    SDL_Color color;
} Container;

typedef struct
{
    SDL_Rect rect;
    u_int8_t num_buttons, num_containers;
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
    // GUI with all of its components
    Graphic_User_Interface GUI;
    Container containers[2];
    Button_TTF buttons_TTF[5];

    // Animation
    Animation_Helper GUI_anim;

    // Font
    TTF_Font *font;

    // Rendering
    SDL_Renderer *renderer;
    Colors colors;
} State;

#endif