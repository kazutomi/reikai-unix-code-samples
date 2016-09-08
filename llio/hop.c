/* llio/hop.c */
#include <sys/types.h>  /* lseek, open, write */
#include <stdio.h>      /* perror */
#include <stdlib.h>     /* exit */
#include <sys/stat.h>   /* open */
#include <fcntl.h>      /* open */
#include <sys/uio.h>    /* write */
#include <unistd.h>     /* close, lseek, write */

int main(void) {
    int d, i;

    if ((d = open("hop.out", O_WRONLY|O_CREAT|O_TRUNC, 0666)) == -1) {
        perror("open");
        exit(1);
    }
    for (i = 0; i < 8; i++) {
        if (write(d, "hop", 3) == -1) {
            perror("write");
            exit(1);
        }
        if (lseek(d, 3, SEEK_CUR) == -1) {
            perror("lseek");
            exit(1);
        }
    }
    close(d); 
    return 0;
}
