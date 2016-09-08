/* llio/writebye.c */
#include <sys/types.h>  /* open, write */
#include <stdio.h>      /* perror */
#include <stdlib.h>     /* exit */
#include <sys/stat.h>   /* open */
#include <fcntl.h>      /* open */
#include <sys/uio.h>    /* write */
#include <unistd.h>     /* close, write */

int main(void) {
    int fd;

    if ((fd = open("bye.txt", O_WRONLY)) == -1) {
        perror("open");
        exit(1);
    }
    if (write(fd, "See you", 7) != 7) {
        perror("write");
        exit(1);
    }
    if (write(fd, " later!", 7) != 7) {
        perror("write");
        exit(1);
    }
    if (write(fd, "\nBye!\n", 6) != 6) {
        perror("write");
        exit(1);
    }
    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }
    return 0;
}
