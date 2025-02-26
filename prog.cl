int main(int argc, char** argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
        printf("File opened successfully: %s\n", argv[1]);
        yyin = file;
    } else {
        printf("Reading from stdin...\n");
    }
    yylex();
    return 0;
}
