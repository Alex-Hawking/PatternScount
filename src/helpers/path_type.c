#include "helpers.h"

char check_path(char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        perror("The path does not exist.\n");
        exit(1);
    } else if (S_ISREG(path_stat.st_mode)) {
        return 'f';
    } else if (S_ISDIR(path_stat.st_mode)) {
        return 'd';
    } else {
        perror("Invalid file type.\n");
        exit(1);
    }
}