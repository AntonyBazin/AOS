#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
//#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    char *fname = argv[1];   //try "/dev/stdout"
    struct stat st_buf;
    stat(fname, &st_buf);
    printf("name: %s\n", fname);
    printf("device: %lu\n", st_buf.st_dev);
    printf("inode: %lu\n", st_buf.st_ino);
    printf("mode: %d, meaning:\n", st_buf.st_mode);
    if (S_ISREG(st_buf.st_mode))
        printf("regular file\n");
    else if (S_ISDIR(st_buf.st_mode))
        printf("directory\n");
    else if (S_ISCHR(st_buf.st_mode))
        printf("symbolic device\n");
    else if (S_ISBLK(st_buf.st_mode))
        printf("block device\n");
    printf("hard links count: %lu\n", st_buf.st_nlink);
    printf("UID: %d\n", st_buf.st_uid);
    printf("GID: %d\n", st_buf.st_gid);
    printf("device type: %lu\n", st_buf.st_rdev);
    printf("size: %lu bytes\n", st_buf.st_size);
    printf("filesystem block size: %ld\n", st_buf.st_blksize);
    printf("filesystem blocks allocated: %ld\n", st_buf.st_blocks);
    printf("last access: %s\n", asctime(gmtime(&st_buf.st_atime)));
    printf("last modification: %s\n", asctime(gmtime(&st_buf.st_mtime)));
    printf("last change: %s\n", asctime(gmtime(&st_buf.st_ctime)));
    exit(0);
}