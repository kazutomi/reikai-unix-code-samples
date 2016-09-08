/* stdio/showfile.c */
#include <stdio.h>      /* fclose, fopen, getc, perror, putchar */
#include <stdlib.h>     /* exit */

#define INFILE          "hello.txt"

int main(void) {
    FILE *fp;
    int c;

    if ((fp = fopen(INFILE, "r")) == NULL) {
        perror("fopen");
        exit(1);
    }
    while ((c = getc(fp)) != EOF) 
        putchar(c); 
    if (fclose(fp) == EOF) {
        perror("fclose");
        exit(1);
    }
    return 0;
}
