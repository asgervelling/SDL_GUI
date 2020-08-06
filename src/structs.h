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
    SDL_Color grey;
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
    SDL_Rect inner_rect;
    u_int8_t border_thickness;
    u_int8_t parent_container;
    SDL_Color rect_color;
    SDL_Color border_color;
    Label label;
} Button_TTF_Bordered;

typedef struct
{
    SDL_Rect rect;
    Button_TTF buttons[3]; // Perhaps change this to a struct and get a LEN(arr) in the init() function?
} Button_TTF_Dropdown;

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
    SDL_Color color;
} Cell;

typedef struct
{
    // A grid made up of cells. Good for LED grids on speakers, for example.
    int num_rows, num_columns;
    SDL_Rect rect;
    u_int8_t parent_container;

    // Don't need to use all these rows and columns
    Cell matrix[96][64];
} Grid;

typedef struct
{
    SDL_Rect rect;
    u_int8_t num_buttons, num_buttons_TTF_bordered;
    u_int8_t num_containers;
    
    u_int8_t num_rows, num_columns;
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
    Button_TTF_Bordered buttons_TTF_bordered[1];
    Button_TTF_Dropdown buttons_TTF_dropdown[1];
    Grid grid;

    // Animation
    Animation_Helper GUI_anim;

    // Font
    TTF_Font *font;

    // Rendering
    SDL_Renderer *renderer;
    Colors colors;

    // State settings
    int display_width, display_height;
} State;

#endif