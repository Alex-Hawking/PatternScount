#include "helpers.h"

int get_terminal_width() {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        perror("ioctl");
        return -1; 
    }
    return w.ws_col; 
}