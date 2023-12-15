#ifndef HELPERS_H
#define HELPERS_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/stat.h>

int get_number_of_cores();
int get_terminal_width();
char check_path(char *path);

#endif 