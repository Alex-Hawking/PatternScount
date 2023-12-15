#include "main.h"

int main(int argc, char *argv[]) {
    
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

    initColours();

    match_lines_file(path, regex_pattern);

    return 0;
}
