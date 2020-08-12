#include "structs.h"
#include "init.h"

Container init_container(State *state, SDL_Renderer *renderer, SDL_Color color, int x, int y, int w, int h)
{
    // Various GUI elements are positioned in relation to containers
    state->GUI.num_containers += 1;

    Container container;
    container.rect = init_rect(x, y, w, h);
    container.color = color;
    return container;
}

Container resize_container(Container input_container, int width, int height)
{
    input_container.rect = init_rect(input_container.rect.x,
                                     input_container.rect.y,
                                     width,
                                     height);
    return input_container;                                     
}

Border init_border(SDL_Rect rect, int border_thickness)
{
    // Gives the input rectangle a border. Works on any rectangle
    Border border;

    // Colors of the borders
    SDL_Color border_color_0, border_color_1, border_color_2, border_color_3;
    border_color_0 = init_color(46, 46, 46, 255);
    border_color_1 = init_color(181, 181, 181, 255);
    border_color_2 = init_color(212, 212, 212, 255);
    border_color_3 = init_color(94, 94, 94, 255);
    border.colors[top] = border_color_0;
    border.colors[bottom] = border_color_1;
    border.colors[left] = border_color_2;
    border.colors[right] = border_color_3;

    // Dimensions
    int x, y;
    int w, h;

    x = rect.x;
    y = rect.y;
    w = rect.w;
    h = rect.h;

    border.rects[top] = init_rect(x + border_thickness, y, w - 2 * border_thickness, border_thickness);
    border.rects[bottom] = init_rect(x + border_thickness,
                                     y + h - border_thickness,
                                     w - 2 * border_thickness,
                                     border_thickness);
    border.rects[left] = init_rect(x, y, border_thickness, h);
    border.rects[right] = init_rect(x + w - border_thickness,
                                    y,
                                    border_thickness,
                                    h);
    return border;
}

Button_TTF init_button_TTF(State *state, SDL_Renderer *renderer, char text[], u_int8_t parent_container, int row, int column)
{
    // Keep track of the total number of buttons
    state->GUI.num_buttons += 1;    

    // Create a new Button_TTF
    Button_TTF button_TTF;

    // Position button according to "parent" container
    // (and save the information for later use)
    int x, y;
    int w, h;
    Int_Tuple text_size = get_text_size(state, text);

    // Colors
    SDL_Color button_color, text_color, text_shadow_color;
    text_color = state->colors.black;
    text_shadow_color = init_color(0, 0, 0, 80);
    button_color = state->colors.grey;
    button_TTF.color = button_color;

    // Size the buttons according to the number of rows and columns in a container
    w = state->containers[parent_container].rect.w / state->containers[parent_container].columns;
    h = state->containers[parent_container].rect.h / state->containers[parent_container].rows;
    x = state->containers[parent_container].rect.x + (column * w);
    y = state->containers[parent_container].rect.y + (row * h);
    
    // Make the rectangle with a border
    button_TTF.rect = init_rect(x, y, w, h);
    button_TTF.border = init_border(button_TTF.rect, 4);
                                       

    // TEXT:
    // Never stretch the text, but shrink it if it is too large
    // for the button.
    u_int8_t margin = 6;
    
    // Text
    int x_label, y_label, w_label, h_label;
    text_size.a = fmin(text_size.a, w - 4 * margin);
    x_label = x + w / 2 - (text_size.a / 2);
    y_label = y + h / 2 - (text_size.b / 2);
    w_label = text_size.a;
    h_label = fmin(text_size.b, h);
    button_TTF.label.rect = init_rect(x_label, y_label, w_label, h_label);
    button_TTF.label.texture = init_text_texture(state, renderer, text, text_color);

    // Text shadow
    button_TTF.label.rect_shadow = init_rect(x_label + 3,
                                             y_label + 3,
                                             w_label,
                                             h_label);
    button_TTF.label.texture_shadow = init_text_texture(state, renderer, text, text_shadow_color);                                             
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