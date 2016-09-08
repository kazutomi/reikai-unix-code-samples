/* proc/showpid.c */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* exit */
#include <sys/types.h>  /* getpid */
#include <unistd.h>     /* getpid */

int main(void) {
    printf("pid = %d\n", getpid());
    exit(0);
}
