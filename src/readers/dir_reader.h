#ifndef DIR_READER_H
#define DIR_READER_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>

#include "file_reader.h"

bool is_text_file(const char *filename);
void open_dir(char *path, char *regex_pattern);

#endif