#ifndef FILE_IO
#define FILE_IO

int get_indentation(char line[]);
int get_word_from_string(char word[], char string[]);
int read_file(State *state, char filename[]);

#endif