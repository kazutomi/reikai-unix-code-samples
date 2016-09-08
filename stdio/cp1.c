/* stdio/cp1.c */
#include <errno.h>      /* errno */
#include <stdio.h>      /* fclose, fopen, fprintf, getc, perror, putc */
#include <stdlib.h>     /* exit */
#include <string.h>     /* strerror */

int main(int argc, char *argv[]) {
    FILE *sfp, *dfp;
    int c;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <infile> <outfile>\n", argv[0]);
        exit(1);
    }
    if ((sfp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "fopen: %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }
    if ((dfp = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "fopen: %s: %s\n", argv[2], strerror(errno));
        exit(1);
    }
    while ((c = getc(sfp)) != EOF) { 
        if (putc(c, dfp) == EOF) {
            perror("putc");
            exit(1);
        }
    }
    fclose(dfp);
    fclose(sfp);
    return 0;
}
