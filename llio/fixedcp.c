/* llio/fixedcp.c */
#include <sys/types.h>  /* open, read, write */
#include <stdio.h>      /* perror */
#include <stdlib.h>     /* exit */
#include <sys/stat.h>   /* open */
#include <fcntl.h>      /* open */
#include <sys/uio.h>    /* read, write */
#include <unistd.h>     /* close, read, write */

#define INFILE          "input.file"
#define OUTFILE         "output.file"

enum {
    BUFSIZE = 1024,
};

int main(void) {
    int ifd, ofd;
    ssize_t cc;
    char buf[BUFSIZE];

    if ((ifd = open(INFILE, O_RDONLY)) == -1) {
        perror("open input file");
        exit(1);
    }
    if ((ofd = open(OUTFILE, O_WRONLY|O_CREAT|O_TRUNC, 0666)) == -1) {
        perror("open output file");
        exit(1);
    }
    while ((cc = read(ifd, buf, sizeof(buf))) > 0) {
        if (write(ofd, buf, cc) == -1) {
            perror("write");
            exit(1);
        }
    }
    if (cc == -1) {
        perror("read");
        exit(1);
    }
    /* cc = 0; エラーなしで EOF に達した */
    if (close(ofd) == -1) {
        perror("close output file");
        exit(1);
    }
    if (close(ifd) == -1) {
        perror("close input file");
        exit(1);
    }
    return 0;
}
