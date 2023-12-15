#ifndef PRINTER_H
#define PRINTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colours.h"
#include "../helpers/helpers.h"

void initColours();

void printer(char *path, int line_number, int start, int end, char *line, int lineLength);

#endif