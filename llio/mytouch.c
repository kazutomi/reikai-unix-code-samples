/* llio/mytouch.c */
#include <sys/types.h>  /* open */
#include <stdio.h>      /* perror */
#include <stdlib.h>     /* exit */
#include <sys/stat.h>   /* open */
#include <fcntl.h>      /* open */
#include <unistd.h>     /* close */

int main(void) {
    int fd;

    if ((fd = open("empty.file", O_WRONLY|O_CREAT|O_TRUNC, 0666)) == -1) {
        perror("open");
        exit(1);
    }
    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }
    return 0;
}
