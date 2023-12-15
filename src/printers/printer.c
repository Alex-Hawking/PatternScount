#include "printer.h"

Colour red;
Colour clear;
Colour bold;

void initColours() {
    red = create_colour("\033[0;31m");
    clear = create_colour("\033[0;0m");
    bold = create_colour("\033[1m");
}

int intStrLen(char *input) {
    size_t length_size_t = strlen(input);
    int length_int = (int)length_size_t; 
    return length_int;
}

void printer(char *path, int line_number, int start, int end, char *line, int lineLength) {

    char header[1024];

    sprintf(header, "%s%s  %d%s  ", bold.ansi_code,path, line_number, clear.ansi_code);
    int header_len = intStrLen(header);
    int match_len = end - start;

    const int MAX_LENGTH = (get_terminal_width() - header_len - match_len) / 2;

    printf("%s", header);


    if (start > MAX_LENGTH) {
            printf("...%.*s", MAX_LENGTH, line + start - MAX_LENGTH);
        } else {
            printf("%.*s", start, line);
        }

        printf("%s%.*s%s",red.ansi_code, end - start, &line[start], clear.ansi_code);

        if (lineLength - end > MAX_LENGTH) {
            printf("%.*s...", MAX_LENGTH, &line[end]);
        } else {
            printf("%.*s", lineLength - end, &line[end]);
        }

        printf("\n");
}