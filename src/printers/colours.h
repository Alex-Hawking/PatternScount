#ifndef COLOURS_H
#define COLOURS_H

#include <stdlib.h>
#include <string.h>

typedef struct{
    char *ansi_code;
} Colour; 

Colour create_colour(char *ansi_code);

#endif