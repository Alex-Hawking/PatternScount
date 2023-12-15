#ifndef DIR_READER_H
#define DIR_READER_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>

bool is_text_file(const char *filename);
void open_dir(char *path);

#endif