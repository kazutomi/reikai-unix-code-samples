/* llio/showfd.c */
#include <sys/types.h>  /* open */
#include <stdio.h>      /* perror, printf */
#include <stdlib.h>     /* exit */
#include <sys/stat.h>   /* open */
#include <fcntl.h>      /* open */

int main(void) {
    int fd;

    if ((fd = open("input.txt", O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }
    printf("fd = %d\n", fd);
    return 0;
}
