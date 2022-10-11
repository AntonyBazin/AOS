#include <stdio.h>
#include <stdlib.h>

void cpy();

int main(int argc, char *argv[])
{
    char* file1, *file2;
    if (argc == 3) {
        file1 = argv[1];
        file2 = argv[2];
    } else {
        printf("Usage: %s [f1 file2]\n", argv[0]);
        exit(1);
    }
    freopen(file1, "r", stdin);
    freopen(file2, "w", stdout);
    cpy();
    freopen("/dev/stdin", "r", stdin);
    freopen("/dev/stdout", "w", stdout);
    return 0;
}

void cpy(){
    int rc;
    while ((rc = getchar()) != EOF)
        putchar(rc);
}
