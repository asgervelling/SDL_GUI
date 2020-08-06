#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "structs.h"
#include "init.h"

void test_grid_colors(State *state)
{
    int index = 0;
    int rgba_value;
    int step = floor(255 / (state->grid.num_rows * state->grid.num_columns));
    for (int row = 0; row < state->grid.num_rows; ++row)
    {
        for (int column = 0; column < state->grid.num_columns; ++column)
        {
            ++index;
            rgba_value = index * step;
            state->grid.matrix[row][column].color = init_color(rgba_value, rgba_value, rgba_value, rgba_value);
            printf("rgba value [%d][%d]: %d\n", row, column, rgba_value);

        }
    }
}