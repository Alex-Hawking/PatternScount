#include "colours.h"

Colour create_colour(char *ansi_code) {
    Colour new_colour;
    new_colour.ansi_code = (char *)malloc(sizeof(char) * strlen(ansi_code) + 1);

    if (new_colour.ansi_code == NULL) {
        exit(1);
    }

    strcpy(new_colour.ansi_code, ansi_code);

    return new_colour;
}