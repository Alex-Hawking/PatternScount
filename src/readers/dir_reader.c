#include "dir_reader.h"

bool is_text_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        return false;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch > 0 && (ch < 32 || ch == 127) && ch != '\t' && ch != '\n' && ch != '\r') {
            fclose(file);
            return false;
        }
    }

    fclose(file);
    return true;
}

void open_dir(char *path) {
    DIR *d;
    struct dirent *dir;
    struct stat fileStat;

    d = opendir(path);
    if (d == NULL ){
        perror("Error opening directory");
        exit(1);
    }

    while ((dir = readdir(d)) != NULL) {
        if (stat(dir->d_name, &fileStat) < 0) {
            continue;
        }

        if (S_ISREG(fileStat.st_mode)) {
            if (strcmp(dir->d_name, "text")) {
            }
        } else if (S_ISDIR(fileStat.st_mode)) {
        
        }
    }

    closedir(d);

}