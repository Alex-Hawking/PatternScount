#include "dir_reader.h"

void open_dir(char *path, char *regex_pattern) {
    DIR *d;
    struct dirent *dir;
    struct stat fileStat;
    char fullPath[1024]; 

    d = opendir(path);
    if (d == NULL) {
        perror("Error opening directory");
        exit(1);
    }

    while ((dir = readdir(d)) != NULL) {

        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
            continue;
        }

        if (path[strlen(path) - 1] == '/') {
            snprintf(fullPath, sizeof(fullPath), "%s%s", path, dir->d_name);
        } else {
            snprintf(fullPath, sizeof(fullPath), "%s/%s", path, dir->d_name);
        }

        if (stat(fullPath, &fileStat) < 0) {
            perror("stat");
            continue;
        }

        if (S_ISREG(fileStat.st_mode)) {
            match_lines_file(fullPath, regex_pattern);
        } else if (S_ISDIR(fileStat.st_mode)) {
            printf("Directory: %s\n", fullPath);
        }
    }

    closedir(d);
}