#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "structs.h"

#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))

int get_indentation(char line[])
{
    // Return the indentation level of a given line
    int max = 12;
    int indentation = 0;
    for (int i = 0; i < max; ++i)
    {
        if (line[i] == ' ')
        {
            ++indentation;
        }
    }
    return indentation;
}

int get_word_from_string(char word[], char string[])
{
    
    // Return 1 if the string contains the word
    char* word_temp = (char*)malloc(LEN(word) * sizeof(char));
    char* string_temp = (char*)malloc(LEN(string) * sizeof(char));
    for (int i = 0; i < LEN(string); ++i)
    {
        
        printf("%c", string[i]);
    }
    free(word_temp);
    free(string_temp);

    return 1;
}

int read_file(State *state, char filename[])
{
    FILE *fp = fopen(filename, "r");
    
    if(fp == NULL)
    {
        perror("Error in opening file\n");
        SDL_Quit();
    }

    int max = 40;
    char line[max];

    // Components
    u_int8_t containers = 0;
    u_int8_t buttons = 0;
    u_int8_t grids = 0;
    while(fgets(line, max, fp))
    {
        u_int8_t indentation = 0;
        if (line[0] != '\n')
        {
            printf("%s", line);
            if (line[0] == 'c')
            {
                ++containers;
            }

            if (line[0] == ' ')
            {
                ++indentation;
            }

            if (strcmp("button", line))
            {
                ++buttons;
            }
        }
        
    }
    printf("\n\nContainers: %d\nButtons: %d\n", containers, buttons);
    
    fclose(fp);

    return 0;
}