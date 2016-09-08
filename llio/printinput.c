/* llio/printinput.c */
#include <sys/types.h>  /* open, read, write */
#include <stdio.h>      /* perror */
#include <stdlib.h>     /* exit */
#include <sys/stat.h>   /* open */
#include <fcntl.h>      /* open */
#include <sys/uio.h>    /* read, write */
#include <unistd.h>     /* close, read, write */

int main(void) {
    int ifd;
    ssize_t cc;
    char buf[1024];

    if ((ifd = open("input.file", O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }
    while ((cc = read(ifd, buf, sizeof(buf))) > 0) {
        /* ccバイトだけ読めたので，ccバイト書く */
        if (write(STDOUT_FILENO, buf, cc) < cc) {
            perror("write");
            exit(1);
        }
    }
    if (cc == -1) {
        perror("read");
        exit(1);
    }
    if (close(ifd) == -1) {
        perror("close");
        exit(1);
    }
    return 0;
}
