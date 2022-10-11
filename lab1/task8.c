#include <stdio.h>
#include <stdlib.h>

void copy_file(FILE*, FILE*);


int main(int argc, char *argv[]){
    char* file1, *file2;
    int got_input = 0;
    if (argc == 3) {
        file1 = argv[1];
        file2 = argv[2];
    } else if (argc == 1) {
        got_input = 1;
        file1 = calloc(30, sizeof(*file1));
        file2 = calloc(30, sizeof(*file2));
        printf("Enter first file name: ");
        scanf("%s", file1);
        printf("Enter second file name: ");
        scanf("%s", file2);
    } else {
        printf("Usage: %s [file1 file2]\n", argv[0]);
        exit(1);
    }
    FILE* from = fopen(file1, "r");
    FILE* to = fopen(file2, "w");
    copy_file(to, from);
    fclose(to);
    fclose(from);
    if (got_input) {
        free(file1);
        free(file2);
    }
    return 0;
}

void copy_file(FILE* to, FILE* from){
    int rc;
    while ((rc = fgetc(from)) != EOF)
        fputc(rc, to);
}

