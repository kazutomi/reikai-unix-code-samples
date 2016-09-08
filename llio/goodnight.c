/* llio/goodnight.c */
#include <sys/types.h>  /* lseek, open, write */
#include <stdio.h>      /* perror */
#include <stdlib.h>     /* exit */
#include <sys/stat.h>   /* open */
#include <fcntl.h>      /* open */
#include <sys/uio.h>    /* write */
#include <unistd.h>     /* close, lseek, write */

int main(void) {
    int fd;

    if ((fd = open("bye.txt", O_WRONLY)) < 0) {
        perror("open");
        exit(1);
    }
    if (lseek(fd, 5, SEEK_SET) == -1) {
        perror("lseek");
        exit(1);
    }
    if (write(fd, "night!\n", 7) != 7) {
        perror("write");
        exit(1);
    }
    if (close(fd) < 0) {
        perror("close");
        exit(1);
    }
    return 0;
}
