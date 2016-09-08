/* llio/writeout.c */
#include <sys/types.h>  /* open, read, write */
#include <stdio.h>      /* perror */
#include <stdlib.h>     /* exit */
#include <sys/stat.h>   /* open */
#include <fcntl.h>      /* open */
#include <sys/uio.h>    /* read, write */
#include <unistd.h>     /* close, read, write */

int main(void) {
    int ofd;
    ssize_t cc;
    char buf[1024];

    if ((ofd = open("output.file", O_WRONLY|O_CREAT|O_TRUNC, 0666)) == -1) {
        perror("open");
        exit(1);
    }
    while ((cc = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
        if (write(ofd, buf, cc) < cc) {
            perror("write");
            exit(1);
        }
    }
    if (cc == -1) {
        perror("read");
        exit(1);
    }
    if (close(ofd) == -1) {
        perror("close");
        exit(1);
    }
    return 0;
}
