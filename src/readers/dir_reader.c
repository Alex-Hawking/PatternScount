#include "dir_reader.h"

void open_dir(char *path, char *regex_pattern) {
    DIR *d;
    struct dirent *dir;
    struct stat fileStat;
    char fullPath[1024]; 
    pid_t pid;

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

        if (lstat(fullPath, &fileStat) < 0) {
            perror("lstat");
            continue;
        }

        if (S_ISREG(fileStat.st_mode)) {
            pid = fork();
            if (pid == -1) {
                perror("fork");
                continue;
            }

            if (pid == 0) { 
                match_lines_file(fullPath, regex_pattern);
                exit(0);
            } else { 
                int status;
                waitpid(pid, &status, 0); 
            }
        } else if (S_ISDIR(fileStat.st_mode) && !S_ISLNK(fileStat.st_mode)) {
            open_dir(fullPath, regex_pattern);
        }
    }

    closedir(d);
}