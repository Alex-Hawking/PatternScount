#include "main.h"

int main(int argc, char *argv[]) {

    /*
    Some stuff so I remember how to do it
    
        char *myString = "some text, this is a variable %s";
        char string2[100];
        sprintf(string2, myString, "bruh");
        printf("%s\n", string2);
    */
    
    int opt;

    while ((opt = getopt(argc, argv, "abc:")) != -1) {
        switch (opt) {
        case 'a':
            break;
        case 'b':
            break;
        case 'c':
            printf("Option c argument: %s\n", optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s [-a] [-b] [-c arg] regex path\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (argc - optind != 2) {
        fprintf(stderr, "Expected regex and path after options\n");
        return EXIT_FAILURE;
    }

    char *regex_pattern = argv[optind];
    char *path = argv[optind + 1];

    match_lines_file(path, regex_pattern);

    return 0;
}
