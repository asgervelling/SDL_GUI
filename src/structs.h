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
    // A rect with some text and a shadow
    SDL_Rect rect;
    SDL_Rect rect_shadow;
    SDL_Texture *texture;
    SDL_Texture *texture_shadow;
} Label;

/**********
 * BUTTONS
 * *******/

typedef struct
{
    // Can be used for any rectangle
    SDL_Rect rects[4];
    SDL_Color colors[4];
} Border;

typedef struct
{
    SDL_Rect rect;
    SDL_Texture *texture;
} Button_IMG;

typedef struct
{
    SDL_Rect rect;
    Border border;
    Label label;
    SDL_Color color;
    SDL_Color text_color;

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

enum Borders
{
    top,
    bottom,
    left,
    right
};

/**********
 * GUI Rectangles
 * *******/

typedef struct
{
    SDL_Rect rect;
    SDL_Color color;
    int rows, columns;
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

    int num_rows, num_columns;
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
 * CONTROL
 * *******/

typedef struct
{
    int x, y;
    SDL_Rect hovering_rect;
} Mouse;

typedef struct
{
    Mouse mouse;
} Control;

/**********
 * STATE
 * *******/
typedef struct
{
    // GUI with all of its components
    Graphic_User_Interface GUI;
    Container containers[6144];
    Button_TTF buttons_TTF[16];
    Button_TTF_Bordered buttons_TTF_bordered[8];
    Button_TTF_Dropdown buttons_TTF_dropdown[8];
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

    // Control
    Control control;
} State;

#endif