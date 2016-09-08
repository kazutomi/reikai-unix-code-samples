/* llio/trunc10.c */
#include <stdio.h>      /* perror */
#include <stdlib.h>     /* exit */
#include <unistd.h>     /* truncate */
#include <sys/types.h>  /* truncate */

int main(void) {
    if (truncate("hello.txt", 10) == -1) {
        perror("truncate");
        exit(1);
    }
    return 0;
}
